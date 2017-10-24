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
#include "Dungeon_Assault_UE4.h"
#include "ArenaEndDoor.h"
#include "EngineUtils.h"

AArenaMapActor::AArenaMapActor()
{
	TileMapComp = FindComponentByClass<UPaperTileMapComponent>();

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(RootComponent);
	BoxCollision->bGenerateOverlapEvents = false;
}

void AArenaMapActor::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		PlayerReference = *ActorItr;
	}

	SetupSaveGame();

	CalculateDifficulty();

	GenerateMap();

	SpawnActors();

	if (SpawnedBase)
	{
		SpawnedBase->SetSaveInstance(*SaveGameInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No base reference"));
	}

	if (PlayerReference)
	{
		PlayerReference->SetSaveInstance(*SaveGameInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No player reference"));
	}
}

void AArenaMapActor::SetupSaveGame()
{
	UDASaveGame* GameSaveInstance = Cast<UDASaveGame>(UGameplayStatics::CreateSaveGameObject(UDASaveGame::StaticClass()));

	if (GameSaveInstance)
	{
		SaveGameInstance = GameSaveInstance;

		SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

		UE_LOG(LogTemp, Warning, TEXT("Player Coins: %d"), SaveGameInstance->MenuSaveData.iPlayerCoins);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Save Game Instance"));
	}
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
				for (int32 mw = 0; mw < MapWidth; mw++)
				{
					for (int32 ml = 0; ml < MapLength; ml++)
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
		FVector BoxLoc = FVector(((MapWidth * 0.5f) * iMapSquareSize) - (iMapSquareSize * 0.5f), 1.0f, -((MapLength * 0.5f) * iMapSquareSize) + (iMapSquareSize * 0.5f));
		BoxCollision->SetRelativeLocation(BoxLoc);

		//Set Spawn Info
		int32 HalfMapWidth = (int32)MapWidth / 2;
		int32 HalfMapHeight = (int32)MapLength / 2;

		UE_LOG(LogTemp, Warning, TEXT("Map Width: %d, Map Heigh: %d"), HalfMapWidth, HalfMapHeight);

		SetPlayerSpawnData(TileMapComp->GetTileCenterPosition(iPlayerSpawnDepth, HalfMapHeight, 0, true));

		SetDoorSpawnData(TileMapComp->GetTileCenterPosition(MapWidth - iDoorSpawnDepth, HalfMapHeight, 0, true));

		SetBossSpawnData(TileMapComp->GetTileCenterPosition(HalfMapWidth, HalfMapHeight, 0, true));

		for (int32 iS = 0; iS < iNumberOfSupportToSpawn; iS++)
		{
			int32 WidthOffSet = FMath::RandRange(iMinimumOffset, HalfMapWidth);
			int32 HeightOffSet = FMath::RandRange(iMinimumOffset, HalfMapHeight);

			UE_LOG(LogTemp, Warning, TEXT("Adding support spawn data"));

			AddSupportSpawnData(TileMapComp->GetTileCenterPosition(HalfMapWidth + WidthOffSet, HalfMapHeight + HeightOffSet, 0, true));
		}
		
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

	AArenaEndDoor* DoorToSpawn = nullptr;

	if (EndDoor)
	{
		EndDoorSpawnData.fVerticalModifier = fDoorSpawnHeight;

		FRotator NewSpawnRot = EndDoorSpawnData.SpawnRotation;
		FVector NewSpawnLoc = FVector(EndDoorSpawnData.SpawnLocation.X, EndDoorSpawnData.SpawnLocation.Y, EndDoorSpawnData.fVerticalModifier);

		DoorToSpawn = GetWorld()->SpawnActor<AArenaEndDoor>(EndDoor, NewSpawnLoc, NewSpawnRot);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("End Door Not Set"))
	}

	if (BossBases.IsValidIndex(0))
	{
		BossSpawnData.fVerticalModifier = fBossSpawnHeight;

		FVector NewSpawnLoc = FVector(BossSpawnData.SpawnLocation.X, BossSpawnData.SpawnLocation.Y, BossSpawnData.fVerticalModifier);
		FRotator NewSpawnRot = FRotator(0, -180.0f, 0);

		SpawnedBase = GetWorld()->SpawnActor<ABossBase>(BossBases[0], NewSpawnLoc, NewSpawnRot);

		if (DoorToSpawn)
		{
			SpawnedBase->SetEndDoor(*DoorToSpawn);
		}

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to spawn Boss"));
	}

	for (int32 iS = 0; iS <= (SupportSpawnDataArray.Num() - 1); iS++)
	{
		int32 iSupportSpawn = FMath::RandRange(0, (BossSupport.Num() - 1));

		if (BossSupport.IsValidIndex(iSupportSpawn) && SupportSpawnDataArray.IsValidIndex(iS))
		{
			SupportSpawnDataArray[iS].fVerticalModifier = fSupportSpawnHeight;

			FVector NewSpawnLoc = FVector(SupportSpawnDataArray[iS].SpawnLocation.X, SupportSpawnDataArray[iS].SpawnLocation.Y, SupportSpawnDataArray[iS].fVerticalModifier);
			FRotator NewSpawnRot = SupportSpawnDataArray[iS].SpawnRotation;

			if (BossSupport[iSupportSpawn]->IsChildOf(ABossLauncher::StaticClass()))
			{
				GetWorld()->SpawnActor<ABossLauncher>(BossSupport[iSupportSpawn], NewSpawnLoc, NewSpawnRot);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Boss Launcher"));
		}
	}
}

void AArenaMapActor::SetBossSpawnData(FVector SpawnVec)
{
	BossSpawnData.SpawnLocation = SpawnVec;
}

void AArenaMapActor::SetPlayerSpawnData(FVector SpawnVec)
{
	PlayerStartData.SpawnLocation = SpawnVec;
}

void AArenaMapActor::SetDoorSpawnData(FVector SpawnVec)
{
	EndDoorSpawnData.SpawnLocation = SpawnVec;
}

void AArenaMapActor::AddSupportSpawnData(FVector SpawnVec)
{
	FTileSpawnData TempData;
	TempData.SpawnLocation = SpawnVec;

	SupportSpawnDataArray.Add(TempData);
}

void AArenaMapActor::CalculateDifficulty()
{
	if (SaveGameInstance)
	{
		int32 iFloor = SaveGameInstance->GameplaySaveData.iLastWaveCompleted;

		UE_LOG(LogTemp, Warning, TEXT("%d"), iFloor);

		if (iFloor < 10)
		{
			iFloorDifficulty = 1;

			iNumberOfSupportToSpawn = iFloor - 1;

			BossBases = BossBasesDif1;
			BossSupport = BossSupportDif1;
		}
		else if (iFloor < 20)
		{
			iFloorDifficulty = 2;

			iNumberOfSupportToSpawn = iFloor - 11;

			BossBases = BossBasesDif2;
			BossSupport = BossSupportDif2;
		}
		else if (iFloor < 30)
		{
			iFloorDifficulty = 3;

			iNumberOfSupportToSpawn = iFloor - 21;

			BossBases = BossBasesDif3;
			BossSupport = BossSupportDif3;
		}
		else if (iFloor < 40)
		{
			iFloorDifficulty = 4;

			iNumberOfSupportToSpawn = iFloor - 31;

			BossBases = BossBasesDif4;
			BossSupport = BossSupportDif4;
		}
		else
		{
			iFloorDifficulty = 5;

			iNumberOfSupportToSpawn = iFloor - 41;

			BossBases = BossBasesDif5;
			BossSupport = BossSupportDif5;
		}
	}

}
