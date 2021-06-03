// Fill out your copyright notice in the Description page of Project Settings.


#include "WolfAndEggsHUD.h"
#include "Engine/Texture2D.h"

// DISABLED, HUD INTEGRATED IN GAME SCENE AS SEPARATE ACTORS

AWolfAndEggsHUD::AWolfAndEggsHUD()
{
	/*static ConstructorHelpers::FObjectFinder<UTexture2D> HealthTextureOb(TEXT("/Game/Assets/loss/loss"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> NumsTextureOb(TEXT("/Game/Assets/score/nums"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> NumBgTextureOb(TEXT("/Game/Assets/score/num-bg"));

	HealthTexture = HealthTextureOb.Object;
	NumsTexture = NumsTextureOb.Object;
	NumBgTexture = NumBgTextureOb.Object;

	HealthIcon = UCanvas::MakeIcon(HealthTexture, 0, 0, 38, 32);
	
	const int NumIcoSizeX = 31;
	const int NumIcoSizeY = 47;

	NumBgIcon = UCanvas::MakeIcon(NumBgTexture, 0, 0, NumIcoSizeX, NumIcoSizeY);
	
	for (uint32 i = 0; i < 10; i++)
	{
		FCanvasIcon NumIcon = UCanvas::MakeIcon(NumsTexture, 0, i * NumIcoSizeY, NumIcoSizeX, NumIcoSizeY);
		NumIcons.Add(NumIcon);
	}*/

}

/*
void AWolfAndEggsHUD::DrawHUD()
{
	Super::DrawHUD();
	if (Canvas == nullptr)
	{
		return;
	}

	Canvas->SetDrawColor(FColor::White);

	Canvas->DrawIcon(HealthIcon, Canvas->SizeX / 2, Canvas->SizeY / 2, 1.0f);
}
*/