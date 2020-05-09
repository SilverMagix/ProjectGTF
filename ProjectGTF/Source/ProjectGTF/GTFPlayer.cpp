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
	GetCharacterMovement()->GravityScale = 4.f;
	GetCharacterMovement()->AirControl = 0.01f;
	GetCharacterMovement()->JumpZVelocity = 2000.0f;
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
			PlayerWidget = CreateWidget<UPlayerWidget>(GetWorld()->GetFirstPlayerController(), UIClass, FName("PlayerUI"));
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
	if (bIsDead || bIsInIFrames||bIsInAnim) {
		return;
	}

	if (bIsDashing) {
		FVector afterDashImpulse = NotHomingImpulsePower;
		afterDashImpulse.Y *= GetActorForwardVector().Y;
		afterDashImpulse.Z += 150;
		CharMoveComponent->StopMovementImmediately();
		ResetAxis(4, true, 0);
		CharMoveComponent->AddImpulse(afterDashImpulse * 12, true);
		LockTimer = 0;
		bIsLocked = true;
		//print("AfterDashing with: Y:" + FString::SanitizeFloat(afterDashImpulse.Y) + " and Z:" + FString::SanitizeFloat(afterDashImpulse.Z),-1);
		bIsDashing = false;
		return;
	}

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

	// Check Battle Status after each attack
	if (ComboState > -1) {
		Score += 300;
		bIsInCombo = true;
		ComboDurationTimer = 0;
		//print("Attacking target ",10);

		//Do damage to enemy
		if (Target->IsDead(AttackPower))
		{
			//If Dead

			print("Target is Dead", -1);
			Score += 200;


			ReleaseCombo();

			//Add small impulse towards Z up to add some momentum 
			CharMoveComponent->AddImpulse(FVector(0, 0, 1700), true);
			bDidHomingOnce = false;
			bIsInIFrames = true;
			IFramesTimer = 0.2;
			//DisableInput(GetWorld()->GetFirstPlayerController());

		}

	}


}

