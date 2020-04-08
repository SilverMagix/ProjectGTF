// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectGTFGameMode.h"
#include "GTFPlayer.h"
#include "UObject/ConstructorHelpers.h"

AProjectGTFGameMode::AProjectGTFGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Character/SpeedChar"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
