// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
//#include "Engine/Canvas.h"
#include "WolfAndEggsHUD.generated.h"



/**
 * 
 */

 // DISABLED, HUD INTEGRATED IN GAME SCENE AS SEPARATE ACTORS

UCLASS()
class WOLFANDEGGS_API AWolfAndEggsHUD : public AHUD
{
	GENERATED_BODY()

	AWolfAndEggsHUD();

public:
	/*
	UPROPERTY()
		UTexture2D* HealthTexture;

	UPROPERTY()
		UTexture2D* NumsTexture;

	UPROPERTY()
		UTexture2D* NumBgTexture;
	
	UPROPERTY()
		FCanvasIcon HealthIcon;

	UPROPERTY()
		TArray<FCanvasIcon> NumIcons;

	UPROPERTY()
		FCanvasIcon NumBgIcon;

	// Main HUD update loop.
	virtual void DrawHUD() override; */

};
