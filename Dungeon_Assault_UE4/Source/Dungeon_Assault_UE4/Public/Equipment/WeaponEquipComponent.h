// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "WeaponEquipComponent.generated.h"

/**
 * 
 */

UENUM()
enum class EWeaponAnimState : uint8
{
	AS_Idle,
	AS_Swing,
	AS_Max
};

USTRUCT(BlueprintType)
struct FWeaponVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float fWeaponDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	float fSwingTimer = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* SwingBook;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	bool bCanDeflect = false;

	UPROPERTY(EditDefaultsOnly, Category = "Stats")
	float fLeechPercent = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Type")
	bool bIsTwoHanded = false;
};

class ADA_Character;

UCLASS(Blueprintable)
class DUNGEON_ASSAULT_UE4_API UWeaponEquipComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()
public:

	UWeaponEquipComponent();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* MyUITexture = nullptr;

	void Attack();

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
	FWeaponVariables WeaponInfo;

	//Called when player changes weapons
	void SetWeapon();

	float GetLeechPercent();

	bool CanDeflect();

	void SetPlayer(ADA_Character &CharacterToSet);

private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector StartLoc;

	//Anim Variables
	FTimerHandle AnimTimerHandle;

	EWeaponAnimState CurrentAnimState = EWeaponAnimState::AS_Idle;

	void AnimSwitch(EWeaponAnimState SwitchState);

	bool bCanSwing = true;

	ADA_Character* MyPlayer;

	void SwitchToIdle();
};
	