// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "WEGameState.generated.h"

/**
 * 
 */
UCLASS()
class WOLFANDEGGS_API AWEGameState : public AGameState
{
	GENERATED_BODY()

	AWEGameState();

protected:

	/** Store best score for GameModeA */
	uint32 ScoreGameAMax;

	/** Store best score for GameModeB */
	uint32 ScoreGameBMax;

	UPROPERTY(EditDefaultsOnly, Category = "WolfAndEggs")
		FName GameAMapName;

	UPROPERTY(EditDefaultsOnly, Category = "WolfAndEggs")
		FName GameBMapName;

	/** true - current game A, false - current game B */
	bool bIsCurrentGameA;

public:

	void RunGameA();
	void RunGameB();

	uint32 GetMaxScoreGameA() const { return ScoreGameAMax; }
	uint32 GetMaxScoreGameB() const { return ScoreGameBMax; }

	/** true - current game A, false - current game B */
	bool IsCurrentGameA() const { return bIsCurrentGameA; }

	/** Try to override GamemodeA Max score */
	void UpdateScoreGameAMax(uint32 Score);

	/** Try to override GamemodeB Max score */
	void UpdateScoreGameBMax(uint32 Score);

};
