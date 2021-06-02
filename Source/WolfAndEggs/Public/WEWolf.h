// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "../WETypes.h"

#include "WEWolf.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnBasketDirectionChange, AWEWolf*, EWECornerDirection);

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

	EWECornerDirection BasketDirection;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		EWECornerDirection GetBasketDirection() const { return BasketDirection; }

	/** Controlls Wolf and Basket Position */
	void SetBasketDirection(EWECornerDirection NewBasketDirection);

	static FOnBasketDirectionChange NotifyOnBasketDirectionChange;

	/** Partial Controll for Wolf and Basket Position */
	void SetBasketPartialDirection(EWEDirection PartialDirection)
	{
		switch (PartialDirection)
		{
		case EWEDirection::Bottom:
			switch (BasketDirection)
			{
			case EWECornerDirection::TopLeft:
				SetBasketDirection(EWECornerDirection::BottomLeft);
				break;
			case EWECornerDirection::TopRight:
				SetBasketDirection(EWECornerDirection::BottomRight);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Top:
			switch (BasketDirection)
			{
			case EWECornerDirection::BottomLeft:
				SetBasketDirection(EWECornerDirection::TopLeft);
				break;
			case EWECornerDirection::BottomRight:
				SetBasketDirection(EWECornerDirection::TopRight);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Left:
			switch (BasketDirection)
			{
			case EWECornerDirection::BottomRight:
				SetBasketDirection(EWECornerDirection::BottomLeft);
				break;
			case EWECornerDirection::TopRight:
				SetBasketDirection(EWECornerDirection::TopLeft);
				break;
			default:
				break;
			}

			break;

		case EWEDirection::Right:
			switch (BasketDirection)
			{
			case EWECornerDirection::BottomLeft:
				SetBasketDirection(EWECornerDirection::BottomRight);
				break;
			case EWECornerDirection::TopLeft:
				SetBasketDirection(EWECornerDirection::TopRight);
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
