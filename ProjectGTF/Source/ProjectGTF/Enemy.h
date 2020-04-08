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




	//Stats
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float attackPower = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float defense = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float hp = 100;

private:

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Target;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	bool RecieveDamage(float damage);

	void DestroyEnemy();

	void EnableTargeting(bool enable);
	//AEnemy SpawnEnemy(int life, FVector spawnLocation);

};
