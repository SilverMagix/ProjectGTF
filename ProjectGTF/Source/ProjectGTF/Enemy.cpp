// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "GTFPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/StaticMesh.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"


// Sets default values
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	Target = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Target"));
	MovComp = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovComp"));





	RootComponent = Collider;
	//Collider->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel1,ECollisionResponse::ECR_Block);
	Mesh->AttachToComponent(Collider, FAttachmentTransformRules::KeepRelativeTransform);
	Target->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);

}



// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	//Reset Values
	Target->SetVisibility(false);
	LocationToGo = GetActorLocation();
	//Find Player
	TSubclassOf<AGTFPlayer> playerRef = AGTFPlayer::StaticClass();
	Player = Cast<AGTFPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), playerRef));


}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsDead) {
		return;
	}
	if (Player) {
		if (Player->bIsAttacking) {
			//Go Slow mode when Player attacks
			MovComp->MaxSpeed = 25;


		}
		else {

			MovComp->MaxSpeed = 400;
		}
	}

	if (bIsGettingHit) {
		print("Getting recoiled", 4);
		SetActorLocation(FMath::VInterpTo(GetActorLocation(), LocationToGo, DeltaTime, 2));
	}

	if (bIsGettingHit) {
		if (RecoilTimer < RecoilTime) {
			RecoilTimer += DeltaTime;
		}
		else {
			bIsGettingHit = false;
			RecoilTimer = 0;
		}
	}

	if (DumbTimer < 4) {
		DumbTimer += DeltaTime;

	}

}



bool AEnemy::IsDead(float damage)
{
	bIsGettingHit = true;
	damage = damage / (Defense + 1);
	Hp -= damage;
	if (Hp <= 0) {

		DestroyEnemy();
		print("Enemy dead", -1);
		return bIsDead = true;
	}
	DumbTimer = 0;
	print("Enemy recieving Damage", -1);
	return bIsDead = false;
}

void AEnemy::Push(FVector playerLocation, FVector impulse) {
	DumbTimer = 0;
	bIsGettingHit = true;
	LocationToGo = (GetActorLocation() + impulse * RecoilSpeed);
	LocationToGo.Z = playerLocation.Z;


}

void AEnemy::DestroyEnemy()
{
	Controller->StopMovement();
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
