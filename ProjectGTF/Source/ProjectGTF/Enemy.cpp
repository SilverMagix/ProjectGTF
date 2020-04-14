// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	


	RootComponent = Collider;
	Mesh->AttachToComponent(Collider, FAttachmentTransformRules::KeepRelativeTransform);
	
	Target->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

}



// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Target->SetVisibility(false);
	LocationToGo = GetActorLocation();
	CurrentSpeed = Speed;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	if (DumbTimer > 3) {
		if (!LocationToGo.ContainsNaN()) {
			if (bIsGettingHit) {
				SetActorLocation(FMath::VInterpTo(GetActorLocation(), LocationToGo, DeltaTime, CurrentSpeed));
			}
			else {
				SetActorLocation(FMath::VInterpConstantTo(GetActorLocation(), LocationToGo, DeltaTime, CurrentSpeed));
			}


		}
	}

	if (bIsGettingHit) {
		if (RecoilTimer < RecoilTime) {
			RecoilTimer += DeltaTime;
		}
		else {
			bIsGettingHit = false;
			RecoilTimer = 0;
			DumbTimer = 0;
			print("Resetting dumb timer", -1);
		}
	}

	if (DumbTimer < 4) {
		DumbTimer += DeltaTime;
	}
	Super::Tick(DeltaTime);

}



bool AEnemy::IsDead(float damage)
{
	bIsGettingHit = true;
	damage = damage / (Defense + 1);
	Hp -= damage;
	if (Hp <= 0) {

		DestroyEnemy();
		print("Enemy dead", -1);
		return true;
	}
	print("Enemy recieving Damage", -1);
	return false;
}

void AEnemy::Push(FVector playerLocation, FVector impulse) {

	bIsGettingHit = true;
	LocationToGo = (GetActorLocation() + impulse * RecoilSpeed);
	LocationToGo.Z = playerLocation.Z;
	CurrentSpeed = 2;

}

void AEnemy::DestroyEnemy()
{
	Destroy();

}

void AEnemy::EnableTargeting(bool enable)
{
	Target->SetVisibility(enable);


}

//AEnemy AEnemy::SpawnEnemy(int life, FVector spawnLocation)
//{
//	FActorSpawnParameters SpawnParams;
//	
//	AActor* AEnemy = GetWorld()->SpawnActor<AActor>(EnemyToSpawn,spawnLocation,FRotator(),SpawnParams);
//
//
//
//}
