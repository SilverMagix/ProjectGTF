// Fill out your copyright notice in the Description page of Project Settings.

#include "WalkingEnemy.h"



void AWalkingEnemy::BeginPlay()
{
	Super::BeginPlay();
	Controller = Cast<AEnemyController>(GetController());
}

void AWalkingEnemy::Tick(float DeltaTime)
{
		Super::Tick(DeltaTime);

		if (Player) {
			
			
			if (FVector::Distance(GetActorLocation(), Player->GetActorLocation()) < 1000 && !bIsGettingHit &&!bIsDead && DumbTimer > 3) {
				print("Close Enough",9);
				Controller->MoveToActor(Player,-1,false);
				
				print("Started Movement", 5);
			}
			else {
				Controller->StopMovement();
				print("Stopped Movement", 5);
			}
		}
		
	
}