// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperTileMapActor.h"
#include "ArenaMapActor.generated.h"

class UPaperTileMapComponent;
class UBoxComponent;
class UPaperTileSet;
class UPaperTileMap;
class APaperFlipbookActor;
class ABossBase;
class ABossLauncher;
class ADA_Character;
class AArenaEndDoor;
class UDASaveGame;

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

	void SetupSaveGame();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UDASaveGame* SaveGameInstance;
	
	//Spawning Variables
	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	float fBossSpawnHeight = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	float fSupportSpawnHeight = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	int32 iMinimumOffset = 4;

	UPROPERTY(EditDefaultsOnly, Category = "End Door")
	float fDoorSpawnHeight = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "End Door")
	int32 iDoorSpawnDepth = 1;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float fPlayerSpawnHeight = 120.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	int32 iPlayerSpawnDepth = 1;

	/////BOSS BASES///////

	TArray<TSubclassOf<ABossBase>> BossBases;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBasesDif1;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBasesDif2;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBasesDif3;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBasesDif4;

	UPROPERTY(EditDefaultsOnly, Category = "Main Bosses")
	TArray<TSubclassOf<ABossBase>> BossBasesDif5;

	/////BOSS SUPPORTS///////

	TArray<TSubclassOf<APaperFlipbookActor>> BossSupport;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	TArray<TSubclassOf<APaperFlipbookActor>> BossSupportDif1;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	TArray<TSubclassOf<APaperFlipbookActor>> BossSupportDif2;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	TArray<TSubclassOf<APaperFlipbookActor>> BossSupportDif3;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	TArray<TSubclassOf<APaperFlipbookActor>> BossSupportDif4;

	UPROPERTY(EditDefaultsOnly, Category = "Boss Support")
	TArray<TSubclassOf<APaperFlipbookActor>> BossSupportDif5;

	UPROPERTY(EditDefaultsOnly, Category = "End Door")
	TSubclassOf<AArenaEndDoor> EndDoor;

	UPROPERTY(EditDefaultsOnly, Category = "Player")
	ADA_Character* PlayerReference = nullptr;

	FTileSpawnData BossSpawnData;

	void SetBossSpawnData(FVector SpawnVec);

	FTileSpawnData PlayerStartData;

	void SetPlayerSpawnData(FVector SpawnVec);

	FTileSpawnData EndDoorSpawnData;

	void SetDoorSpawnData(FVector SpawnVec);

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

	ABossBase* SpawnedBase = nullptr;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollision = nullptr;

	void CalculateDifficulty();

	int32 iFloorDifficulty = 1;

	int32 iNumberOfSupportToSpawn = 0;
	
};
