// Fill out your copyright notice in the Description page of Project Settings.


#include "EggRoller.h"
#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "../WolfAndEggs.h"

FOnEggOut AEggRoller::NotifyOnEggOut;

EWECornerDirection AEggRoller::BasketDirecitonCurrent = static_cast<EWECornerDirection>(WE_DEFAULT_BASKET_DIRECTION);

// Sets default values
AEggRoller::AEggRoller()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComp;

	for (int i = 0; i < WE_EGG_ROLLER_NUM; i++)
	{
		UPaperSpriteComponent* SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(FName(TEXT("EggState_") + FString::FromInt(i)));
		SpriteComp->SetupAttachment(RootComponent);

		// try to find egg sprite
		static ConstructorHelpers::FObjectFinder<UPaperSprite> EggSprite(TEXT("/Game/Assets/egg/egg_Sprite.egg_Sprite"));
		if (EggSprite.Succeeded())
		{
			SpriteComp->SetSprite(EggSprite.Object);
			
			FVector2D SpriteSize = SpriteComp->GetSprite()->GetSourceSize(); // add little offset for easier bp offset configuration
			FVector Offset = FVector(1.0f * SpriteSize.X * i, 0.0f, 0.0f);
			SpriteComp->AddLocalOffset(Offset);
		}
		
		SpriteComponents.Add(SpriteComp);
	}

	// defaults
	PushEggTime = 1.0f;
	bActivateOnSpawn = true;
	bShouldAddEggOnSpawn = true;
	EggRollerPosition = EWECornerDirection::TopLeft;
}

// Called when the game starts or when spawned
void AEggRoller::BeginPlay()
{
	Super::BeginPlay();

	for (auto& Sprite : SpriteComponents)
	{
		Sprite->SetVisibility(false);
	}

	if (bActivateOnSpawn)
	{
		AddEgg();
		Activate(true);
	}
}

void AEggRoller::Activate(bool bActivate)
{
	if (bActivate)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_EggPush);
		GetWorldTimerManager().SetTimer(TimerHandle_EggPush, this, &AEggRoller::PushEgg, PushEggTime, false);
	}
	else
	{
		TimerHandle_EggPush.Invalidate();
	}

	bIsActive = bActivate;
}

void AEggRoller::SetPushEggTime(float NewTime, bool bImmediately)
{
	PushEggTime = NewTime;

	if (bImmediately)
	{
		// reset timer
		Activate(true);
	}
}

void AEggRoller::AddEgg()
{
	UPaperSpriteComponent* FirstEggSlot = SpriteComponents[0];
	ensure(FirstEggSlot);

	if (FirstEggSlot->IsVisible())     // first slot is occupied, shift all
	{
		ShiftEggs();
	}

	FirstEggSlot->SetVisibility(true); // add egg to first slot
}

void AEggRoller::ShiftEggs()
{
	for (int32 i = SpriteComponents.Num() - 1; i != 0; --i)
	{
		UPaperSpriteComponent* NextEggSlot = SpriteComponents[i];
		ensure(NextEggSlot);
		UPaperSpriteComponent* PrevEggSlot = SpriteComponents[i - 1];
		ensure(PrevEggSlot);

		NextEggSlot->SetVisibility(PrevEggSlot->IsVisible());
	}
}

void AEggRoller::TryToCatchEgg()
{
	UPaperSpriteComponent* LastEggSlot = SpriteComponents[SpriteComponents.Num() - 1];
	ensure(LastEggSlot);

	if (LastEggSlot->IsVisible())                                       // last slot has egg?
	{
		if (BasketDirecitonCurrent == EggRollerPosition)                // catch egg
		{
			NotifyOnEggOut.Broadcast(this, EggRollerPosition, true);

			// Debug
			if (GEngine)
			{
				FString Msg = FString::Printf(TEXT("[EggRoller] Egg catched! roller id: %d"), 
					static_cast<uint8>(EggRollerPosition));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Msg);
			}
		}
		else                                                            // let egg fall 
		{
			NotifyOnEggOut.Broadcast(this, EggRollerPosition, false);

			// Debug
			if (GEngine)
			{
				FString Msg = FString::Printf(TEXT("[EggRoller] Egg falls! roller id: %d"), 
					static_cast<uint8>(EggRollerPosition));
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Msg);
			}
		}

		LastEggSlot->SetVisibility(false);                              // clear last egg slot
	}
}

void AEggRoller::PushEgg()
{
	TryToCatchEgg();
	ShiftEggs();

	// continue egg push loop
	if (bIsActive)
	{
		Activate(true);
	}
}

void AEggRoller::OnWolfBasketDirectionChange(AWEWolf* Wolf, EWECornerDirection BasketDirection)
{
	BasketDirecitonCurrent = BasketDirection;

	TryToCatchEgg();  // try to catch egg instant
}
