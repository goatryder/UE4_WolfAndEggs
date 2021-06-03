// Fill out your copyright notice in the Description page of Project Settings.


#include "WEWolfPlayerController.h"
#include "WEWolf.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

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
