// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Dungeon_Assault_UE4GameMode.h"
#include "UObject/ConstructorHelpers.h"

ADungeon_Assault_UE4GameMode::ADungeon_Assault_UE4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/Blueprints/DA_Character_BP")); 
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}