// Fill out your copyright notice in the Description page of Project Settings.


#include "WELifesDisplay.h"

#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "../WolfAndEggs.h"

// Sets default values
AWELifesDisplay::AWELifesDisplay()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComp;

	// try to find life sprite
	static ConstructorHelpers::FObjectFinder<UPaperSprite> LifeSpriteOb(TEXT("/Game/Assets/loss/loss_Sprite_0.loss_Sprite_0"));

	if (LifeSpriteOb.Succeeded())
	{
		LifeSprite = LifeSpriteOb.Object;
	}

	float SpriteOffsetX = 34.0f;

	if (LifeSprite)
	{
		SpriteOffsetX = LifeSprite->GetSourceSize().X;
	}

	for (int32 i = 0; i < WE_MAX_LIFES / 2; i++)
	{
		UPaperSpriteComponent* SpriteComp = CreateDefaultSubobject<UPaperSpriteComponent>(
			FName(TEXT("SpriteLife_") + FString::FromInt(i)));
		SpriteComp->SetupAttachment(RootComponent);
		SpriteComp->AddLocalOffset(FVector(-i * SpriteOffsetX, 0.0f, 0.0f));

		if (LifeSprite)
		{
			SpriteComp->SetSprite(LifeSprite);
		}

		LifeSpriteComps.Add(SpriteComp);
	}
}

// Called when the game starts or when spawned
void AWELifesDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void AWELifesDisplay::SetCurrentLife(uint32 LifeNum)
{
	for (auto& SpriteComp : LifeSpriteComps)
	{
		SpriteComp->SetVisibility(false);
	}

	switch (LifeNum)
	{
	case 6:
		LifeSpriteComps[0]->SetVisibility(true);
		LifeSpriteComps[1]->SetVisibility(true);
		LifeSpriteComps[2]->SetVisibility(true);
		break;

	case 5:
	case 4:
		LifeSpriteComps[0]->SetVisibility(true);
		LifeSpriteComps[1]->SetVisibility(true);
		LifeSpriteComps[2]->SetVisibility(false);
		break;

	case 3:
	case 2:
		LifeSpriteComps[0]->SetVisibility(true);
		LifeSpriteComps[1]->SetVisibility(false);
		LifeSpriteComps[2]->SetVisibility(false);
		break;

	default:
		break;
	}

	// Debug
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[WELifesDisplay] SetCurrentLife %d"), LifeNum);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Msg);

	}
}
