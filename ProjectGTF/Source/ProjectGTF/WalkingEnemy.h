// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "GTFPlayer.h"
#include "EnemyController.h"
#include "WalkingEnemy.generated.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

/**
 *
 */
UCLASS()
class PROJECTGTF_API AWalkingEnemy : public AEnemy
{
	GENERATED_BODY()

private:

	AEnemyController* Controller;

public:
	AWalkingEnemy(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer) {};


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
