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
		if (!PlayerWidget) {
			PlayerWidget = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), UIClass, FName("PlayerUI"));
			if (!PlayerWidget) {
				//print("Error with Widget", -1);

			}
			else {
				PlayerWidget->AddToViewport();
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
	if (bIsDead||bIsInIFrames) {
		return;
	}

	if (bIsDashing) {
		FVector afterDashImpulse = bImpulsePower;
		afterDashImpulse.Y *= GetActorForwardVector().Y;
		afterDashImpulse.Z += 100;
		CharMoveComponent->StopMovementImmediately();
		CharMoveComponent->AddImpulse(afterDashImpulse * 1000);
		//print("AfterDashing with: Y:" + FString::SanitizeFloat(afterDashImpulse.Y) + " and Z:" + FString::SanitizeFloat(afterDashImpulse.Z),-1);
		bIsDashing = false;
		ResetAxis(4, true, 0);
		return;
	}
	if (!bIsInAnim) {
		if (ComboState < 0) {

			if (!(CharMoveComponent->IsFalling())) {
				//When ground jump
				bIsTouchingGroundOnce = true;
				bIsInAir = true;
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
	bIsInAnim = true;
	//print("Playing anim",-1);
	ComboFollowupTimer = 0;
}

void AGTFPlayer::OnMontageEnd(UAnimMontage* Montage, bool binterrupted) {
	bIsInAnim = false;
	if (ComboState > -1) {
		
		Score += 300;
		bIsInCombo = true;
		ComboDurationTimer = 0;
		//print("Attacking target ",10);
		if (Target->RecieveDamage(AttackPower))
		{
			print("Target is Dead", -1);
			Score += 200;


		
			
			ReleaseCombo();
			
			CharMoveComponent->AddImpulse(FVector(0, 0, 1200), true);
			bDidHomingOnce = false;
			bIsInIFrames = true;
			IFramesTime = 0;
			//DisableInput(GetWorld()->GetFirstPlayerController());

		}

	}


}
void AGTFPlayer::Dash() {
	if (bIsDead||bIsInIFrames) {
		return;
	}

	if (!bIsInAnim || !bIsDashing) {
		//GetMesh()->BodyInstance.bLockRotation = true;
		if (!(CharMoveComponent->IsFalling()) && ComboState < 0) {

			CharMoveComponent->StopMovementImmediately();
			ResetAxis(4, true, 0);
			FVector dashfinalImpulse = DashImpulse * GetActorForwardVector() * 100;
			CharMoveComponent->BrakingFrictionFactor = 0;
			bIsDashing = true;
			DashTimer = 0;
			CharMoveComponent->AddImpulse(dashfinalImpulse, true);
			//print("Dashing",-1);
		}
		else {
			if (!IsValid(Target)) {

				if (!bIsWallStuck) {
					if (!bIsLocked) {
						if (!bDidHomingOnce) {
							//When in the air do homing attack
							FVector impulse = GetActorForwardVector() * bImpulsePower.Y * 1000;
							impulse.Z = bImpulsePower.Z * 1000;

							if (IsValid(PotentialTarget)) {

								float relativeY = PotentialTarget->GetActorLocation().Y - GetActorLocation().Y;
								float relativeZ = PotentialTarget->GetActorLocation().Z - GetActorLocation().Z;
								float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));

								//print("Angle to boost at: " + FString::SanitizeFloat(angle),-1);
								if (FMath::Abs(angle) < 45) {
									impulse = FVector(0, relativeY, relativeZ);
									impulse.Normalize();
									impulse *= (1000 * HomingImpulsePower);
									impulse.Z = 0;
								}
								PotentialTarget->EnableTargeting(false);
								PotentialTarget = nullptr;
							}
							LockTimer = 0;
							bIsLocked = true;
							CharMoveComponent->StopMovementImmediately();
							ResetAxis(4, false, 0);

							CharMoveComponent->AddImpulse(impulse);
							bDidHomingOnce = true;
							//print("Homing",-1);
						}
					}
				}
				else {

					//If stuck to wall to walljump
					ResetAxis(4, false, 0);

					CharMoveComponent->StopMovementImmediately();
					CharMoveComponent->AddImpulse(WallReboundImpulse * 12, true);
					LockTimer = 0;



					//print("Rebound" + WallReboundImpulse.ToString(),-1);

					bIsWallStuck = false;


				}

			}
			else {

				AttackCombo();
			}
		}
	}

}


void AGTFPlayer::AttackCombo() {

	//Verify if in Anim or no Anims loaded
	if (bIsInAnim || AttackAnims.Num() < 1 ||bIsInIFrames) {
		print("Failed to Attack", -1);
		return;
	}


	//Play Attack Anim


	//Attack calcs
	if (IsValid(Target)) {

		if (ComboState == -1) {
			ComboState++;
		}
		PlayAnimMontage(AttackAnims[ComboState], AttackSpeed);
		
		


		
		//Stop moving when attacking
		
		ComboState++;
		CharMoveComponent->StopMovementImmediately();
		ResetAxis(0, false, 0);

		ComboNumber++;
		ComboNumber %= 4;
	}



	//print("Attacking with " + FString::FromInt(ComboState),-1);



}

void AGTFPlayer::ReleaseCombo()
{
	//print("Releasing from combo",-1);
	ComboState = -1;

	Target = nullptr;
	ResetAxis();

}

void AGTFPlayer::MoveRight(float Value)
{
	if (bIsDead||bIsInIFrames) {
		return;
	}

	if (!bIsWallStuck && !bIsInAnim) {
		if (Value != 0 && ComboState > -1) {
			//Stop mid combo when moving
			ReleaseCombo();
			bDidHomingOnce = false;

		}
		if (!bIsLocked && !IsValid(Target) && !bIsDashing) {
			AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			if (Value != 0) {
				ResetAxis();

			}

		}
	}

}

void AGTFPlayer::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (bIsDead) {
		return;
	}

	if (bIsInIFrames) {
		return;
	}
	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	AWall* wall = Cast<AWall>(OtherActor);
	if (IsValid(enemy)) {
		if (bIsLocked || bIsDashing) {

			Target = enemy;
			//Enemy got hit
			bIsLocked = false;
			ResetAxis();
			CharMoveComponent->StopMovementImmediately();
			AttackCombo();


			print("Hit Enemy", -1);
			PreviousWall = nullptr;
		}
		else {
			//Recieve Damage from Enemy

			//ReduceHP
			ReceiveDamage(enemy->AttackPower);


			//Change color
			if (ComboState < 0) {
				if (matInstance != nullptr) {
					matInstance->SetVectorParameterValue("BodyColor", FColor::Red);
					//printOnce2("Color normal");
				}
				if (IsValid(PotentialTarget)) {

					PotentialTarget->EnableTargeting(false);
					PotentialTarget = nullptr;

				}

				//Turn IFrames
				//DisableInput(GetWorld()->GetFirstPlayerController());
				bIsInIFrames = true;

				//Getting knocked back
				CharMoveComponent->StopMovementImmediately();
				FVector knockback = FVector(0, -GetActorForwardVector().Y * 1000, 900);
				ResetAxis(4, true, 0);
				CharMoveComponent->AddImpulse(knockback, true);
				//print("Knocked back with" + knockback.ToString(), -1);
			}
		}

	}

	if (IsValid(wall) && wall != PreviousWall) {
		if (!CharMoveComponent->IsWalking()) {
			CharMoveComponent->StopMovementImmediately();
			//Wall got hit
			ResetAxis(0);
			bIsWallStuck = true;
			bIsLocked = false;
			bDidHomingOnce = false;
			//Turn around
			AddActorWorldRotation(FRotator(0, 180, 0));
			WallReboundImpulse = FVector(0, FMath::Sign(GetActorLocation().Y - wall->GetActorLocation().Y) * 200, 100);
			PreviousWall = wall;
			print("Hit wall", -1);
		}


	}




}

