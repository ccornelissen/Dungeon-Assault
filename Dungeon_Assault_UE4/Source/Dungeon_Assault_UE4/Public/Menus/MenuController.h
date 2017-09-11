// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuController.generated.h"

class UMenuWidget;
/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API AMenuController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMenuWidget> MenuUIToCreate = nullptr;;
	
	
};
