// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/PathFollowingComponent.h"	
#include "AI/NavigationSystemBase.h"
#include "NavigationSystem.h"
#include "NavMesh/RecastNavMesh.h"
#include "UEnemyPathFollowComp.generated.h"

#define print(text, i) if (GEngine) GEngine->AddOnScreenDebugMessage(i, 1.5, FColor::White,text)

/**
 * 
 */
UCLASS()
class PROJECTGTF_API UEnemyPathFollowComp : public UPathFollowingComponent
{
	GENERATED_BODY()
public:
	///WIP
	UEnemyPathFollowComp(const FObjectInitializer& PCIP) {};


	/** follow current path segment */
	virtual void FollowPathSegment(float DeltaTime) override;

	/** sets variables related to current move segment */
	//virtual void SetMoveSegment(int32 SegmentStartIndex) override;

	/** check state of path following, update move segment if needed */
	//virtual void UpdatePathSegment() override;
	
	

	//Adapted to UE4 v4.20+ from Rama AI navigation tutorial
	FORCEINLINE const ANavigationData* EnemyGetNavData() const
	{
		const FNavAgentProperties& AgentProperties = MovementComp->GetNavAgentPropertiesRef();
		UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
		const ANavigationData* NavData = NavSystem->GetNavDataForProps(AgentProperties);
		if (!NavData)
		{
			print("ERROR USING MAIN NAV DATA",-1);
			return nullptr;
		}

		return NavData;
	}

	//VERY IMPORTANT FOR CRASH PROTECTION !!!!!
	FORCEINLINE bool TileIsValid(const ARecastNavMesh* NavMesh, int32 TileIndex) const
	{
		if (!NavMesh) return false;
		//~~~~~~~~~~~~~~
		const FBox TileBounds = NavMesh->GetNavMeshTileBounds(TileIndex);

		return TileBounds.IsValid != 0;
	}

	//add this to your custom path follow component!
	bool NavPoly_GetAllPolys(TArray<NavNodeRef>& Polys);
	
};
