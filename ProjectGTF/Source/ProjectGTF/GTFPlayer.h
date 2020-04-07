// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wall.h"
#include "Enemy.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
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


	
	

	//Homming Attack values
	UPROPERTY(EditAnywhere, BlueprintReadWrite , Category = HomingAttack)
	FVector impulsePower = FVector(0, 100,0);

	UPROPERTY(BlueprintReadWrite, Category = HomingAttack)
	bool isLocked = false;
	
	UPROPERTY(BlueprintReadWrite, Category = State)
	bool isInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HomingAttack)
	FVector HalfSize = FVector(10, 40, 480);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HomingAttack)
	TArray<TEnumAsByte<EObjectTypeQuery>> objectsToHomming;
	
	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HomingAttack)
	float homingImpulsePower = 400;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HomingAttack)
	float TimeToFreeHoming = 0.4;
	//
	//Grounded Dash 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroundedDash)
	FVector dashImpulse = FVector(0,100,0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GroundedDash)
	float dashTime = 0.5f;

	//
	//Wall jump 
	UPROPERTY(BlueprintReadWrite, Category = WallJump)
	bool isWallStuck = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallJump)
	float descendWallSpeed = -20000.0;

	UPROPERTY(BlueprintReadWrite, Category = WallJump)
	bool didWallJumpOnce = false;
	//
	//AttackCombo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackCombo)
	TArray<UAnimMontage*> AttackAnims;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackCombo)
	float comboFollowupTime = 1.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AttackCombo)
	float attackSpeed =1;

	//IFrames
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = IFrames)
	float IFramesTime = 0.5f;

private:
	//General
	bool inAnim = false;
	UMaterialInstanceDynamic* matInstance; //Character Material
	FLinearColor matOriginalColor; //Material original color

	//Player Stats
	float attackPower = 25;
	float defense = 50;
	float hp = 100;

	//Movement
	bool isTouchingGroundOnce = false;
	UCharacterMovementComponent* CharMoveComponent;

	//Wall rebound
	FVector wallReboundImpulse;
	AWall* previousWall;

	//Homing
	float LockTimer = 0;
	bool didHomingOnce = false;
	
	//Attack Combo
	int comboState = -1;
	float comboFollowupTimer = 0;
	AEnemy* target;

	//Grounded Dash
	bool isDashing = false;
	float DashTimer = 0;

	//Enemy Targetting
	AEnemy* potentialTarget;

	//IFrames
	float iFramesTimer = 0;
	bool isInIFrames;



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

	UFUNCTION(BlueprintCallable)
	void HommingTick(float delta);

	UFUNCTION()
	void OnMontageBegin(UAnimMontage* Montage);
	
	UFUNCTION()
	void OnMontageEnd(UAnimMontage* Montage, bool binterrupted);

private: 

	void ResetAxis(float gravity = 4, bool enableInput = true, float fallingLateralFriction = 50);
	void ReleaseCombo();

};
