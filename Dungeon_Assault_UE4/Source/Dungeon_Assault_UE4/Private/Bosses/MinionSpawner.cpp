// Fill out your copyright notice in the Description page of Project Settings.

#include "MinionSpawner.h"
#include "BossMinion.h"
#include "DACoin.h"
#include "Dungeon_Assault_UE4.h"

void AMinionSpawner::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMinionSpawner::SpawnMinion, fSpawnTime, false);
}

void AMinionSpawner::SpawnMinion()
{
	if (MinionToSpawn)
	{
		ABossMinion* SpawnedMinion = GetWorld()->SpawnActor<ABossMinion>(MinionToSpawn, GetActorLocation(), GetActorRotation());
	}
	
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AMinionSpawner::SpawnMinion, fSpawnTime, false);
}

void AMinionSpawner::DestroySpawner()
{
	SpawnCoin();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Destroy();
}

void AMinionSpawner::SpawnCoin()
{
	UDASaveGame* SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::CreateSaveGameObject(UDASaveGame::StaticClass()));

	SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

	if (Coin && SaveGameInstance)
	{
		FRotator SpawnRot = FRotator(0.0, -90.0, 90.0);

		FVector SpawnVec = FVector(GetActorLocation().X, GetActorLocation().Y, 50.0);

		ADACoin* SpawnedCoin = GetWorld()->SpawnActor<ADACoin>(Coin, SpawnVec, SpawnRot);

		int32 CoinValue = SaveGameInstance->GameplaySaveData.iLastFloorCompleted * CoinModifier;

		SpawnedCoin->SetValue(CoinValue);
	}
}
