// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "ArenaMapActor.generated.h"

class UPaperTileMapComponent;
class UBoxComponent;
class UPaperTileSet;
class UPaperTileMap;
class ABossBase;
class ABossLauncher;
class ADA_Character;

USTRUCT()
struct FTileSpawnData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	FVector SpawnLocation;
	UPROPERTY()
	FRotator SpawnRotation = FRotator(0.0f, 90.0f, -90.0f);
	UPROPERTY()
	float fVerticalModifier = 120.0f;
	UPROPERTY()
	int32 LayerOfTile = 0;
};

UCLASS()
class DUNGEON_ASSAULT_UE4_API AArenaMapActor : public APaperTileMapActor
{
	GENERATED_BODY()

	AArenaMapActor();

public:
	void GenerateMap();

	void SpawnActors();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//Spawning Variables
	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	float fBossSpawnHeight = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	float fSupportSpawnHeight = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	int32 iMinimumOffset = 4;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerSpawnHeight = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	int32 iPlayerSpawnDepth = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBases;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Launchers")
	TArray<TSubclassOf<ABossLauncher>> BossLaunchers;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	ADA_Character* PlayerReference = nullptr;

	FTileSpawnData BossSpawnData;

	void SetBossSpawnData(FVector SpawnVec);

	FTileSpawnData PlayerStartData;

	void SetPlayerSpawnData(FVector SpawnVec);

	TArray<struct FTileSpawnData> SupportSpawnDataArray;

	void AddSupportSpawnData(FVector SpawnVec);

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
