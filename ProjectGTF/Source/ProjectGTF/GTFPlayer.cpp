#include "GTFPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine.h"



#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

AGTFPlayer::AGTFPlayer()
{
	CharMoveComponent = GetCharacterMovement();

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	PrimaryActorTick.bCanEverTick = true;
	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	SideViewCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
	SideViewCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	SideViewCameraComponent->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)



}

void AGTFPlayer::BeginPlay() {
	Super::BeginPlay();
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AGTFPlayer::OnCompHit);
	GetMesh()->GetAnimInstance()->OnMontageStarted.AddDynamic(this, &AGTFPlayer::OnMontageBegin);
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AGTFPlayer::OnMontageEnd);


	//Set Player UI
	if (UIClass) {
		if (!playerWidget) {
			playerWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), UIClass, FName("PlayerUI"));
			if (!playerWidget) {
				//print("Error with Widget", -1);

			}
			else {
				playerWidget->AddToViewport();
				//print("Placed widget", -1);
			}
		}
	}


	//Set dynamic material
	UMaterialInterface* Material = GetMesh()->GetMaterial(0);
	matInstance = GetMesh()->CreateDynamicMaterialInstance(0, Material);
	if (matInstance != nullptr) {
		matInstance->GetVectorParameterValue(FName("BodyColor"), matOriginalColor);
		//print("Got Mat Texture",-1);
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AGTFPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGTFPlayer::Jump);

	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Dash", IE_Pressed, this, &AGTFPlayer::Dash);


	PlayerInputComponent->BindAxis("MoveRight", this, &AGTFPlayer::MoveRight);

}

void AGTFPlayer::Jump()
{
	if (isDashing) {
		FVector afterDashImpulse = impulsePower;
		afterDashImpulse.Y *= GetActorForwardVector().Y;
		afterDashImpulse.Z += 100;
		CharMoveComponent->StopMovementImmediately();
		CharMoveComponent->AddImpulse(afterDashImpulse * 1000);
		//print("AfterDashing with: Y:" + FString::SanitizeFloat(afterDashImpulse.Y) + " and Z:" + FString::SanitizeFloat(afterDashImpulse.Z),-1);
		isDashing = false;
		ResetAxis(4, true, 0);
		return;
	}
	if (!inAnim) {
		if (comboState < 0) {

			if (!(CharMoveComponent->IsFalling())) {
				//When ground jump
				isTouchingGroundOnce = true;
				isInAir = true;
				bPressedJump = true;
				JumpKeyHoldTime = 0.0f;
				ResetAxis(4, true, 0);
				return;
			}

		}

		Dash();


	}


}




void AGTFPlayer::StopJumping() {

	bPressedJump = false;
	ResetJumpState();


}

void AGTFPlayer::OnMontageBegin(UAnimMontage* Montage) {
	inAnim = true;
	//print("Playing anim",-1);
	comboFollowupTimer = 0;
}

void AGTFPlayer::OnMontageEnd(UAnimMontage* Montage, bool binterrupted) {
	inAnim = false;



}
void AGTFPlayer::Dash() {
	if (!inAnim || !isDashing) {
		//GetMesh()->BodyInstance.bLockRotation = true;
		if (!(CharMoveComponent->IsFalling()) && comboState < 0) {

			CharMoveComponent->StopMovementImmediately();
			ResetAxis(4, true, 0);
			FVector dashfinalImpulse = dashImpulse * GetActorForwardVector() * 100;
			CharMoveComponent->BrakingFrictionFactor = 0;
			isDashing = true;
			DashTimer = 0;
			CharMoveComponent->AddImpulse(dashfinalImpulse, true);
			//print("Dashing",-1);
		}
		else {
			if (!IsValid(target)) {

				if (!isWallStuck) {
					if (!isLocked) {
						if (!didHomingOnce) {
							//When in the air do homing attack
							FVector impulse = GetActorForwardVector() * impulsePower.Y * 1000;
							impulse.Z = impulsePower.Z * 1000;

							if (IsValid(potentialTarget)) {

								float relativeY = potentialTarget->GetActorLocation().Y - GetActorLocation().Y;
								float relativeZ = potentialTarget->GetActorLocation().Z - GetActorLocation().Z;
								float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));

								//print("Angle to boost at: " + FString::SanitizeFloat(angle),-1);
								if (FMath::Abs(angle) < 45) {
									impulse = FVector(0, relativeY, relativeZ);
									impulse.Normalize();
									impulse *= (1000 * homingImpulsePower);
									impulse.Z = 0;
								}
								potentialTarget->EnableTargeting(false);
								potentialTarget = nullptr;
							}
							LockTimer = 0;
							isLocked = true;
							CharMoveComponent->StopMovementImmediately();
							ResetAxis(4, false, 0);

							CharMoveComponent->AddImpulse(impulse);
							didHomingOnce = true;
							//print("Homing",-1);
						}
					}
				}
				else {

					//If stuck to wall to walljump
					ResetAxis(4, false, 0);

					CharMoveComponent->StopMovementImmediately();
					CharMoveComponent->AddImpulse(wallReboundImpulse * 12, true);
					LockTimer = 0;



					//print("Rebound" + wallReboundImpulse.ToString(),-1);

					isWallStuck = false;


				}

			}
			else {

				AttackCombo();
			}
		}
	}

}


