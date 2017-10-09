// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class EDynamicResState : uint8
{
	DS_Enabled,
	DS_Disabled,
	DS_Max
};

UENUM(BlueprintType)
enum class EControlState : uint8
{
	CS_Joystick,
	CS_Touch,
	CS_Max
};

UENUM(BlueprintType)
enum class EAdState : uint8
{
	AS_Free,
	AS_Purchased,
	CS_Max
};

class DUNGEON_ASSAULT_UE4_API DAEnums
{

};
