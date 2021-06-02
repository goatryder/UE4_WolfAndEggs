// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "../WETypes.h"

#include "WEGameModeA.generated.h"

/**
* [GameMode A] 
*
*  will spawn eggs, player should catch them
* 
* 
* [Spawn]
* 
*  Eggs will spawn randomly from one active roller at time (A has 3 rollers, B has 4 rollers)
*
* [Speed]
* 
*  Game Speed Should be clamped to some "SpeedMin" "SpeedMax" val
* 
*  Game Starts with "SpeedMin" val
*
*  Game Speed icrements linearly with some const float value - "SpeedFracture" after each egg collect
*
* [Score]
*  When Player Pickup Egg, "Score" increment
* 
*  When "Score" is 200 or 500 we get restore our "HP" and game speed decrese on "SpeedFracture" * 0.5 * 200 and "SpeedFracture" * 0.5 * 500 respectively
* 
*  Score is Clamped between 0 and 999
* 
* each egg catch we try to update max score for gameMode
* 
*  [HP]
* 
* rabit should be active for some "Rabbit Time"
* rabbit should spawn on random between "RabbitShowTimeMin", "RabbitShowTimeMax"
* 
*  When Player Let Egg fall, player life:
*       case1: rabbit is active     - player loose 1 "HP"
*       case2: rabbit is not active - player loose 2 "HP"
* 
*  Game Start with 6 "HP"
*      When "HP" == 6                unused roller is BottomLeft
*      When "HP" == 5 or "HP" = 4    unused roller is BottomRight
*      When "HP" == 3 or "HP" == 2   unused roller is TopLeft
*      When "HP" == 1                unused roller is TopRight
*      When "HP" == 0                game over
*
* [Start]
* 
*  On Start Should pick game mode
* 
*  Game can be Paused
* 
* [Keys]
* 
* // todo need game instance.
* 
* Movement x8 keys (full and partial)
* Pause
* GameA/GameB - when pressed - show record. when released - play GameA/GameB
* 
* 
* [GameMode B]
* 
*
* All above, but: 
* eggs spawns from all rollers
* Inital Game Speed is "SpeedMin" + "SpeedMax" * 0.5
*/

UCLASS()
class WOLFANDEGGS_API AWEGameModeA : public AGameMode
{
	GENERATED_BODY()

public:

	AWEGameModeA();

	virtual void StartPlay() override;
	virtual void BeginDestroy() override;
	virtual void EndMatch() override;

protected:
	
	virtual void BeginPlay() override;

	class AWEEggRollerManager* EggRollerManager;
	
	/** Lifes from game start, max possible amount */
	uint32 DefaultLifeNum;
	
	/** Current Player Lifes */
	uint32 CurrentLifeNum;

	/** Current Game Player Score, will be modulo div on WolfAndEggs.h WE_MAX_SCORE, 
	 * but actual max score will be written to GameState max score*/
	uint32 CurrentScoreNum;

	/** Increment Current Score Num with clamp max */
	void IncrCurrentScoreNum();

	/** Decrementing Current life num with clamp */
	void DecrCurrentLifeNum();

	/** Check loose condition, called after egg fall */
	void CheckLoose() { if (CurrentLifeNum == 0) EndMatch(); }

	/** Custom GameState ref */
	class AWEGameState* CustomGameState;

	// todo rabbit handle show/hide
	/** If Rabbit Is Active then on egg crack we loose 1 hp, if he not active we will loose 2 hp */
	bool bRabbitIsActive;

	/** Change Egg Spawn Time. Called after each Score Increment */
	void DecrementSpawnTime();

	/** Limit SpawnTimeMin */
	UPROPERTY(EditDefaultsOnly, Category = "GameModeA: Egg Spawn")
		float SpawnTimeLimitMin;

	/** Limit SpawnTimeMax */
	UPROPERTY(EditDefaultsOnly, Category = "GameModeA: Egg Spawn")
		float SpawnTimeLimitMax;

	/** Will be spawn egg on random position in rand range [SpawnTimeMin SpawnTimeMax] */
	UPROPERTY(EditDefaultsOnly, Category = "GameModeA: Egg Spawn")
		float SpawnTimeMin;

	/** Will be spawn egg on random position in rand range [SpawnTimeMin SpawnTimeMax] */
	UPROPERTY(EditDefaultsOnly, Category = "GameModeA: Egg Spawn")
		float SpawnTimeMax;

	/** Value On Which we Decrement SpawnTimeMin and SpawnTimeMax on each egg collected */
	UPROPERTY(EditDefaultsOnly, Category = "GameModeA: Egg Spawn")
		float SpawnTimeDecrement;

	FTimerHandle TimerHandle_SpawnEgg;

	/** Handle Egg spawn */
	UFUNCTION()
		void SpawnEggRand();

public:
	
	/** Observer on AWEEggRoller NotifyOnEggOut */
	UFUNCTION()
		void OnEggOutObserver(class AWEEggRoller* EggRoller, EWECornerDirection RollerPosition, bool bIsCached);

	uint32 GetDefaultLifeNum() { return DefaultLifeNum; }
	uint32 GetCurrentLifeNum() { return CurrentLifeNum; }

private:

	/** OnEggOut Delegate Handle ref */
	class FDelegateHandle DelegateHandle_OnEggOut;
};
