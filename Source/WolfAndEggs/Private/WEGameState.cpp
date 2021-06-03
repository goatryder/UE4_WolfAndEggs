// Fill out your copyright notice in the Description page of Project Settings.


#include "WEGameState.h"
#include "../WolfAndEggs.h"
#include "Kismet/GameplayStatics.h"

AWEGameState::AWEGameState()
{
	// defaults
	ScoreGameAMax = 0;
	ScoreGameBMax = 0;

	GameAMapName = FName("MapGameA");
	GameBMapName = FName("MapGameB");
	
	bIsCurrentGameA = true;
}

void AWEGameState::RunGameA()
{
	UGameplayStatics::OpenLevel((UObject*)this, GameAMapName);
	bIsCurrentGameA = true;
}

void AWEGameState::RunGameB()
{
	UGameplayStatics::OpenLevel((UObject*)this, GameBMapName);
	bIsCurrentGameA = false;
}

void AWEGameState::UpdateScoreGameAMax(uint32 Score)
{
	if (Score > ScoreGameAMax)
	{
		if (Score > WE_MAX_SCORE)
		{
			ScoreGameAMax = WE_MAX_SCORE;
		}
		else
		{
			ScoreGameAMax = Score;
		}
	}
}

void AWEGameState::UpdateScoreGameBMax(uint32 Score)
{
	if (Score > ScoreGameBMax)
	{
		if (Score > WE_MAX_SCORE)
		{
			ScoreGameBMax = WE_MAX_SCORE;
		}
		else
		{
			ScoreGameBMax = Score;
		}
	}
}
