// Fill out your copyright notice in the Description page of Project Settings.


#include "WEWolfPlayerController.h"
#include "WEWolf.h"

AWEWolfPlayerController::AWEWolfPlayerController()
{
	OnNewPawn.AddUObject(this, &AWEWolfPlayerController::SetPlayerCharacter);
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
}

void AWEWolfPlayerController::SetPlayerCharacter(APawn* PossesedPawn)
{
	AWEWolf* PossesedCharacter = Cast<AWEWolf>(PossesedPawn);
	if (PossesedCharacter)
	{
		PossesedWolfPawn = PossesedCharacter;
	}
}

void AWEWolfPlayerController::MoveTopLeft()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveTopLeft"));
		PossesedWolfPawn->SetBasketDirection(EWEBasketDirection::TopLeft);
	}
}

void AWEWolfPlayerController::MoveTopRight()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveTopRight"));
		PossesedWolfPawn->SetBasketDirection(EWEBasketDirection::TopRight);
	}
}

void AWEWolfPlayerController::MoveBottomLeft()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveBottomLeft"));
		PossesedWolfPawn->SetBasketDirection(EWEBasketDirection::BottomLeft);
	}
}

void AWEWolfPlayerController::MoveBottomRight()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveBottomRight"));
		PossesedWolfPawn->SetBasketDirection(EWEBasketDirection::BottomRight);
	}
}

void AWEWolfPlayerController::MoveRight()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveRight"));
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Right);
	}
}

void AWEWolfPlayerController::MoveLeft()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveLEft"));
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Left);
	}
}

void AWEWolfPlayerController::MoveBottom()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveBottom"));
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Bottom);
	}
}

void AWEWolfPlayerController::MoveTop()
{
	if (PossesedWolfPawn)
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveTop"));
		PossesedWolfPawn->SetBasketPartialDirection(EWEDirection::Top);
	}
}
