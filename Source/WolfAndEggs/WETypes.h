// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "WETypes.generated.h"


UENUM(BlueprintType)
enum class EWECornerDirection : uint8
{
	TopLeft           =0,
	TopRight          =1,
	BottomLeft        =2,
	BottomRight       =3,
};

UENUM(BlueprintType)
enum class EWEDirection : uint8
{
	Left              =0,
	Right             =1,
	Top               =2,
	Bottom            =3,
};