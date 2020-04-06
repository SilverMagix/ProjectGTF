// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

class UStaticMeshComponent;

UCLASS()
class PROJECTGTF_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemy();


	/*UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemy> EnemyToSpawn;*/

	UPROPERTY(VisibleAnywhere)
	float attackPower;

private: 

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Target;
	
	UPROPERTY(VisibleAnywhere)
	float HP;

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void RecieveDamage(float damage);

	void DestroyEnemy();

	void EnableTargeting(bool enable);
	//AEnemy SpawnEnemy(int life, FVector spawnLocation);

};
