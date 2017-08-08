// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "Components/BoxComponent.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"
#include "EngineUtils.h"

AArenaMapActor::AArenaMapActor()
{
	TileMapComp = FindComponentByClass<UPaperTileMapComponent>();

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = false;
}

void AArenaMapActor::GenerateMap()
{
	if (TileMapComp)
	{
		int32 MapWidth = FMath::RandRange(iMinMapSize, iMaxMapSize);
		int32 MapLength = FMath::RandRange(iMinMapSize, iMaxMapSize);

		TileMapComp->CreateNewTileMap(MapWidth, MapLength, iMapSquareSize, iMapSquareSize, 1.0f, true);

		TileMap = TileMapComp->TileMap;

		//Set the tile set
		if (TileMap != nullptr && TileSetOne != nullptr)
		{
			TileMap->SelectedTileSet = TileSetOne;

			FPaperTileInfo TileInfo;
			TileInfo.TileSet = TileSetOne;
			int32 TileIndex = FMath::RandRange(0, (TileSetOne->GetTileCount() - 2));
			TileInfo.PackedTileIndex = TileIndex;

			FPaperTileInfo TileEdgeInfo;
			TileEdgeInfo.TileSet = TileSetOne;
			TileEdgeInfo.PackedTileIndex = 5;

			UPaperTileLayer* TileLayer = TileMap->TileLayers[0];

			if (TileLayer != nullptr)
			{
				for (int mw = 0; mw < MapWidth; mw++)
				{
					for (int ml = 0; ml < MapLength; ml++)
					{
						//Set the map border
						if (ml == 0 || mw == 0)
						{
							TileLayer->SetCell(mw, ml, TileEdgeInfo);
						}
						else if (ml == (MapLength - 1) || mw == (MapWidth - 1))
						{
							TileLayer->SetCell(mw, ml, TileEdgeInfo);
						}
						else
						{
							TileLayer->SetCell(mw, ml, TileInfo);
						}
					}
				}
				
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No Tile layer present"));
			}

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Tile map or missing tile set"));
		}

		//Adjust the box collision for the new maps location and size
		FVector BoxScale = FVector(MapWidth * 2.0f, 1.0f, MapLength * 2.0f);
		BoxCollision->SetWorldScale3D(BoxScale);
		FVector BoxLoc = FVector(((MapWidth * 0.5f) * iMapSquareSize) - (iMapSquareSize * 0.5f) , 1.0f, -((MapLength * 0.5f) * iMapSquareSize) + (iMapSquareSize * 0.5f));
		BoxCollision->SetRelativeLocation(BoxLoc);

		//Set Spawn Info
		int32 HalfMapWidth = (int32)MapWidth / 2;
		int32 HalfMapHeight = (int32)MapLength / 2;

		UE_LOG(LogTemp, Warning, TEXT("Map Width: %d, Map Heigh: %d"), HalfMapWidth, HalfMapHeight);
		
		SetPlayerSpawnData(TileMapComp->GetTileCenterPosition(iPlayerSpawnDepth, HalfMapHeight, 0, true));

		SetBossSpawnData(TileMapComp->GetTileCenterPosition(HalfMapWidth, HalfMapHeight, 0, true));

		AddSupportSpawnData(TileMapComp->GetTileCenterPosition(HalfMapWidth + iMinimumOffset, HalfMapHeight + iMinimumOffset, 0, true));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Paper tile map component found to generate a map with."));
	}
}

void AArenaMapActor::SpawnActors()
{
	if (PlayerReference)
	{
		PlayerStartData.fVerticalModifier = fPlayerSpawnHeight;

		FRotator NewSpawnRot = PlayerStartData.SpawnRotation;
		FVector NewSpawnLoc = FVector(PlayerStartData.SpawnLocation.X, PlayerStartData.SpawnLocation.Y, PlayerStartData.fVerticalModifier);

		PlayerReference->SetActorLocation(NewSpawnLoc);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to move Player"))
	}
	
	if (BossBases.IsValidIndex(0))
	{
		BossSpawnData.fVerticalModifier = fBossSpawnHeight;

		FVector NewSpawnLoc = FVector(BossSpawnData.SpawnLocation.X, BossSpawnData.SpawnLocation.Y, BossSpawnData.fVerticalModifier);
		FRotator NewSpawnRot = FRotator(0,-180.0f,0);

		GetWorld()->SpawnActor<ABossBase>(BossBases[0], NewSpawnLoc, NewSpawnRot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Boss"))
	}

	if (BossLaunchers.IsValidIndex(0) && SupportSpawnDataArray.IsValidIndex(0))
	{
		SupportSpawnDataArray[0].fVerticalModifier = fSupportSpawnHeight;

		FVector NewSpawnLoc = FVector(SupportSpawnDataArray[0].SpawnLocation.X, SupportSpawnDataArray[0].SpawnLocation.Y, SupportSpawnDataArray[0].fVerticalModifier);
		FRotator NewSpawnRot = SupportSpawnDataArray[0].SpawnRotation;

		GetWorld()->SpawnActor<ABossLauncher>(BossLaunchers[0], NewSpawnLoc, NewSpawnRot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to Boss Launcher"))
	}
}

void AArenaMapActor::BeginPlay()
{
	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		PlayerReference = *ActorItr;
	}

	GenerateMap();

	SpawnActors();
}

void AArenaMapActor::SetBossSpawnData(FVector SpawnVec)
{
	BossSpawnData.SpawnLocation = SpawnVec;
}

void AArenaMapActor::SetPlayerSpawnData(FVector SpawnVec)
{
	PlayerStartData.SpawnLocation = SpawnVec;
}

void AArenaMapActor::AddSupportSpawnData(FVector SpawnVec)
{
	FTileSpawnData TempData;
	TempData.SpawnLocation = SpawnVec;

	SupportSpawnDataArray.Add(TempData);
}
