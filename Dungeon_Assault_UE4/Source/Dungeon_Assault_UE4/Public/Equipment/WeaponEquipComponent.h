// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "WeaponEquipComponent.generated.h"

/**
 * 
 */
UENUM()
enum class EAnimState : uint8
{
	AS_Idle,
	AS_Swing,
	AS_Max
};

UCLASS()
class DUNGEON_ASSAULT_UE4_API UWeaponEquipComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
public:

	UWeaponEquipComponent();

	void Attack();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float fWeaponDamage = 20.0f;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector StartLoc;

	//Anim Variables
	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float fSwingTimer = 0.5f;

	FTimerHandle AnimTimerHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* SwingBook;

	EAnimState CurrentAnimState = EAnimState::AS_Idle;

	void AnimSwitch(EAnimState SwitchState);

	void SwitchToIdle();
};
	