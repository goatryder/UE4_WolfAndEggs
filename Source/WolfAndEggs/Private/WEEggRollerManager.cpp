// Fill out your copyright notice in the Description page of Project Settings.


#include "WEEggRollerManager.h"

#include "Kismet/GameplayStatics.h"

#include "WEEggRoller.h"

// Sets default values
AWEEggRollerManager::AWEEggRollerManager()
{
	PrimaryActorTick.bCanEverTick = false;
	bIsActivated = false;
}

// Called when the game starts or when spawned
void AWEEggRollerManager::BeginPlay()
{
	Super::BeginPlay();

	ActivateManager();
}

void AWEEggRollerManager::ActivateManager()
{
	if (bIsActivated)
	{
		return;
	}

	bIsActivated = true;

	TArray<AActor*> EggRollerArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWEEggRoller::StaticClass(), EggRollerArray);

	AWEEggRoller* TopLeftEggRoller = nullptr;
	AWEEggRoller* TopRightEggRoller = nullptr;
	AWEEggRoller* BottomLeftEggRoller = nullptr;
	AWEEggRoller* BottomRightEggRoller = nullptr;

	for (AActor*& EggRollerActor : EggRollerArray)
	{
		if (AWEEggRoller* EggRoller = Cast<AWEEggRoller>(EggRollerActor))
		{
			switch (EggRoller->EggRollerPosition)
			{
			case EWECornerDirection::TopLeft:
				if (!TopLeftEggRoller)
					TopLeftEggRoller = EggRoller;
				break;

			case EWECornerDirection::TopRight:
				if (!TopRightEggRoller)
					TopRightEggRoller = EggRoller;
				break;

			case EWECornerDirection::BottomLeft:
				if (!BottomLeftEggRoller)
					BottomLeftEggRoller = EggRoller;
				break;

			case EWECornerDirection::BottomRight:
				if (!BottomRightEggRoller)
					BottomRightEggRoller = EggRoller;
				break;

			default:
				break;
			}
		}
	}

	if (!TopLeftEggRoller)
		UE_LOG(LogTemp, Warning, TEXT("Please, place EggRoller on map with EggRollerPosition == EWECornerDirection::TopLeft"));

	if (!TopRightEggRoller)
		UE_LOG(LogTemp, Warning, TEXT("Please, place EggRoller on map with EggRollerPosition == EWECornerDirection::TopRight"));

	if (!BottomLeftEggRoller)
		UE_LOG(LogTemp, Warning, TEXT("Please, place EggRoller on map with EggRollerPosition == EWECornerDirection::BottomLeft"));

	if (!BottomRightEggRoller)
		UE_LOG(LogTemp, Warning, TEXT("Please, place EggRoller on map with EggRollerPosition == EWECornerDirection::BottomRight"));

	EggRollers = FCornerEggRollers(TopLeftEggRoller, TopRightEggRoller, BottomLeftEggRoller, BottomRightEggRoller);
}

void AWEEggRollerManager::SpawnEgg(EWECornerDirection CornerDirection)
{
	AWEEggRoller* EggRoller = EggRollers.GetEggRoller(CornerDirection);

	if (EggRoller)
	{
		EggRoller->AddEgg();

		// Debug
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("[EggRollerManager] EggSpawned for '%d' Egg Roller"), 
				static_cast<uint8>(EggRoller->EggRollerPosition));
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Orange, Msg);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[EggRollermanager] %s can't spawn egg, egg roller with direction %d is null"),
			*GetName(), static_cast<uint8>(CornerDirection));
	}
}
