// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/EquipmentBase.h"
#include "ShieldBase.generated.h"

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API AShieldBase : public AEquipmentBase
{
	GENERATED_BODY()
	
public:
	AShieldBase();

	void Block();

	void UnBlock();

	void SetIdlePoint(USceneComponent &SceneRef);

	void SetBlockingPoint(USceneComponent &SceneRef);

private:
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	USceneComponent* IdlePoint;

	USceneComponent* BlockingPoint;

	virtual void AnimSwitch(EEquipAnimState SwitchState) override;
	
	
};
