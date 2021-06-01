// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../WETypes.h"

#include "WEWolf.generated.h"

class UPaperSpriteComponent;

UCLASS()
class WOLFANDEGGS_API AWEWolf : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AWEWolf();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteWolfFaceLeftComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteWolfFaceRightComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteBasketTopLeftComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteBasketTopRightComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteBaskeBottomLeftComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UPaperSpriteComponent* SpriteBasketBottomRightComp;

	EWEBasketDirection BasketDirection;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		EWEBasketDirection GetBasketDirection() const { return BasketDirection; }

	/** Controlls Wolf and Basket Position */
	void SetBasketDirection(EWEBasketDirection NewBasketDirection);

	/** Partial Controll for Wolf and Basket Position */
	void SetBasketPartialDirection(EWEDirection PartialDirection)
	{
		switch (PartialDirection)
		{
		case EWEDirection::Bottom:
			switch (BasketDirection)
			{
			case EWEBasketDirection::TopLeft:
				SetBasketDirection(EWEBasketDirection::BottomLeft);
				break;
			case EWEBasketDirection::TopRight:
				SetBasketDirection(EWEBasketDirection::BottomRight);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Top:
			switch (BasketDirection)
			{
			case EWEBasketDirection::BottomLeft:
				SetBasketDirection(EWEBasketDirection::TopLeft);
				break;
			case EWEBasketDirection::BottomRight:
				SetBasketDirection(EWEBasketDirection::TopRight);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Left:
			switch (BasketDirection)
			{
			case EWEBasketDirection::BottomRight:
				SetBasketDirection(EWEBasketDirection::BottomLeft);
				break;
			case EWEBasketDirection::TopRight:
				SetBasketDirection(EWEBasketDirection::TopLeft);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Right:
			switch (BasketDirection)
			{
			case EWEBasketDirection::BottomLeft:
				SetBasketDirection(EWEBasketDirection::BottomRight);
				break;
			case EWEBasketDirection::TopLeft:
				SetBasketDirection(EWEBasketDirection::TopRight);
				break;
			default:
				break;
			}

			break;

		default:
			break;
		}
	}
};
