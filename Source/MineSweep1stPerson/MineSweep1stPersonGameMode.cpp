// Copyright Epic Games, Inc. All Rights Reserved.

#include "MineSweep1stPersonGameMode.h"
#include "MineSweep1stPersonCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMineSweep1stPersonGameMode::AMineSweep1stPersonGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
