// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAEnums.h"
#include "GameFramework/SaveGame.h"
#include "DASaveGame.generated.h"

class UWeaponEquipComponent;
class UArmormEquipComponent;
class UHelmetEquipComponent;
class UPaperFlipbookComponent;

USTRUCT(BlueprintType)
struct FMenuSaveData
{
	GENERATED_BODY()

	//////EQUIPMENT SCREEN/////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedHelmets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedOffhands;

	//////OPTIONS/////////

	float SavedResolution = 1.0f;

	EDynamicResState SavedDynamicResState = EDynamicResState::DS_Enabled;

	EControlState SavedControlState = EControlState::CS_Joystick;

	float SaveMusicVolume = 1.0f;

	float SavedSFXVolume = 1.0f;

	//////STORE/////////
	int iPlayerCoins = 0;

	EAdState SavedAdState = EAdState::AS_Free;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreOffhands;
};

USTRUCT(BlueprintType)
struct FGameplaySaveData
{
	GENERATED_BODY()

	int iLastWaveCompleted = 1;

	UPaperFlipbookComponent* SetMainWeapon;
	UPaperFlipbookComponent* SetMainOffhand;
	UPaperFlipbookComponent* SetSecondaryWeapon;
	UPaperFlipbookComponent* SetSecondaryOffhand;
	UPaperFlipbookComponent* SetHelmet;
	UPaperFlipbookComponent* SetArmor;
};

UCLASS()
class DUNGEON_ASSAULT_UE4_API UDASaveGame : public USaveGame
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	FString PlayerName;

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	uint32 UserIndex;

	UDASaveGame();
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
	FGameplaySaveData GameplaySaveData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Save Data")
	FMenuSaveData MenuSaveData;
	
};
