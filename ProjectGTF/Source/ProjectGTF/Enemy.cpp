// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"


// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	RootComponent = Mesh;
	Target->AttachTo(GetRootComponent());
	UStaticMesh* StaticMesh = Mesh->GetStaticMesh();
	//FBoxSphereBounds LocalBound = StaticMesh->GetBounds();
	//float x = LocalBound.GetBox().GetSize().X;	
	auto TargetTransform = FTransform(FRotator(0,90, 180),FVector(60,0,0));

	Target->SetRelativeTransform(TargetTransform);
	HP = 100;
	attackPower = 10;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Target->SetVisibility(false);

}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::RecieveDamage(float damage)
{
	HP -= damage;
	if (HP <= 0)
		DestroyEnemy();
}

void AEnemy::DestroyEnemy()
{
	//AActor Char = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

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
