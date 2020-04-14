// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"		
#include "UEnemyPathFollowComp.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTGTF_API UEnemyPathFollowComp : public UPathFollowingComponent
{
	GENERATED_BODY()
public:

	UEnemyPathFollowComp(const FObjectInitializer& PCIP) {};


/** follow current path segment */
	virtual void FollowPathSegment(float DeltaTime) override;

	

	
};
