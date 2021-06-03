// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WEGameModeA.h"
#include "WEGameModeB.generated.h"

/**
 * 
 */
UCLASS()
class WOLFANDEGGS_API AWEGameModeB : public AWEGameModeA
{
	GENERATED_BODY()
	
public:

	virtual void EndMatch() override;

protected:

	virtual void SpawnEggRandPos() override;
};
