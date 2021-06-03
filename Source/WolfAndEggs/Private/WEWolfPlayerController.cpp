// Fill out your copyright notice in the Description page of Project Settings.


#include "WEWolfPlayerController.h"
#include "WEWolf.h"

#include "WEGameModeA.h"
#include "WEGameModeB.h"
#include "WEGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

AWEWolfPlayerController::AWEWolfPlayerController()
{
	OnNewPawn.AddUObject(this, &AWEWolfPlayerController::SetPlayerCharacter);

	CustomGameState = Cast<AWEGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

void AWEWolfPlayerController::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("MoveTopLeft", IE_Pressed, this, &AWEWolfPlayerController::MoveTopLeft);
	InputComponent->BindAction("MoveTopRight", IE_Pressed, this, &AWEWolfPlayerController::MoveTopRight);
	InputComponent->BindAction("MoveBottomLeft", IE_Pressed, this, &AWEWolfPlayerController::MoveBottomLeft);
	InputComponent->BindAction("MoveBottomRight", IE_Pressed, this, &AWEWolfPlayerController::MoveBottomRight);

	InputComponent->BindAction("MoveRight", IE_Pressed, this, &AWEWolfPlayerController::MoveRight);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &AWEWolfPlayerController::MoveLeft);
	InputComponent->BindAction("MoveBottom", IE_Pressed, this, &AWEWolfPlayerController::MoveBottom);
	InputComponent->BindAction("MoveTop", IE_Pressed, this, &AWEWolfPlayerController::MoveTop);

	InputComponent->BindAction("GameA", IE_Pressed, this, &AWEWolfPlayerController::GameAPressed);
	InputComponent->BindAction("GameA", IE_Released, this, &AWEWolfPlayerController::GameAReleased);
	InputComponent->BindAction("GameB", IE_Pressed, this, &AWEWolfPlayerController::GameBPressed);
	InputComponent->BindAction("GameB", IE_Released, this, &AWEWolfPlayerController::GameBReleased);
	InputComponent->BindAction("Pause", IE_Pressed, this, &AWEWolfPlayerController::PausePressed).bExecuteWhenPaused = true;;
}

void AWEWolfPlayerController::SetPlayerCharacter(APawn* PossesedPawn)
{
	AWEWolf* PossesedCharacter = Cast<AWEWolf>(PossesedPawn);
	if (PossesedCharacter)
	{
		PossesedWolfPawn = PossesedCharacter;

		// set camera
		AActor* SceneCamera = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraActor::StaticClass());

		if (SceneCamera)
		{
			SetViewTarget(SceneCamera);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("[WolfPlayerController] Can't find any camera on %s scene, please add one"), 
				*GetWorld()->GetName());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[WolfPlayerController] Possesed Character should be instance of WEWolf class"));
	}
}

void AWEWolfPlayerController::MoveTopLeft()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketDirection(EWECornerDirection::TopLeft);
	}
}

void AWEWolfPlayerController::MoveTopRight()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketDirection(EWECornerDirection::TopRight);
	}
}

void AWEWolfPlayerController::MoveBottomLeft()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketDirection(EWECornerDirection::BottomLeft);
	}
}

void AWEWolfPlayerController::MoveBottomRight()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketDirection(EWECornerDirection::BottomRight);
	}
}

void AWEWolfPlayerController::MoveRight()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Right);
	}
}

void AWEWolfPlayerController::MoveLeft()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Left);
	}
}

void AWEWolfPlayerController::MoveBottom()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Bottom);
	}
}

void AWEWolfPlayerController::MoveTop()
{
	if (PossesedWolfPawn)
	{
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Top);
	}
}

void AWEWolfPlayerController::GameAPressed()
{
	ensure(CustomGameState);
	
	uint32 RecordScoreA = CustomGameState->GetMaxScoreGameA();

	// todo: show score
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[WolfPlayerController] Todo show score A: %d"), RecordScoreA);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Msg);
	}
}

void AWEWolfPlayerController::GameAReleased()
{
	ensure(CustomGameState);
	CustomGameState->RunGameA();
}

void AWEWolfPlayerController::GameBPressed()
{
	ensure(CustomGameState);
	CustomGameState->RunGameB();
}

void AWEWolfPlayerController::GameBReleased()
{
	ensure(CustomGameState);

	uint32 RecordScoreB = CustomGameState->GetMaxScoreGameB();

	// todo: show score
	if (GEngine)
	{
		FString Msg = FString::Printf(TEXT("[WolfPlayerController] Todo show score B: %d"), RecordScoreB);
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Msg);
	}
}

void AWEWolfPlayerController::PausePressed()
{
	SetPause(!IsPaused());
}
