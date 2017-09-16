// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class UTextBlock;
class UImage;

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
	void ChangeEquipment(UImage* ImageToSet, TArray<UImage*> ImageArray, int i);

	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> ArmorImages;

	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> HelmetImages;

	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> WeaponImages;

	UPROPERTY(BlueprintReadWrite)
	TArray<UImage*> OffhandImages;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor UnhoveredColor;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	FLinearColor HoveredColor;
	
};
