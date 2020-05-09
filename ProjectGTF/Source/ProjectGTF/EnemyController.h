// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UEnemyPathFollowComp.h"
#include "GTFPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyController.generated.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

/**
 *
 */
UCLASS()
class PROJECTGTF_API AEnemyController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
