// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "EquipmentBase.generated.h"

/**
 * The base of all Equipment actors
 */

UENUM()
enum class EEquipmentType : uint8
{
	ET_Melee,
	ET_Shield,
	ET_Ranged,
	ET_Max
};

UENUM()
enum class EEquipAnimState : uint8
{
	AS_Idle,
	AS_Blocking,
	AS_Attacking,
	AS_Reloading,
	AS_Max
};


UENUM()
enum class EHandType : uint8
{
	HT_Main,
	HT_Off,
	HT_Max
};

class ADA_Character;
class ARangedProjectile;
class UPaperFlipbook;
class UPaperFlipbookComponent;

USTRUCT(BlueprintType)
struct FEquipmentVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float fWeaponDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fLeechPercent = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fPoisonPercent = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	bool bIsTwoHanded = false;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	bool bCanReflect = false;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	float fBlockPercent = 100.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fAttackTimer = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Ranged")
	TSubclassOf<ARangedProjectile> Projectile = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Ranged")
	int32 iAmmo = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* AimBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* ReloadBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* AttackBook;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* MyUITexture = nullptr;
};


UCLASS()
class DUNGEON_ASSAULT_UE4_API AEquipmentBase : public APaperFlipbookActor
{
	GENERATED_BODY()
	
public:

	AEquipmentBase();

	virtual void Attack();

	//Called when player changes weapons
	void SetWeapon();

	float GetLeechPercent();

	float GetPoisonPercent();

	bool CanReflect();

	void SetPlayer(ADA_Character &CharacterToSet);

	UPROPERTY(EditDefaultsOnly, Category = "EquipmentInfo")
	FEquipmentVariables EquipmentInfo;

	void SwitchToIdle();

	EEquipAnimState CurrentAnimState = EEquipAnimState::AS_Idle;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EEquipmentType MyEquipType = EEquipmentType::ET_Melee;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	EHandType MyHandType = EHandType::HT_Main;

	bool bCanAttack = true;

	ADA_Character* MyPlayer;

	FString GetEnumAsString(EEquipmentType EnumValue);

protected:
	virtual void AnimSwitch(EEquipAnimState SwitchState);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "FlipBook")
	UPaperFlipbookComponent* MyFlipbookComp = nullptr;

	//Anim Variables
	FTimerHandle AnimTimerHandle;
	
	
};
