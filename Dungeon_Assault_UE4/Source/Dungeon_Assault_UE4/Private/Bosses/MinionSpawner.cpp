// Fill out your copyright notice in the Description page of Project Settings.

#include "MinionSpawner.h"
#include "BossMinion.h"

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
