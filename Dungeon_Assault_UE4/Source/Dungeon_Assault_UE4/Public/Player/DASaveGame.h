// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DASaveGame.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FMenuSaveData
{
	GENERATED_BODY()




};

struct FGameplaySaveData
{
	GENERATED_BODY()

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
	
protected:
	FGameplaySaveData GameplaySaveData;
	FMenuSaveData MenuSaveData;
	
};
