// Fill out your copyright notice in the Description page of Project Settings.


#include "WEEggRoller.h"

#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "WEWolf.h"
#include "../WolfAndEggs.h"

FOnEggOut AWEEggRoller::NotifyOnEggOut;

EWECornerDirection AWEEggRoller::BasketDirecitonCurrent = static_cast<EWECornerDirection>(WE_DEFAULT_BASKET_DIRECTION);

// Sets default values
AWEEggRoller::AWEEggRoller()
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
	bShouldAddEggOnSpawn = false;
	EggRollerPosition = EWECornerDirection::TopLeft;
}

// Called when the game starts or when spawned
void AWEEggRoller::BeginPlay()
{
	Super::BeginPlay();

	// subscribe to basket change direction
	DelegateHandle_BasketDirectionChange = AWEWolf::NotifyOnBasketDirectionChange.AddUObject(this, &AWEEggRoller::OnWolfBasketDirectionChange);

	for (auto& Sprite : SpriteComponents)
	{
		Sprite->SetVisibility(false);
	}

	if (bActivateOnSpawn)
	{
		
		Activate(true);
	}

	if (bShouldAddEggOnSpawn)
	{
		AddEgg();
	}
}

void AWEEggRoller::BeginDestroy()
{
	Super::BeginDestroy();

	// unsubscribe from basket change direction
	if (DelegateHandle_BasketDirectionChange.IsValid())
	{
		AWEWolf::NotifyOnBasketDirectionChange.Remove(DelegateHandle_BasketDirectionChange);
	}
}

void AWEEggRoller::Activate(bool bActivate)
{
	if (bActivate)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle_EggPush);
		GetWorldTimerManager().SetTimer(TimerHandle_EggPush, this, &AWEEggRoller::PushEgg, PushEggTime, false);
	}
	else
	{
		TimerHandle_EggPush.Invalidate();
	}

	bIsActive = bActivate;
}

void AWEEggRoller::SetPushEggTime(float NewTime, bool bImmediately)
{
	PushEggTime = NewTime;

	if (bImmediately)
	{
		// reset timer
		Activate(true);
	}
}

void AWEEggRoller::AddEgg()
{
	UPaperSpriteComponent* FirstEggSlot = SpriteComponents[0];
	ensure(FirstEggSlot);

	if (FirstEggSlot->IsVisible())     // first slot is occupied, shift all
	{
		ShiftEggs();
	}

	FirstEggSlot->SetVisibility(true); // add egg to first slot
}

void AWEEggRoller::ShiftEggs()
{
	for (int32 i = SpriteComponents.Num() - 1; i != 0; --i)
	{
		UPaperSpriteComponent* NextEggSlot = SpriteComponents[i];
		ensure(NextEggSlot);
		UPaperSpriteComponent* PrevEggSlot = SpriteComponents[i - 1];
		ensure(PrevEggSlot);

		NextEggSlot->SetVisibility(PrevEggSlot->IsVisible());
		PrevEggSlot->SetVisibility(false);
	}
}

void AWEEggRoller::TryToCatchEgg(bool bAllowEggDrop)
{
	UPaperSpriteComponent* LastEggSlot = SpriteComponents[SpriteComponents.Num() - 1];
	ensure(LastEggSlot);

	if (LastEggSlot->IsVisible())                                       // last slot has egg?
	{
		if (BasketDirecitonCurrent == EggRollerPosition)                // catch egg
		{
			NotifyOnEggOut.Broadcast(this, EggRollerPosition, true);

			// Debug
			FString Msg = FString::Printf(TEXT("[EggRoller] Egg catched! roller id: %d"),
				static_cast<uint8>(EggRollerPosition));

			/*if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Msg);
			}*/

			UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
		}
		else                                                            // let egg fall if allowed
		{
			if (bAllowEggDrop)
			{
				NotifyOnEggOut.Broadcast(this, EggRollerPosition, false);

				// Debug
				FString Msg = FString::Printf(TEXT("[EggRoller] Egg falls! roller id: %d"),
					static_cast<uint8>(EggRollerPosition));

				/*if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, Msg);
				}*/

				UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
			}
		}

		LastEggSlot->SetVisibility(false);                              // clear last egg slot
	}
}

void AWEEggRoller::PushEgg()
{
	TryToCatchEgg(true);
	ShiftEggs();

	// continue egg push loop
	if (bIsActive)
	{
		Activate(true);
	}
}

void AWEEggRoller::OnWolfBasketDirectionChange(AWEWolf* Wolf, EWECornerDirection BasketDirection)
{
	/*// Debug
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[EggRoller] OnBasketDirectionChange NewDirection: %d"), static_cast<uint8>(BasketDirection));
		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Yellow, Msg);
	}*/

	BasketDirecitonCurrent = BasketDirection;

	TryToCatchEgg(false);  // try to catch egg instant
}
