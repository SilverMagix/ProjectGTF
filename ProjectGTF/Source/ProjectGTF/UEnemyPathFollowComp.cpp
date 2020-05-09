// Fill out your copyright notice in the Description page of Project Settings.


#include "UEnemyPathFollowComp.h"
#include <Runtime\NavigationSystem\Public\NavMesh\RecastNavMesh.h>

void UEnemyPathFollowComp::FollowPathSegment(float DeltaTime)
{
}
///WIP
//Rama's UE4 Nav code to get all the nav polys!
bool UEnemyPathFollowComp::NavPoly_GetAllPolys(TArray<NavNodeRef>& Polys)
{

	
	if (!MovementComp) return false;
	//~~~~~~~~~~~~~~~~~~

	//Get Nav Data
	const ANavigationData* NavData = EnemyGetNavData();

	const ARecastNavMesh* NavMesh = Cast<ARecastNavMesh>(NavData);
	if (!NavMesh)
	{
		return false;
	}

	TArray<FNavPoly> EachPolys;
	for (int32 v = 0; v < NavMesh->GetNavMeshTilesCount(); v++)
	{

		//CHECK IS VALID FIRST OR WILL CRASH!!! 
	   //     256 entries but only few are valid!
		// use continue in case the valid polys are not stored sequentially
		if (!TileIsValid(NavMesh, v))
		{
			continue;
		}

		NavMesh->GetPolysInTile(v, EachPolys);
	}


	//Add them all!
	for (int32 v = 0; v < EachPolys.Num(); v++)
	{
		Polys.Add(EachPolys[v].Ref);
	}
	return true;
}