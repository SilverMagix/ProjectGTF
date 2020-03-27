#include "GTFPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Animation/AnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine.h"
#include "EnemyTemplate.h"


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)
#define printOnce(text) if (GEngine) GEngine->AddOnScreenDebugMessage(1, 1.5, FColor::White,text)

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
	GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this, &AGTFPlayer::OnRollEnded);
}


//////////////////////////////////////////////////////////////////////////
// Input

void AGTFPlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AGTFPlayer::Jump);

	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &AGTFPlayer::Roll);

	PlayerInputComponent->BindAxis("MoveRight", this, &AGTFPlayer::MoveRight);
	
}

void AGTFPlayer::Jump()
{
	isTouchingGroundOnce = true;
	//GetMesh()->BodyInstance.bLockRotation = true;
	if (!(CharMoveComponent->IsFalling())) {
		isInAir = true;
		bPressedJump = true;
		JumpKeyHoldTime = 0.0f;
	}
	else {
		if (!LockHoming) {
			if (!isWallStuck) {
				if (!isHomming) {
					FHitResult HitResult;
					FVector StartLocation = GetActorLocation();
					FVector EndLocation = StartLocation + GetActorForwardVector() * 750;
					FVector impulse = GetActorForwardVector() * impulsePower * 1000;

					bool hit = UKismetSystemLibrary::BoxTraceSingleForObjects(this, StartLocation, EndLocation, HalfSize, FRotator(), objectsToHomming, false, TArray<AActor*>(), EDrawDebugTrace::None, HitResult, true);
					if (hit) {

						float relativeY = HitResult.ImpactPoint.Y - GetActorLocation().Y;
						float relativeZ = HitResult.ImpactPoint.Z - GetActorLocation().Z;
						impulse = FVector(0, relativeY, relativeZ);
						impulse.Normalize();
						impulse *= (1000 * homingImpulsePower);

					}
					LockTimer = 0;
					isHomming = true;
					CharMoveComponent->StopMovementImmediately();
					ResetAxis(4, false, 0);
					CharMoveComponent->AddImpulse(impulse);
					print("Attacking");
				}
			}
			else {
				ResetAxis(4, false, 0);
				isHomming = false;
				CharMoveComponent->StopMovementImmediately();
				CharMoveComponent->AddImpulse(wallReboundImpulse * 12, true);
				LockTimer = 0;



				print("Rebound" + wallReboundImpulse.ToString());

				isWallStuck = false;


			}
		}
	}
	

}




void AGTFPlayer::StopJumping() {

	bPressedJump = false;
	ResetJumpState();


}

void AGTFPlayer::OnRollEnded(UAnimMontage* Montage, bool binterrupted){

	isRolling = false;

}
void AGTFPlayer::Roll() {

	if (!isRolling && CharMoveComponent->IsWalking()) {
		PlayAnimMontage(RollAnim);
		isRolling = true;
	}

}

void AGTFPlayer::MoveRight(float Value)
{
	// add movement in that direction
	if (!isWallStuck) {
		if (!LockHoming) {
			AddMovementInput(FVector(0.f, -1.f, 0.f), Value);
			if (Value != 0) {
				ResetAxis();
			} 
			
		}
	}
	
}

void AGTFPlayer::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AEnemyTemplate* enemy = Cast<AEnemyTemplate>(OtherActor);
	AWall* wall = Cast<AWall>(OtherActor);
	if (enemy != nullptr) {
		if (isHomming) {
		
			isHomming = false;
			ResetAxis();
			CharMoveComponent->StopMovementImmediately();
			CharMoveComponent->AddImpulse(FVector(0, 0, 1500), true);
			print("Homming");
		}

	}

	if (wall != nullptr && wall != previousWall) {
		if (!CharMoveComponent->IsWalking()) {
			CharMoveComponent->StopMovementImmediately();
			
			ResetAxis(0);
			isWallStuck = true;
			AddActorWorldRotation(FRotator(0, 180, 0));
			wallReboundImpulse = FVector(0, FMath::Sign(GetActorLocation().Y- wall->GetActorLocation().Y)*200, 100);
			previousWall = wall;
			print("Hit wall");
		}
	

	}




}

//To replace in blueprint
void AGTFPlayer::HommingTick(float delta) {

	if (LockTimer < TimeToFreeHoming) {
		LockTimer += delta;
	
	}
	else {
		LockHoming = false;
		
	}

	printOnce(TEXT("Friction") + FString::SanitizeFloat(CharMoveComponent->FallingLateralFriction));

	if (CharMoveComponent->IsWalking()) {
		isWallStuck = false;
		if (isTouchingGroundOnce) {
			isHomming = false;
			ResetAxis();
			isInAir = true;
			isTouchingGroundOnce = false;
			
			previousWall = nullptr;
			//print(CharMoveComponent->Velocity.ToString());
		}

	}
	else {
		isTouchingGroundOnce = true;
	}
	if (isWallStuck) {
		CharMoveComponent->AddForce(FVector(0,0,descendWallSpeed));
	
	}

}




void AGTFPlayer::ResetAxis(float gravity, bool enableInput, float fallingLateralFriction) {

	CharMoveComponent->GravityScale = gravity;
	LockHoming = !enableInput;
	CharMoveComponent->FallingLateralFriction = fallingLateralFriction;
	
}