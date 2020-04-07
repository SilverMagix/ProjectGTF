// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyManager.h"
#include "Engine.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

// Sets default values
AEnemyManager::AEnemyManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<AEnemy> ClassToFind = AEnemy::StaticClass();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, EnemyList);
	print("Looking for actors", -1);
	for (AActor* a : EnemyList) {
		print(a->GetName(), -1);
	}
	
}

// Called every frame
void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

