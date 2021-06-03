// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WELifesDisplay.generated.h"

class UPaperSpriteComponent;
class UPaperSprite;

UCLASS()
class WOLFANDEGGS_API AWELifesDisplay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWELifesDisplay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSprite* LifeSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		TArray<UPaperSpriteComponent*> LifeSpriteComps;

public:	

	void SetCurrentLife(uint32 LifeNum);

};
