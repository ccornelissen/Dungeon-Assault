// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "MinionSpawner.generated.h"

class ABossMinion;
/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API AMinionSpawner : public APaperFlipbookActor
{
	GENERATED_BODY()

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


protected:
	void SpawnMinion();
	
	UPROPERTY(EditDefaultsOnly, Category = "Minion Details")
	TSubclassOf<ABossMinion> MinionToSpawn;
	
	UPROPERTY(EditDefaultsOnly, Category = "Minion Details")
	float fSpawnTime = 10.0f;

	FTimerHandle SpawnTimerHandle;
	
};
