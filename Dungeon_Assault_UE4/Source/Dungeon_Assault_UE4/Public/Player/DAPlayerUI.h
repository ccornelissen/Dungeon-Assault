// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DAPlayerUI.generated.h"


class UProgressBar;
/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API UDAPlayerUI : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;
	
public:
	void UpdateHealthBar(float Health);

	float fPlayerMaxHealth;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player")
	UProgressBar* PlayerHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	FLinearColor FullHealthColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	FLinearColor MidHealthColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	FLinearColor LowHealthColor;
};
