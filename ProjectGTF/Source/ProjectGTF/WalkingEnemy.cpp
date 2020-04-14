// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkingEnemy.h"


void AWalkingEnemy::EnemyMove()
{


	FVector PlayerPosition = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();
	if ((FMath::Abs(PlayerPosition.Z - GetActorLocation().Z) < 200) &&
		(FMath::Abs(PlayerPosition.Y - GetActorLocation().Y) < 1000) && !bIsGettingHit) {
		
		LocationToGo = PlayerPosition;
		LocationToGo.Z = GetActorLocation().Z;
		CurrentSpeed = Speed;
		print("Moving Enemy at " + LocationToGo.ToString(), 19);
	}



}


void AWalkingEnemy::Tick(float DeltaTime)
{
	EnemyMove();
	AEnemy::Tick(DeltaTime);

}