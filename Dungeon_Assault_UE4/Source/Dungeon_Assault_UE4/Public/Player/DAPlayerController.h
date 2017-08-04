// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DAPlayerController.generated.h"

class UDAPlayerUI;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ADAPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<UDAPlayerUI> PlayerUIToCreate = nullptr;;
	
};
