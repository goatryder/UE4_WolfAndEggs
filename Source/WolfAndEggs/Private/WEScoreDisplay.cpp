// Fill out your copyright notice in the Description page of Project Settings.


#include "WEScoreDisplay.h"

#include "Components/SceneComponent.h"
#include "PaperSpriteComponent.h"
#include "PaperSprite.h"

#include "../WolfAndEggs.h"

// Sets default values
AWEScoreDisplay::AWEScoreDisplay()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComp;

	// try to find digits sprite
	for (uint32 i = 0; i < 10; i++)
	{
		FString Path = FString::Printf(TEXT("/Game/Assets/score/nums_SpriteNum_%d.nums_SpriteNum_%d"), i, i);
		static ConstructorHelpers::FObjectFinder<UPaperSprite> NumSpriteOb(*Path);

		if (NumSpriteOb.Succeeded())
		{
			SpriteNums.Add(NumSpriteOb.Object);
		}
	}
	
	// try find digit bg sprite
	static ConstructorHelpers::FObjectFinder<UPaperSprite> BGSpriteOb(TEXT("/Game/Assets/score/num-bg_Sprite.num-bg_Sprite"));
	if (BGSpriteOb.Succeeded())
	{
		SpriteNumBG = BGSpriteOb.Object;
	}

	float SpriteOffsetX = 31.0f;
	UPaperSprite* SpriteNumZero = nullptr;

	if (SpriteNums.Num() > 0 && SpriteNums[0])
	{
		SpriteNumZero = SpriteNums[0];
		SpriteOffsetX = SpriteNums[0]->GetSourceSize().X;
	}

	for (int32 i = 0; i < WE_MAX_SCORE_DISPLAY_DIGITS; i++)
	{
		UPaperSpriteComponent* SpriteCompNum = CreateDefaultSubobject<UPaperSpriteComponent>(
			FName(TEXT("SpriteCompNum_") + FString::FromInt(i)));
		SpriteCompNum->SetupAttachment(RootComponent);
		SpriteCompNum->AddLocalOffset(FVector(-i * SpriteOffsetX, 0.0f, 0.0f));
		if (SpriteNumZero)
		{
			SpriteCompNum->SetSprite(SpriteNumZero);
		}
		DigitSpriteComps.Add(SpriteCompNum);

		UPaperSpriteComponent* SpriteCompBG = CreateDefaultSubobject<UPaperSpriteComponent>(
			FName(TEXT("SpriteCompBG_") + FString::FromInt(i)));
		SpriteCompBG->SetupAttachment(SpriteCompNum);
		SpriteCompBG->SetRelativeLocation(FVector(8.0f, 8.0f, 0.0f));
		if (SpriteNumBG)
		{
			SpriteCompBG->SetSprite(SpriteNumBG);
		}
		DigitBGSpriteComps.Add(SpriteCompBG);
	}

	// defaults
	MaxScore = WE_MAX_SCORE;
	CurrentScore = 0;
}

// Called when the game starts or when spawned
void AWEScoreDisplay::BeginPlay()
{
	Super::BeginPlay();
}

void AWEScoreDisplay::SetScore(uint32 ScoreNum)
{
	uint32 Val = (ScoreNum) % 1000;

	uint32 DigitsArray[3] = { 0 };

	uint32 Index = 0;

	while (Val > 0)
	{
		DigitsArray[Index] = Val % 10;
		Val = Val / 10;
		Index++;
	}

	for (uint32 i = 0; i < 3; i++)
	{
		uint32 Digit = DigitsArray[i];

		UPaperSprite* DigitSprite = SpriteNums[DigitsArray[i]];
		DigitSprite->GetName();
		DigitSpriteComps[i]->SetSprite(DigitSprite);

		/*// Debug
		if (GEngine)
		{
			FString Msg = FString::Printf(TEXT("[WEScoreDisplay] Digit %d Sprite Name %s"), Digit, *DigitSprite->GetName());
			GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Msg);
		}*/
	}

	/*// Debug
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[WEScoreDisplay] SetScore %d"), ScoreNum);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, Msg);
	}*/
}