void AGTFPlayer::AttackCombo() {

	if (IsValid(target)) {

		bool isTargetDead = target->RecieveDamage(attackPower);

		//print("Attacking target ",10);
		if (isTargetDead)
		{
			ReleaseCombo();
			didHomingOnce = false;
			target = nullptr;

		}
	}


	if (inAnim || AttackAnims.Num() < 1) {
		print("Failed to Attack", -1);
		return;
	}
	if (comboState == AttackAnims.Num() - 1) {
		comboState = -1;
	}
	comboState++;
	PlayAnimMontage(AttackAnims[comboState], attackSpeed);

	//Stop moving when attacking
	CharMoveComponent->StopMovementImmediately();
	ResetAxis(0, false, 0);


	//print("Attacking with " + FString::FromInt(comboState),-1);



}

void AGTFPlayer::MoveRight(float Value)
{
	if (!isWallStuck && !inAnim) {
		if (Value != 0 && comboState > -1) {
			//Stop mid combo when moving
			ReleaseCombo();
			didHomingOnce = false;

		}
		if (!isLocked && !IsValid(target) && !isDashing) {
			AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			if (Value != 0) {
				ResetAxis();

			}

		}
	}

}

void AGTFPlayer::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (isInIFrames) {
		return;
	}
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	AWall* wall = Cast<AWall>(OtherActor);
	if (IsValid(enemy)) {
		if (isLocked || isDashing) {

			target = enemy;
			//Enemy got hit
			isLocked = false;
			ResetAxis();
			CharMoveComponent->StopMovementImmediately();
			AttackCombo();
			print("Hit Enemy", -1);
			previousWall = nullptr;
		}
		else {
			//Recieve Damage from Enemy

			//ReduceHP
			ReceiveDamage(enemy->attackPower);

			if (comboState < 0) {
				if (matInstance != nullptr) {
					matInstance->SetVectorParameterValue("BodyColor", FColor::Red);
					//printOnce2("Color normal");
				}
				if (IsValid(potentialTarget)) {

					potentialTarget->EnableTargeting(false);
					potentialTarget = nullptr;

				}
				DisableInput(GetWorld()->GetFirstPlayerController());
				isInIFrames = true;

				//Getting knocked back
				CharMoveComponent->StopMovementImmediately();
				FVector knockback = FVector(0, -GetActorForwardVector().Y * 1000, 900);
				ResetAxis(4, true, 0);
				CharMoveComponent->AddImpulse(knockback, true);
				//print("Knocked back with" + knockback.ToString(), -1);
			}
		}

	}

	if (IsValid(wall) && wall != previousWall) {
		if (!CharMoveComponent->IsWalking()) {
			CharMoveComponent->StopMovementImmediately();
			//Wall got hit
			ResetAxis(0);
			isWallStuck = true;
			isLocked = false;
			didHomingOnce = false;
			//Turn around
			AddActorWorldRotation(FRotator(0, 180, 0));
			wallReboundImpulse = FVector(0, FMath::Sign(GetActorLocation().Y - wall->GetActorLocation().Y) * 200, 100);
			previousWall = wall;
			print("Hit wall", -1);
		}


	}




}

