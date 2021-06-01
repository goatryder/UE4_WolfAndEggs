// Fill out your copyright notice in the Description page of Project Settings.


#include "WEWolf.h"
#include "PaperSpriteComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
AWEWolf::AWEWolf()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneComp;

	SpriteWolfFaceLeftComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteFaceLeft"));
	SpriteWolfFaceLeftComp->SetupAttachment(RootComponent);
	
	SpriteWolfFaceRightComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteFaceRight"));
	SpriteWolfFaceRightComp->SetupAttachment(RootComponent);

	SpriteBasketTopLeftComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteBasketUpLeft"));
	SpriteBasketTopLeftComp->SetupAttachment(RootComponent);
	
	SpriteBasketTopRightComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteBasketUpRight"));
	SpriteBasketTopRightComp->SetupAttachment(RootComponent);
	
	SpriteBaskeBottomLeftComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteBaskeDownLeft"));
	SpriteBaskeBottomLeftComp->SetupAttachment(RootComponent);
	
	SpriteBasketBottomRightComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("SpriteBaskeDownRight"));
	SpriteBasketBottomRightComp->SetupAttachment(RootComponent);

	// default basket direction
	SetBasketDirection(EWEBasketDirection::TopRight);
}

// Called when the game starts or when spawned
void AWEWolf::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWEWolf::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AWEWolf::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AWEWolf::SetBasketDirection(EWEBasketDirection NewBasketDirection)
{
	if (BasketDirection == NewBasketDirection)
	{
		return;
	}

	ensure(SpriteWolfFaceLeftComp);
	ensure(SpriteWolfFaceRightComp);

	ensure(SpriteBasketTopLeftComp);
	ensure(SpriteBasketTopRightComp);
	ensure(SpriteBaskeBottomLeftComp);
	ensure(SpriteBasketBottomRightComp);

	// todo: alpha anim for sprites

	switch (NewBasketDirection)
	{
	case EWEBasketDirection::BottomRight:
		SpriteWolfFaceLeftComp->SetVisibility(false);
		SpriteWolfFaceRightComp->SetVisibility(true);

		SpriteBasketTopLeftComp->SetVisibility(false);
		SpriteBasketTopRightComp->SetVisibility(false);
		SpriteBaskeBottomLeftComp->SetVisibility(false);
		SpriteBasketBottomRightComp->SetVisibility(true);
		break;
	
	case EWEBasketDirection::BottomLeft:
		SpriteWolfFaceLeftComp->SetVisibility(true);
		SpriteWolfFaceRightComp->SetVisibility(false);

		SpriteBasketTopLeftComp->SetVisibility(false);
		SpriteBasketTopRightComp->SetVisibility(false);
		SpriteBaskeBottomLeftComp->SetVisibility(true);
		SpriteBasketBottomRightComp->SetVisibility(false);
		break;
	
	case EWEBasketDirection::TopLeft:
		SpriteWolfFaceLeftComp->SetVisibility(true);
		SpriteWolfFaceRightComp->SetVisibility(false);

		SpriteBasketTopLeftComp->SetVisibility(true);
		SpriteBasketTopRightComp->SetVisibility(false);
		SpriteBaskeBottomLeftComp->SetVisibility(false);
		SpriteBasketBottomRightComp->SetVisibility(false);
		break;
	
	case EWEBasketDirection::TopRight:
		SpriteWolfFaceLeftComp->SetVisibility(false);
		SpriteWolfFaceRightComp->SetVisibility(true);

		SpriteBasketTopLeftComp->SetVisibility(false);
		SpriteBasketTopRightComp->SetVisibility(true);
		SpriteBaskeBottomLeftComp->SetVisibility(false);
		SpriteBasketBottomRightComp->SetVisibility(false);
		break;
	
	default:
		break;
	}

	BasketDirection = NewBasketDirection;
}
