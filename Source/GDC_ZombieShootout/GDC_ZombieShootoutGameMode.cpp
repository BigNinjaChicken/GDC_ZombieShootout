// Copyright Epic Games, Inc. All Rights Reserved.

#include "GDC_ZombieShootoutGameMode.h"
#include "GDC_ZombieShootoutCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGDC_ZombieShootoutGameMode::AGDC_ZombieShootoutGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
