// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentBase.h"
#include "RangedBase.generated.h"

/**
 * 
 */

class ARangedProjectile;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ARangedBase : public AEquipmentBase
{
	GENERATED_BODY()
	
public:
	ARangedBase();

	virtual void Attack() override;

private:

	FVector FireLoc;

	virtual void AnimSwitch(EEquipAnimState SwitchState) override;
	
	
};
