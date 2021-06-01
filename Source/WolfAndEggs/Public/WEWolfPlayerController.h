// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WEWolfPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WOLFANDEGGS_API AWEWolfPlayerController : public APlayerController
{
	GENERATED_BODY()

	AWEWolfPlayerController();

	UFUNCTION()
		virtual void SetupInputComponent() override;

protected:

	void SetPlayerCharacter(class APawn* PossesedPawn);
	class AWEWolf* PossesedWolfPawn;

	void MoveTopLeft();
	void MoveTopRight();
	void MoveBottomLeft();
	void MoveBottomRight();

	void MoveRight();
	void MoveLeft();
	void MoveBottom();
	void MoveTop();

};
