// Fill out your copyright notice in the Description page of Project Settings.


#include "WEGameModeB.h"
#include "WEEggRollerManager.h"
#include "Kismet/Gameplaystatics.h"
#include "WeGameState.h"

void AWEGameModeB::EndMatch()
{
	AGameMode::EndMatch();

	AWEGameState* GS = Cast<AWEGameState>(UGameplayStatics::GetGameState(GetWorld()));
	GS->RunGameB();
}

void AWEGameModeB::SpawnEggRandPos()
{
	// select random spawn
	TArray<EWECornerDirection> EggRollersDirectionsPickFrom;

	for (auto& EggRollerPair : EggRollerManager->EggRollers.EggRollers)
	{
		EggRollersDirectionsPickFrom.Add(EggRollerPair.Key);
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
		TEXT("[%s] SpawnRandEgg from roller: %d, score: %d, lifes: %d, spawnTime: %f, rollTime: %f"),
		*StaticClass()->GetFName().ToString(), static_cast<uint8>(RandSpawnDirection),
		CurrentScoreNum, CurrentLifeNum, EggSpawnTimer.LastTimeCache, EggRollTime
	);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
}