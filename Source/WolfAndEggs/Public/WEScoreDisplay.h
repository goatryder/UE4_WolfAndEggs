// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WEScoreDisplay.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class WOLFANDEGGS_API AWEScoreDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWEScoreDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	uint32 MaxScore;
	uint32 CurrentScore;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		TArray<UPaperSprite*> SpriteNums;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSprite* SpriteNumBG;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TArray<UPaperSpriteComponent*> DigitSpriteComps;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		TArray<UPaperSpriteComponent*> DigitBGSpriteComps;

public:	

	void SetScore(uint32 ScoreNum);
};
