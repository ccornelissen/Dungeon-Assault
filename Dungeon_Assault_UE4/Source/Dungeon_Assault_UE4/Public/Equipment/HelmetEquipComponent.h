// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "HelmetEquipComponent.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FHelmetVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* ForwardBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* BackBook;
};

UCLASS(Blueprintable)
class DUNGEON_ASSAULT_UE4_API UHelmetEquipComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	UTexture2D* MyUITexture = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Helmet Info")
	FHelmetVariables HelmetInfo;
	
	
	
};
