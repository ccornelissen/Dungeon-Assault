// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAEnums.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;
class UPaperFlipbookComponent;
class UDASaveGame;
class UBlueprint;

UCLASS()
class DUNGEON_ASSAULT_UE4_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;


protected:
	///////////////////////////
	//GENERAL//
	///////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = "Save")
	TSubclassOf<UBlueprint> SaveGameBP;

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	UDASaveGame* SaveGameInstance;

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetHoveredColor(UTextBlock* TextToSet);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetUnhoveredColor(UTextBlock* TextToSet);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor UnhoveredColor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor HoveredColor;

	///////////////////////////
	//Options//
	///////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Options")
	void ChangeResolution(float fRes);

	FString sResolution;

	UFUNCTION(BlueprintCallable, Category = "Options")
	void ApplyOptions();

	UFUNCTION(BlueprintCallable, Category = "Options")
	void ChangeSFXMultiplier(float fMulti);

	UFUNCTION(BlueprintCallable, Category = "Options")
	void ChangeMusicMultiplier(float fMulti);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	FLinearColor EnabledColor;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Options")
	FLinearColor DisabledColor;

	UFUNCTION(BlueprintCallable, Category = "Options")
	void SetDynamicResolution(EDynamicResState StateToSet);

	UFUNCTION(BlueprintCallable, Category = "Options")
	void SetControlState(EControlState StateToSet);

	EDynamicResState CurDynamicResState = EDynamicResState::DS_Enabled;

	EControlState CurControlState = EControlState::CS_Joystick;

	///////////////////////////
	//Equipment Screen//
	///////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Options")
	int32 ChangeEquipment(UImage* ImageToSet, TArray<TSubclassOf<UPaperFlipbookComponent>> EquipmentArray, int32 i);

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iHelmets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> HelmetArray;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> ArmorArray;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iMainWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> WeaponArray;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iMainOffhand;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OffhandArray;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iSecondWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iSecondOffhand;

	///////////////////////////
	//Store//
	///////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Store")
	void BuyCoins(int CoinsPurchased);

	int iPlayerFunds = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreWeaponArray;

	UPROPERTY(BlueprintReadWrite, Category = "Store")
	int32 iStoreWeapon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreArmorArray;

	UPROPERTY(BlueprintReadWrite, Category = "Store")
	int32 iStoreArmor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreOffhandArray;

	UPROPERTY(BlueprintReadWrite, Category = "Store")
	int32 iStoreOffhand;
	
	UFUNCTION(BlueprintCallable, Category = "Store")
	void BuyAdFree(UButton* AdFreeButton, UImage* AdFreeImage);

	EAdState CurrentAdState = EAdState::AS_Free;


};
