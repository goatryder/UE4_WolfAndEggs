// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../WETypes.h"
#include "WEEggRollerManager.generated.h"

class AWEEggRoller;

/**
 * Level Corner EggRollers ptr holder struct
 */
USTRUCT(BlueprintType)
struct FCornerEggRollers
{
	GENERATED_BODY()

	FCornerEggRollers() {}
	FCornerEggRollers(AWEEggRoller* TopLeft, AWEEggRoller* TopRight, AWEEggRoller* BottomLeft, AWEEggRoller* BottomRight)
	{
		EggRollers.Add(EWECornerDirection::TopLeft, TopLeft);
		EggRollers.Add(EWECornerDirection::TopRight, TopRight);
		EggRollers.Add(EWECornerDirection::BottomLeft, BottomLeft);
		EggRollers.Add(EWECornerDirection::BottomRight, BottomRight);
	}

	virtual ~FCornerEggRollers() {}
	
	UPROPERTY(BlueprintReadOnly, Category = "CornerEggRollers")
		TMap<EWECornerDirection, AWEEggRoller*> EggRollers;

	AWEEggRoller* GetEggRoller(EWECornerDirection CornerDirection) 
	{
		if (EggRollers.Contains(CornerDirection))
			return EggRollers[CornerDirection];
		else
			return nullptr;
	}
};

UCLASS()
class WOLFANDEGGS_API AWEEggRollerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWEEggRollerManager();

	/** Spawn egg for chosen EggRoller */
	void SpawnEgg(EWECornerDirection CornerDirection);

	/** Get Level Egg Rollers references. */
	void ActivateManager();

protected:

	bool bIsActivated;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FCornerEggRollers EggRollers;
};