void AGTFPlayer::Dash() {
	if (bIsDead || bIsInIFrames) {
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
							FVector impulse = GetActorForwardVector() * NotHomingImpulsePower.Y * 1000;
							impulse.Z = NotHomingImpulsePower.Z * 1000;

							if (IsValid(PotentialTarget)) {

								float relativeY = PotentialTarget->GetActorLocation().Y - GetActorLocation().Y;
								float relativeZ = PotentialTarget->GetActorLocation().Z - GetActorLocation().Z;
								float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));

								//print("Angle to boost at: " + FString::SanitizeFloat(angle),-1);
								if (FMath::Abs(angle) < 45) {
									impulse = FVector(0, relativeY, relativeZ);
									impulse.Normalize();
									impulse *= (1000 * HomingImpulsePower.Y);
									impulse.Z = HomingImpulsePower.Z;
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
					LockTimer = 0.2;



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
	if (bIsInAnim || AttackAnims.Num() < 1 || bIsInIFrames) {
		//print("Failed to Attack with" + AttackAnims.Num() + bIsInAnim + bIsInIFrames, -1);
		return;
	}


	//Play Attack Anim


	//Attack calcs
	if (IsValid(Target)) {
		Target->Push(GetActorLocation(), GetActorForwardVector());
		if (ComboState == -1) {
			ComboState++;
		}
		PlayAnimMontage(AttackAnims[ComboState], AttackSpeed);
		//Stop moving when attacking

		ComboState++;
		ComboState %= 4;
		CharMoveComponent->StopMovementImmediately();
		ResetAxis(0, false, 0);
		//print("Doing combo number " + FString::FromInt(ComboNumber),-1);
		ComboNumber++;
		
		PlayerWidget->ActivateCombo(ComboNumber);

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
	if (bIsDead || bIsInIFrames) {
		return;
	}

	if (ComboState > -1) {
		if (GetActorForwardVector().Y > 0) {
			if (Value < 0) {
				return;
			}

		}
		else {
			if (Value > 0) {
				return;
			}

		}
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
	if (bIsDead || bIsInIFrames || ComboState > -1) {
		return;
	}

	AEnemy* enemy = Cast<AEnemy>(OtherActor);
	AWall* wall = Cast<AWall>(OtherActor);
	if (IsValid(enemy)) {
		if (bIsLocked || bIsDashing) {
			print("Caught Enemy", -1);
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
				float normalizedY = FMath::Sign(GetActorLocation().Y - enemy->GetActorLocation().Y);
				FVector knockback = FVector(0, normalizedY * 1000, 900);
				ResetAxis(4, true, 0);
				CharMoveComponent->AddImpulse(knockback, true);
				print("Knocked back with" + knockback.ToString(), -1);
			}
		}

	}

	if (IsValid(wall) && wall != PreviousWall) {

		FVector StartLocation = GetActorLocation();
		FVector EndLocation = StartLocation + FVector(0, 0, 200);
		FHitResult wallHitResult;
		//Casting line to see if it hits top wall
		bool hit = UKismetSystemLibrary::LineTraceSingleForObjects(this, StartLocation, EndLocation, UObjectsToHoming, false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, wallHitResult, true);
		if (!hit) {
			if (!CharMoveComponent->IsWalking()) {
				CharMoveComponent->StopMovementImmediately();
				//Wall got hit
				ResetAxis(0);
				bIsWallStuck = true;
				bIsLocked = false;
				bDidHomingOnce = false;
				//Turn around
				AddActorWorldRotation(FRotator(0, 180, 0));
				WallReboundImpulse.Y = FMath::Abs(WallReboundImpulse.Y);
				WallReboundImpulse.Y *= GetActorForwardVector().Y;
				PreviousWall = wall;
				print("Hit wall", -1);
			}
		}

	}




}

//To replace in blueprint
void AGTFPlayer::Tick(float delta) {
	Super::Tick(delta);
	if (bIsDead) {
		return;
	}
	//IFrames
	if (bIsInIFrames) {
		IFramesTimer += delta;
		//print("Is IFraming for " + FString::SanitizeFloat(IFramesTimer),-1);
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
		bIsAttacking = true;
		if (matInstance != nullptr) {
			matInstance->SetVectorParameterValue("BodyColor", FLinearColor(FColor::Blue));
			//printOnce2("Color Blue");
		}
	}
	else {
		bIsAttacking = false;

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


		bool hit = UKismetSystemLibrary::BoxTraceSingleForObjects(this, StartLocation, EndLocation, HalfSize, FRotator::ZeroRotator, UObjectsToHoming, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);
		if (hit) {
			if (IsValid(PotentialTarget)) {
				if (PotentialTarget != Cast<AEnemy>(HitResult.Actor)) {
					PotentialTarget->EnableTargeting(false);
					//print("Changing Target", -1);
				}
			}

		//print("Trying to catch " + msg,-1);
			PotentialTarget = Cast<AEnemy>(HitResult.Actor);

			float relativeY = PotentialTarget->GetActorLocation().Y - GetActorLocation().Y;
			float relativeZ = PotentialTarget->GetActorLocation().Z - GetActorLocation().Z;
			float angle = FMath::RadiansToDegrees(FMath::Atan(relativeZ / relativeY));
			if (FMath::Abs(angle) < 45) {
				PotentialTarget->EnableTargeting(true);
				//print("Catching stuff",12);
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
	if (bIsInCombo) {
		if (ComboDurationTimer < ComboDurationTime) {
			ComboDurationTimer += delta;

		}
		else {
			bIsInCombo = false;
			ComboNumber = 0;
			//print("Resetting Combo Number", -1);
		}
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

		FVector StartLocation = GetActorLocation();

		FVector EndLocation = StartLocation + FVector(0, 50, 0);
		StartLocation -= FVector(0, 50, 0);
		FHitResult wallHitResult;

		//Checking if still hitting a wall
		bool hit = UKismetSystemLibrary::LineTraceSingleForObjects(this, StartLocation, EndLocation, WallRef, false, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, wallHitResult, true);
		
		if (!hit) {
		
			print("Falling off",-1);
			ResetAxis();
			bIsWallStuck = false;
			PreviousWall = nullptr;

		}
	}

}



void AGTFPlayer::ResetAxis(float gravity, bool bEnableInput, float fallingLateralFriction) {

	CharMoveComponent->GravityScale = gravity;
	bIsLocked = !bEnableInput;
	CharMoveComponent->FallingLateralFriction = fallingLateralFriction;
	CharMoveComponent->BrakingFrictionFactor = 40;


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



