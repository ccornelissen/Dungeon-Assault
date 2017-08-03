// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "ArenaMapActor.generated.h"

class UPaperTileMapComponent;
class UBoxComponent;
class UPaperTileSet;
class UPaperTileMap;

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API AArenaMapActor : public APaperTileMapActor
{
	GENERATED_BODY()

	AArenaMapActor();

public:
	void GenerateMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	//Map Gen Variables
	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	int32 iMaxMapSize = 25;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	int32 iMinMapSize = 15;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	int32 iMapSquareSize = 128;

	UPROPERTY(EditDefaultsOnly, Category = "Map Generation")
	UPaperTileSet* TileSetOne;

private:
	UPaperTileMapComponent* TileMapComp = nullptr;
	UPaperTileMap* TileMap = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision = nullptr;
	
};