//To replace in blueprint
void AGTFPlayer::Tick(float delta) {
	if (bIsDead) {
		return;
	}
	//IFrames
	if (bIsInIFrames) {
		IFramesTimer += delta;
		//print("Is IFraming",6);
		if (IFramesTimer > IFramesTime) {
			bIsInIFrames = false;
			IFramesTimer = 0;
			if (matInstance != nullptr) {
				matInstance->SetVectorParameterValue("BodyColor", matOriginalColor);

			}
			//EnableInput(GetWorld()->GetFirstPlayerController());
			//print("Stop IFraming", 6);

		}
		else {
			return;
		}

	}

	//Attack state debug

	if (bIsLocked || bIsDashing || (ComboState > -1)) {

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

	if (bIsInAir && !bDidHomingOnce && !bIsLocked && (ComboState < 0) && !bIsInIFrames) {
		FHitResult HitResult;
		FVector StartLocation = GetActorLocation();
		FVector EndLocation = StartLocation + GetActorForwardVector() * 750;
		//print(StartLocation.ToString());



		bool hit = UKismetSystemLibrary::BoxTraceSingleForObjects(this, StartLocation, EndLocation, HalfSize, FRotator::ZeroRotator, UObjectsToHoming, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);
		if (hit) {
			if (IsValid(PotentialTarget)) {
				if (PotentialTarget != Cast<AEnemy>(HitResult.Actor)) {
					PotentialTarget->EnableTargeting(false);
					//print("Changing Target", -1);
				}
			}

			PotentialTarget = Cast<AEnemy>(HitResult.Actor);
			float relativeY = PotentialTarget->GetActorLocation().Y - GetActorLocation().Y;
			float relativeZ = PotentialTarget->GetActorLocation().Z - GetActorLocation().Z;
			float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));
			if (FMath::Abs(angle) < 45) {
				PotentialTarget->EnableTargeting(true);
				//print("Catching stuff",2);
			}
			else {
				PotentialTarget->EnableTargeting(false);
				PotentialTarget = nullptr;
				//print("Not looking for targets",2);

			}




		}
		else {
			if (IsValid(PotentialTarget)) {

				PotentialTarget->EnableTargeting(false);
				PotentialTarget = nullptr;

			}

		}
	}
	else {
		//print("Not looking for targets",2);
		if (IsValid(PotentialTarget)) {

			PotentialTarget->EnableTargeting(false);
			PotentialTarget = nullptr;

		}
	}


	//Time to free fall
	if (bIsLocked && LockTimer < TimeToFreeHoming) {
		LockTimer += delta;

	}
	else {
		bIsLocked = false;

	}

	//Time to free fall
	if (bIsInCombo && ComboDurationTimer < ComboDurationTime) {
		ComboDurationTimer += delta;

	}
	else {
		bIsInCombo = false;
		ComboNumber = 0;
	}
	//
	//Dash Timer
	if (bIsDashing)
	{
		if (DashTimer < dashTime) {
			DashTimer += delta;

		}
		else {
			bIsDashing = false;
			CharMoveComponent->BrakingFrictionFactor = 40;
			if (CharMoveComponent->IsWalking())
				CharMoveComponent->StopMovementImmediately();
		}
	}
	//

	//Time to break combo after move
	if (ComboState > -1) {
		if (ComboFollowupTimer < ComboFollowupTime) {
			ComboFollowupTimer += delta;

		}
		else {
			ReleaseCombo();
		}
	}
	//

	//Touching ground
	if (CharMoveComponent->IsWalking()) {
		bIsWallStuck = false;
		if (bIsTouchingGroundOnce) {
			//Reset values when touching ground for first time
			if (IsValid(PotentialTarget)) {
				PotentialTarget->EnableTargeting(false);
				PotentialTarget = nullptr;
			}
			bIsLocked = false;
			ResetAxis();
			bIsInAir = false;
			bIsTouchingGroundOnce = false;
			ComboState = -1;
			PreviousWall = nullptr;
			ReleaseCombo();
			bDidHomingOnce = false;
			//print(CharMoveComponent->Velocity.ToString());
		}

	}
	else {
		bIsTouchingGroundOnce = true;
	}




	if (bIsWallStuck) {
		//Falling when wall stuck
		CharMoveComponent->AddForce(FVector(0, 0, DescendWallSpeed));

	}

}



void AGTFPlayer::ResetAxis(float gravity, bool bEnableInput, float fallingLateralFriction) {

	CharMoveComponent->GravityScale = gravity;
	bIsLocked = !bEnableInput;
	CharMoveComponent->FallingLateralFriction = fallingLateralFriction;
	CharMoveComponent->BrakingFrictionFactor = 40;Hp


}


void AGTFPlayer::ReceiveDamage(float damage)
{
	//print("Enemy attack stat" + FString::SanitizeFloat(damage), -1);

	//Calculating damage after defense
	damage -= Defense;
	if (damage < 1) {
		damage = 1;
	}
	//print("Player defense stat" + FString::SanitizeFloat(defense),-1);
	print("Recieving " + FString::SanitizeFloat(damage) + " damage", -1);
	Hp -= damage;
	if (Hp <= 0) {
		//Player dies if hp <= 0
		bIsDead = true;
	}


}



