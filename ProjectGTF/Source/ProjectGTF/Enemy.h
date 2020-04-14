// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/BoxComponent.h"
#include "UEnemyPathFollowComp.h"

#include "Enemy.generated.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

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
		float AttackPower = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Defense = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Hp = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
		float Speed = 60;

	//Hit Reaction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		FVector LocationToGo = FVector(0, 0, 0);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Target)
		float RecoilSpeed = 20;
	UPROPERTY()
		float RecoilTime = 2;

private:

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Mesh;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UBoxComponent* Collider;

	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* Target;
	


protected:
	//Enemy current Stats
	float CurrentSpeed;
	float RecoilTimer = 0;
	float DumbTimer = 4;

	//Attack Values
	bool bIsGettingHit;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	bool IsDead(float damage = 0);

	void Push(FVector playerLocation, FVector impulse);

	void DestroyEnemy();

	void EnableTargeting(bool enable);

	virtual void EnemyMove() PURE_VIRTUAL(AEnemy::EnemyMove(), return;);;

	//AEnemy SpawnEnemy(int life, FVector spawnLocation);

};
