// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "RangedEquipComponent.generated.h"

/**
 * 
 */

UENUM()
enum class ERangedAnimState : uint8
{
	RAS_Idle,
	RAS_Aiming,
	RAS_Shoot,
	RAS_Reloading,
	RAS_Max
};

class ADA_Character;
class ARangedProjectile;

USTRUCT(BlueprintType)
struct FRangedInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float fWeaponDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Reload")
	float fReloadTimer = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 iAmmo = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fLeechPercent = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* AimBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* ReloadBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* FireBook;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	bool bIsTwoHanded = false;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	TSubclassOf<ARangedProjectile> Projectile = nullptr;
};


UCLASS(Blueprintable)
class DUNGEON_ASSAULT_UE4_API URangedEquipComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

	URangedEquipComponent();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* MyUITexture = nullptr;

public:

	void Attack();

	UPROPERTY(EditDefaultsOnly, Category = "RangedInfo")
	FRangedInfo RangedInfo;

	void SetWeapon();

	void SetPlayer(ADA_Character &CharacterToSet);

private:

	FVector FireLoc;

	//Anim Variables
	FTimerHandle AnimTimerHandle;

	ERangedAnimState CurrentAnimState = ERangedAnimState::RAS_Idle;

	void AnimSwitch(ERangedAnimState SwitchState);

	bool bCanFire = true;

	ADA_Character* MyPlayer;

	void SwitchToIdle();
	
};
