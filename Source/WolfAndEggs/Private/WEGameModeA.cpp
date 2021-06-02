// Fill out your copyright notice in the Description page of Project Settings.


#include "WEGameModeA.h"

#include "WEWolf.h"
#include "WEWolfPlayerController.h"
#include "WolfAndEggsHUD.h"

AWEGameModeA::AWEGameModeA()
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