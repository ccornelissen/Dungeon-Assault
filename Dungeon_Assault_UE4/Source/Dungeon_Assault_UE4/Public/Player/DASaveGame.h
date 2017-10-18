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
	int32 iSavedMainWep = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int32 iSavedMainOffhand = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int32 iSavedArmor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int32 iSavedHelmet = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int32 iSavedSecondaryWeapon = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	int32 iSavedSecondaryOffhand = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedHelmets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OwnedOffhands;

	//////OPTIONS/////////

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	float SavedResolution = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	EDynamicResState SavedDynamicResState = EDynamicResState::DS_Enabled;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	EControlState SavedControlState = EControlState::CS_Joystick;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	float SaveMusicVolume = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Options")
	float SavedSFXVolume = 1.0f;

	//////STORE/////////
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	int iPlayerCoins = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	int iLastStoreWeapon = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	int iLastStoreOffhand = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	int iLastStoreArmor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	int iLastStoreHelmet = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	EAdState SavedAdState = EAdState::AS_Free;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreWeapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreOffhands;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreHelmets;
};

USTRUCT(BlueprintType)
struct FGameplaySaveData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	int iLastWaveCompleted = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetMainWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetMainOffhand;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetSecondaryWeapon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetSecondaryOffhand;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetHelmet;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Gameplay")
	UPaperFlipbookComponent* SetArmor;
};

UCLASS()
class DUNGEON_ASSAULT_UE4_API UDASaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	FString SaveSlotName;

	UPROPERTY(VisibleAnywhere, Category = "SetUp")
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FGameplaySaveData GameplaySaveData;

	UPROPERTY(VisibleAnywhere, Category = Basic)
	FMenuSaveData MenuSaveData;

	UDASaveGame();
};
