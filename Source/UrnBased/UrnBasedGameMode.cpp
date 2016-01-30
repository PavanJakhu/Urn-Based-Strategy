// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "UrnBased.h"
#include "UrnBasedGameMode.h"
#include "UrnBasedPlayerController.h"
#include "UrnBasedCharacter.h"

AUrnBasedGameMode::AUrnBasedGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// use our custom PlayerController class
	PlayerControllerClass = AUrnBasedPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}