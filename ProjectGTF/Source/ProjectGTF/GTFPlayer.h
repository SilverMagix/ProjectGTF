// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wall.h"
#include "Enemy.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/UserWidget.h"
#include "PlayerWidget.h"
#include "GTFPlayer.generated.h"


UCLASS()
class PROJECTGTF_API AGTFPlayer : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	AGTFPlayer();
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;

	//Widget
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget> UIClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = UI)
		UPlayerWidget* PlayerWidget;

	//General values

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
		bool bIsDead = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
		float IFramesTime = 0.5f;
	//Homming Attack values
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		FVector NotHomingImpulsePower = FVector(0, 400, 0);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		FVector HomingImpulsePower = FVector(0, 500, 0);

	UPROPERTY(BlueprintReadWrite, Category = "Battle|HomingAttack")
		bool bIsLocked = false;

	UPROPERTY(BlueprintReadWrite, Category = "State")
		bool bIsInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		FVector HalfSize = FVector(10, 40, 480);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		TArray<TEnumAsByte<EObjectTypeQuery>> UObjectsToHoming;
	


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		float TimeToFreeHoming = 0.4;
	//
	//Grounded Dash 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|GroundedDash")
		FVector DashImpulse = FVector(0, 100, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|GroundedDash")
		float dashTime = 0.5f;

	//
	//Wall jump 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|HomingAttack")
		TArray<TEnumAsByte<EObjectTypeQuery>> WallRef;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Battle|WallJump")
		FVector WallReboundImpulse = FVector(0,200,200);
	
	UPROPERTY(BlueprintReadWrite, Category = "Battle|WallJump")
		bool bIsWallStuck = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|WallJump")
		float DescendWallSpeed = -20000.0;

	UPROPERTY(BlueprintReadWrite, Category = "Battle|WallJump")
		bool bDidWallJumpOnce = false;
	//
	//AttackCombo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|AttackCombo")
		TArray<UAnimMontage*> AttackAnims;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|AttackCombo")
		float ComboFollowupTime = 1.6f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|AttackCombo")
		float ComboDurationTime = 5;

		float ComboDurationTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle|AttackCombo")
		float AttackSpeed = 1;

		bool bIsAttacking = false;


	//Player Stats
	float AttackPower = 25;
	float Defense = 0;
	float Hp = 100;
	int ComboNumber = 0;
	int Score = 0;



private:
	//General
	bool bIsInAnim = false;
	UMaterialInstanceDynamic* matInstance; //Character Material
	FLinearColor matOriginalColor; //Material original color

	//Movement
	bool bIsTouchingGroundOnce = false;
	UCharacterMovementComponent* CharMoveComponent;

	//Wall rebound
	AWall* PreviousWall;

	//Homing
	float LockTimer = 0;
	bool bDidHomingOnce = false;

	//Attack Combo
	int ComboState = -1;
	float ComboFollowupTimer = 0;
	AEnemy* Target;

	bool bIsInCombo = false;

	//Grounded Dash
	bool bIsDashing = false;
	float DashTimer = 0;

	//Enemy Targetting
	AEnemy* PotentialTarget;


	//IFrames
	float IFramesTimer = 0;
	bool bIsInIFrames;



protected:

	/** Called for side to side input */
	void MoveRight(float Val);




	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	//Action Functions
	void Jump();
	void StopJumping();
	void Dash();
	void AttackCombo();


	virtual void BeginPlay() override;

public:

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns SideViewCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetSideViewCameraComponent() const { return SideViewCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Called to bind functionality to input
	UFUNCTION()
		virtual void Tick(float delta) override;

	UFUNCTION()
		void OnMontageBegin(UAnimMontage* Montage);

	UFUNCTION()
		void OnMontageEnd(UAnimMontage* Montage, bool binterrupted);

private:


	void ResetAxis(float gravity = 4, bool bEnableInput = true, float fallingLateralFriction = 50);
	void ReleaseCombo();
	void ReceiveDamage(float damage);
};
