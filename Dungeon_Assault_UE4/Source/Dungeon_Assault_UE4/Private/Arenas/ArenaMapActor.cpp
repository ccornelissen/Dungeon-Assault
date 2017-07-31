// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaMapActor.h"
#include "PaperTileMapComponent.h"
#include "PaperTileSet.h"
#include "PaperTileMap.h"
#include "PaperTileLayer.h"
#include "Components/BoxComponent.h"

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

		//Adjust the box collisio for the new maps location and size
		FVector BoxScale = FVector(MapWidth * 2.0f, 1.0f, MapLength * 2.0f);
		BoxCollision->SetWorldScale3D(BoxScale);
		FVector BoxLoc = FVector(((MapWidth * 0.5f) * iMapSquareSize) - (iMapSquareSize * 0.5f) , 1.0f, -((MapLength * 0.5f) * iMapSquareSize) + (iMapSquareSize * 0.5f));
		BoxCollision->SetRelativeLocation(BoxLoc);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No Paper tile map component found to generate a map with."));
	}
}

void AArenaMapActor::BeginPlay()
{
	GenerateMap();
}
