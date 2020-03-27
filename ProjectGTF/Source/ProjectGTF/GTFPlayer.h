// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Wall.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GTFPlayer.generated.h"


UCLASS()
class PROJECTGTF_API AGTFPlayer : public ACharacter
{
	GENERATED_BODY()
	/** Side view camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCameraComponent;

	/** Camera boom positioning the camera beside the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;


	
	// Sets default values for this character's properties
	AGTFPlayer();
public:
	

	//Homming Attack values
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float impulsePower = 100;

	UPROPERTY(BlueprintReadWrite)
	bool isHomming = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool isInAir = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HalfSize = FVector(10, 40, 480);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TEnumAsByte<EObjectTypeQuery>> objectsToHomming;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float descendWallSpeed = -1000;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float homingImpulsePower = 200;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeToFreeHoming = 2;

	//Rolling 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* RollAnim;

	//Wall jump 
	UPROPERTY(BlueprintReadWrite)
	bool isWallStuck = false;
	
	UPROPERTY(BlueprintReadWrite)
	bool didWallJumpOnce = false;
	


private:
	//Movement
	bool isTouchingGroundOnce = false;
	UCharacterMovementComponent* CharMoveComponent;\

	//Wall rebound
	FVector wallReboundImpulse;
	AWall* previousWall;

	//Homing
	bool LockHoming = false;
	float LockTimer = 100;

	//Rolling
	bool isRolling = false;
protected:
	
	/** Called for side to side input */
	void MoveRight(float Val);




	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	void Jump();
	void StopJumping();
	void Roll();
	// End of APawn interface
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
	void OnRollEnded(UAnimMontage* Montage, bool binterrupted);

private: 

	void ResetAxis(float gravity = 4, bool enableInput = true, float fallingLateralFriction = 50);


};
