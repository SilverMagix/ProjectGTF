// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	

	RootComponent = Collider;
	Mesh->AttachToComponent(Collider,FAttachmentTransformRules::KeepRelativeTransform);
	Target->AttachToComponent(Mesh,FAttachmentTransformRules::KeepRelativeTransform);

}



// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Target->SetVisibility(false);
	LocationToGo = GetActorLocation();
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{

	if (!LocationToGo.ContainsNaN()) {
		SetActorLocation(FMath::VInterpTo(GetActorLocation(),LocationToGo,DeltaTime,2));
		
	}

	Super::Tick(DeltaTime);

}



bool AEnemy::IsDead(float damage)
{
	
	damage = damage / (Defense + 1);
	Hp -= damage;
	if (Hp <= 0) {
	
		DestroyEnemy();
		print("Enemy dead",-1);
		return true;
	}
	print("Enemy recieving Damage",-1);
	return false;
}

void AEnemy::Push(FVector impulse) {

	LocationToGo = GetActorLocation() + impulse * RecoilSpeed;

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
