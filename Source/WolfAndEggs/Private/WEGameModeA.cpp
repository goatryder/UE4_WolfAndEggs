// Fill out your copyright notice in the Description page of Project Settings.


#include "WEGameModeA.h"

#include "Kismet/Gameplaystatics.h"

#include "WEWolf.h"
#include "WEWolfPlayerController.h"
#include "WolfAndEggsHUD.h"
#include "WEEggRollerManager.h"
#include "../WolfAndEggs.h"
#include "WeGameState.h"
#include "WEEggRoller.h"


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

	// use our custom Game State Class
	GameStateClass = AWEGameState::StaticClass();

	// defaults
	DefaultLifeNum = WE_MAX_LIFES;
	CurrentLifeNum = DefaultLifeNum;
	CurrentScoreNum = 0;
	bRabbitIsActive = false;
}

void AWEGameModeA::BeginPlay()
{
	Super::BeginPlay();

	// get custom game state ref
	CustomGameState = GetGameState<AWEGameState>();
	ensure(CustomGameState);

	// subscribe to NotifyOnEggOut
	DelegateHandle_OnEggOut = AWEEggRoller::NotifyOnEggOut.AddUObject(this, &AWEGameModeA::OnEggOutObserver);
}

void AWEGameModeA::BeginDestroy()
{
	Super::BeginDestroy();

	// unsubscribe from NotifyOnEggOut
	if (DelegateHandle_OnEggOut.IsValid())
	{
		AWEEggRoller::NotifyOnEggOut.Remove(DelegateHandle_OnEggOut);
	}
}

void AWEGameModeA::EndMatch()
{
	Super::EndMatch();
}

void AWEGameModeA::StartPlay()
{
	Super::StartPlay();


	// try to get EggRollerManager from game scene
	EggRollerManager = Cast<AWEEggRollerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWEEggRollerManager::StaticClass()));

	if (EggRollerManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameMode A] On StartPlay() EggRollerManager on current map successfully finded!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameMode A] Can't find EggRollerManager on current map, please add one!"));
		ensure(EggRollerManager);

	}

	// reset lifes
	CurrentLifeNum = DefaultLifeNum;

	// reset score
	CurrentScoreNum = 0;
}

void AWEGameModeA::SpawnEggRand()
{
}

void AWEGameModeA::OnEggOutObserver(AWEEggRoller* EggRoller, EWECornerDirection RollerPosition, bool bIsCached)
{
	if (bIsCached)            // increment score
	{
		IncrCurrentScoreNum();
	}
	else                      // decrement life
	{
		DecrCurrentLifeNum();
	}
}

void AWEGameModeA::DecrCurrentLifeNum()
{
	uint32 NewLifeNum = CurrentLifeNum;

	// calc rabbit active factor
	if (bRabbitIsActive)
	{
		NewLifeNum--;
	}
	else
	{
		NewLifeNum -= 2;
	}

	// clamp
	if (NewLifeNum > DefaultLifeNum)
	{
		CurrentLifeNum = DefaultLifeNum;
	}
	else if (NewLifeNum < 0)
	{
		CurrentLifeNum = 0;
	}
	else
	{
		CurrentLifeNum = NewLifeNum;
	}

	// check loose condition
	CheckLoose();
}

void AWEGameModeA::IncrCurrentScoreNum()
{
	uint32 NewScore = ++CurrentScoreNum;

	// try to override total record:
	ensure(CustomGameState);
	CustomGameState->UpdateScoreGameAMax(NewScore);
	
	// Handle New Egg Spawn Time
	DecrementSpawnTime();

	// if score > then max score, use modulo div
	CurrentScoreNum = NewScore % (WE_MAX_SCORE + 1);
}

void AWEGameModeA::DecrementSpawnTime()
{
	// todo
}
