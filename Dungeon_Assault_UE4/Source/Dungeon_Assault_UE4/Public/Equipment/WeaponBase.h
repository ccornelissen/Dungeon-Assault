// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentBase.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API AWeaponBase : public AEquipmentBase
{
	GENERATED_BODY()

public:
	AWeaponBase();

	virtual void Attack() override;

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector StartLoc;

	virtual void AnimSwitch(EEquipAnimState SwitchState) override;
	
	
	
	
};