//To replace in blueprint
void AGTFPlayer::HommingTick(float delta) {

	//IFrames
	if (isInIFrames) {
		iFramesTimer += delta;
		//print("Is IFraming",6);
		if (iFramesTimer > IFramesTime) {
			isInIFrames = false;
			iFramesTimer = 0;
			if (matInstance != nullptr) {
				matInstance->SetVectorParameterValue("BodyColor", matOriginalColor);

			}
			EnableInput(GetWorld()->GetFirstPlayerController());
			//print("Stop IFraming", 6);

		}
		else {
			return;
		}

	}

	//Attack state debug

	if (isLocked || isDashing || (comboState > -1)) {

		if (matInstance != nullptr) {
			matInstance->SetVectorParameterValue("BodyColor", FLinearColor(FColor::Blue));
			//printOnce2("Color Blue");
		}
	}
	else {
		if (matInstance != nullptr) {
			matInstance->SetVectorParameterValue("BodyColor", matOriginalColor);
			//printOnce2("Color normal");
		}
	}
	//

	//inAir targetting
	if (isInAir && !didHomingOnce && !isLocked && (comboState < 0) && !isInIFrames) {
		FHitResult HitResult;
		FVector StartLocation = GetActorLocation();
		FVector EndLocation = StartLocation + GetActorForwardVector() * 750;
		//print(StartLocation.ToString());



		bool hit = UKismetSystemLibrary::BoxTraceSingleForObjects(this, StartLocation, EndLocation, HalfSize, FRotator::ZeroRotator, objectsToHomming, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);
		if (hit) {
			if (IsValid(potentialTarget)) {
				if (potentialTarget != Cast<AEnemy>(HitResult.Actor)) {
					potentialTarget->EnableTargeting(false);
					//print("Changing Target", -1);
				}
			}

			potentialTarget = Cast<AEnemy>(HitResult.Actor);
			float relativeY = potentialTarget->GetActorLocation().Y - GetActorLocation().Y;
			float relativeZ = potentialTarget->GetActorLocation().Z - GetActorLocation().Z;
			float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));
			if (FMath::Abs(angle) < 45) {
				potentialTarget->EnableTargeting(true);
				//print("Catching stuff",2);
			}
			else {
				potentialTarget->EnableTargeting(false);
				potentialTarget = nullptr;
				//print("Not looking for targets",2);

			}




		}
		else {
			if (IsValid(potentialTarget)) {

				potentialTarget->EnableTargeting(false);
				potentialTarget = nullptr;

			}

		}
	}
	else {
		//print("Not looking for targets",2);
		if (IsValid(potentialTarget)) {

			potentialTarget->EnableTargeting(false);
			potentialTarget = nullptr;

		}
	}


	//Time to free fall
	if (isLocked && LockTimer < TimeToFreeHoming) {
		LockTimer += delta;

	}
	else {
		isLocked = false;

	}
	//
	//Dash Timer
	if (isDashing)
	{
		if (DashTimer < dashTime) {
			DashTimer += delta;

		}
		else {
			isDashing = false;
			CharMoveComponent->BrakingFrictionFactor = 40;
			if (CharMoveComponent->IsWalking())
				CharMoveComponent->StopMovementImmediately();
		}
	}
	//

	//Time to break combo after move
	if (comboState > -1) {
		if (comboFollowupTimer < comboFollowupTime) {
			comboFollowupTimer += delta;

		}
		else {
			ReleaseCombo();
		}
	}
	//

	//Touching ground
	if (CharMoveComponent->IsWalking()) {
		isWallStuck = false;
		if (isTouchingGroundOnce) {
			//Reset values when touching ground for first time
			if (IsValid(potentialTarget)) {
				potentialTarget->EnableTargeting(false);
				potentialTarget = nullptr;
			}
			isLocked = false;
			ResetAxis();
			isInAir = false;
			isTouchingGroundOnce = false;
			comboState = -1;
			previousWall = nullptr;
			ReleaseCombo();
			didHomingOnce = false;
			//print(CharMoveComponent->Velocity.ToString());
		}

	}
	else {
		isTouchingGroundOnce = true;
	}




	if (isWallStuck) {
		//Falling when wall stuck
		CharMoveComponent->AddForce(FVector(0, 0, descendWallSpeed));

	}

}



void AGTFPlayer::ResetAxis(float gravity, bool enableInput, float fallingLateralFriction) {

	CharMoveComponent->GravityScale = gravity;
	isLocked = !enableInput;
	CharMoveComponent->FallingLateralFriction = fallingLateralFriction;
	CharMoveComponent->BrakingFrictionFactor = 40;


}

void AGTFPlayer::ReleaseCombo()
{
	//print("Releasing from combo",-1);
	comboState = -1;

	target = nullptr;
	ResetAxis();

}

void AGTFPlayer::ReceiveDamage(float damage)
{
	//print("Enemy attack stat" + FString::SanitizeFloat(damage), -1);

	//Calculating damage after defense
	damage -= defense;
	if (damage < 1) {
		damage = 1;
	}
	//print("Player defense stat" + FString::SanitizeFloat(defense),-1);
	print("Recieving " + FString::SanitizeFloat(damage) + " damage", -1);
	hp -= damage;
	if (hp <= 0) {
		//Player dies if hp <= 0
		DisableInput();
	}

	
}



