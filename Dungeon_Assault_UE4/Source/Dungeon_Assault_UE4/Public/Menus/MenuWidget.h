// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UImage;
class UPaperFlipbookComponent;

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;


protected:
	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetHoveredColor(UTextBlock* TextToSet);

	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetUnhoveredColor(UTextBlock* TextToSet);

	UFUNCTION(BlueprintCallable, Category = "Button")
	int32 ChangeEquipment(UImage* ImageToSet, TArray<TSubclassOf<UPaperFlipbookComponent>> EquipmentArray, int32 i);

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor UnhoveredColor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor HoveredColor;

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
	
};
