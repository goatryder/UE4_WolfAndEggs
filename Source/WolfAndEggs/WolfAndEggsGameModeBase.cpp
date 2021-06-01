// Copyright Epic Games, Inc. All Rights Reserved.


#include "WolfAndEggsGameModeBase.h"

#include "Public/WEWolf.h"
#include "Public/WEWolfPlayerController.h"
#include "Public/WolfAndEggsHUD.h"

AWolfAndEggsGameModeBase::AWolfAndEggsGameModeBase()
{
	// PrimaryActorTick.bCanEverTick = true;

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/_WolfAndEggs/Blueprints/BP_Wolf"));
	if (PlayerPawnClassFinder.Succeeded())
		DefaultPawnClass = PlayerPawnClassFinder.Class;
	else
		DefaultPawnClass = AWEWolf::StaticClass();

	// use our custom Player Controller class
	PlayerControllerClass = AWEWolfPlayerController::StaticClass();

	// use our custom HUD class
	HUDClass = AWolfAndEggsHUD::StaticClass();
}
