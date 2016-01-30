// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Urn_Based.h"
#include "Urn_BasedGameMode.h"
#include "Urn_BasedPlayerController.h"
#include "Urn_BasedCharacter.h"

AUrn_BasedGameMode::AUrn_BasedGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUrn_BasedPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}