// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyHealthBar.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API UEnemyHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
	virtual void NativeConstruct() override;

public:
	void UpdateHealthBar(float Health);

	float fMaxHealth;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
		UProgressBar* HealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		FLinearColor FullHealthColor;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		FLinearColor MidHealthColor;

	UPROPERTY(EditDefaultsOnly, Category = "Health")
		FLinearColor LowHealthColor;
	
	
	
};
