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

	// defaults GameModeA
	bEggSpawnActive = false;
	DefaultLifeNum = WE_MAX_LIFES;
	CurrentLifeNum = DefaultLifeNum;
	CurrentScoreNum = 0;
	bRabbitIsActive = false;
	EggSpawnTimer = FWEGameRandTimer(0.33f, 3.0f, 2.0f, 3.0f, 0.05f);
	EggRollTimeClampMin = 0.33f;
	EggRollTimeClampMax = 2.0f;
	EggRollTime = 2.0f;
	EggRollTimeDecrementFracture = 0.05f;
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
	
	// Debug 
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Cyan, TEXT("[GameModeA] EndMatch"));
	UE_LOG(LogTemp, Warning, TEXT("[%s] EndMatch()"), *StaticClass()->GetFName().ToString());
}

void AWEGameModeA::StartPlay()
{
	Super::StartPlay();

	// try to get EggRollerManager from game scene
	EggRollerManager = Cast<AWEEggRollerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AWEEggRollerManager::StaticClass()));

	if (EggRollerManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] On StartPlay() EggRollerManager on current map successfully finded!"), *StaticClass()->GetFName().ToString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[%s] Can't find EggRollerManager on current map, please add one!"), *StaticClass()->GetFName().ToString());
		ensure(EggRollerManager);

	}

	// reset lifes
	CurrentLifeNum = DefaultLifeNum;

	// reset score
	CurrentScoreNum = 0;

	// set egg roll time
	EggRollTime = FMath::Clamp(EggRollTime, EggRollTimeClampMin, EggRollTimeClampMax);
	EggRollerManager->SetEggRollersShiftTime(EggRollTime);

	// spawn egg loop run
	ActivateSpawnEggTimer(true);

	// Debug
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[%s] StartPlay"), *StaticClass()->GetFName().ToString());
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Msg);
	}
	UE_LOG(LogTemp, Warning, TEXT("[%s] On StartPlay()"), *StaticClass()->GetFName().ToString());
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
	if (CurrentLifeNum == 0)
	{
		return;
	}

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

	// Debug
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, *FString::Printf(TEXT("[GameModeA] Egg fall Lifes Num: %d"), CurrentLifeNum));

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
	if (CurrentScoreNum == 199)
	{
		EggSpawnTimer.DecreaseTime(-100.0f);  // easing, increase time on half of what already decreased
		CurrentLifeNum = DefaultLifeNum;

		UE_LOG(LogTemp, Warning, TEXT("[%s] On Score 199 Time Easing, Life Restore"), *StaticClass()->GetFName().ToString());
	}
	else if (CurrentScoreNum == 499)
	{
		EggSpawnTimer.DecreaseTime(-250.0f + 100.0f);  // easing, increase time on half of what already decreased
		CurrentLifeNum = DefaultLifeNum;

		UE_LOG(LogTemp, Warning, TEXT("[%s] On Score 499 Time Easing, Life Restore"), *StaticClass()->GetFName().ToString());
	}
	else
	{
		EggSpawnTimer.DecreaseTime(1.0);
	}
	
	// update egg rollers shift time
	UpdateEggRollTime();

	// if score > then max score, use modulo div
	CurrentScoreNum = NewScore % (WE_MAX_SCORE + 1);
}

void AWEGameModeA::UpdateEggRollTime()
{
	ensure(EggRollerManager);

	EggRollTime = FMath::Clamp(EggRollTime, EggRollTimeClampMin, EggRollTimeClampMax);

	EggRollerManager->SetEggRollersShiftTime(EggRollTime);

	EggRollTime -= EggRollTimeDecrementFracture;
}

void AWEGameModeA::ActivateSpawnEggTimer(bool bActivate)
{
	if (bActivate)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_SpawnEgg);
		GetWorldTimerManager().SetTimer(TimerHandle_SpawnEgg, this,
			&AWEGameModeA::SpawnEggRandPos, EggSpawnTimer.GetRandTime(), false);
	}
	else
	{
		TimerHandle_SpawnEgg.Invalidate();
	}

	bEggSpawnActive = bActivate;
}

void AWEGameModeA::SpawnEggRandPos()
{
	ensure(EggRollerManager);

	EWECornerDirection UnusedRollerDirection = EWECornerDirection::TopLeft;

	// GameA has one unused roller, which is changing depending on Current Life value
	switch (CurrentLifeNum)
	{
	case 1:
		UnusedRollerDirection = EWECornerDirection::TopRight;
		break;
	
	case 2:
	case 3:
		UnusedRollerDirection = EWECornerDirection::TopLeft;
		break;
	
	case 4:
	case 5:
		UnusedRollerDirection = EWECornerDirection::BottomRight;
		break;
	
	case 6:
		UnusedRollerDirection = EWECornerDirection::BottomLeft;
		break;

	default:
		break;
	}

	// select random spawn
	TArray<EWECornerDirection> EggRollersDirectionsPickFrom;

	for (auto& EggRollerPair : EggRollerManager->EggRollers.EggRollers)
	{
		if (EggRollerPair.Value && EggRollerPair.Key != UnusedRollerDirection)
		{
			EggRollersDirectionsPickFrom.Add(EggRollerPair.Key);
		}
	}
	
	uint32 RandIndex = FMath::Rand() % EggRollersDirectionsPickFrom.Num();
	EWECornerDirection RandSpawnDirection = EggRollersDirectionsPickFrom[RandIndex];

	// spawn egg
	EggRollerManager->SpawnEgg(RandSpawnDirection);

	// continue egg spawn loop
	if (bEggSpawnActive)
	{
		ActivateSpawnEggTimer(true);
	}

	FString Msg = FString::Printf(
		TEXT("[%s] SpawnRandEgg from roller: %d, unusedRoller: %d, score: %d, lifes: %d, spawnTime: %f, rollTime: %f"),
		*StaticClass()->GetFName().ToString(), static_cast<uint8>(RandSpawnDirection), static_cast<uint8>(UnusedRollerDirection),
		CurrentScoreNum, CurrentLifeNum, EggSpawnTimer.LastTimeCache, EggRollTime
	);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);

	// Debug
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Green, Msg);
	}
}