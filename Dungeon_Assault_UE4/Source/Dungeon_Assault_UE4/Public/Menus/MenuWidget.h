// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DAEnums.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UImage;
class UButton;
class USlider;
class UPaperFlipbookComponent;
class UDASaveGame;

UCLASS()
class DUNGEON_ASSAULT_UE4_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;


protected:
	///////////////////////////
	//GENERAL//
	///////////////////////////

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SetupSaveGame(UDASaveGame* GameSaveInstance);

	UPROPERTY(BlueprintReadWrite, Category = "Save")
	UDASaveGame* SaveGameInstance;

	UFUNCTION(BlueprintCallable, Category = "Save")
	void SaveGame();

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

	//Set Up//
	UFUNCTION(BlueprintCallable, Category = "Options")
	void OptionScreenSetup(USlider* ResSlide, USlider* MusicSlide, USlider* SFXSlide, UButton* EnableDynRes, UButton* DisableDynRes, UButton* StickControl, UButton* TouchControl);

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

	///////////////////////////
	//Equipment Screen//
	///////////////////////////

	//Set Up//
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void EquipmentScreenSetup(UImage* MainWep, UImage* MainOff, UImage* HelmImg, UImage* ArmorImg, UImage* SecondWep, UImage* SecondOff);

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iHelmets;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iArmor;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iMainWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iMainOffhand;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iSecondWeapon;

	UPROPERTY(BlueprintReadWrite, Category = "Equipment")
	int32 iSecondOffhand;

	///////////////

	UFUNCTION(BlueprintCallable, Category = "Options")
	int32 ChangeEquipment(UImage* ImageToSet, TArray<TSubclassOf<UPaperFlipbookComponent>> EquipmentArray, int32 i);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> HelmetArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> ArmorArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> WeaponArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Equipment")
	TArray<TSubclassOf<UPaperFlipbookComponent>> OffhandArray;

	///////////////////////////
	//Store//
	///////////////////////////

	//Set Up//
	UFUNCTION(BlueprintCallable, Category = "Equipment")
	void StoreSetup(UImage* StoreWeapon, UImage* StoreArmor, UImage* StoreOffhand, UImage* StoreHelmet, UButton* AdFreeButton, UImage* AdFreeImage);

	///////////////////////

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Store")
	TArray<TSubclassOf<UPaperFlipbookComponent>> StoreHelmetArray;

	UPROPERTY(BlueprintReadWrite, Category = "Store")
	int32 iStoreHelmet;
	
	UFUNCTION(BlueprintCallable, Category = "Store")
	void BuyAdFree(UButton* AdFreeButton, UImage* AdFreeImage);

	EAdState CurrentAdState = EAdState::AS_Free;


};
