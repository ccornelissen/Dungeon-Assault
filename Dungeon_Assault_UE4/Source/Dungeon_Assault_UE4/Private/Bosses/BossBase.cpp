// Fill out your copyright notice in the Description page of Project Settings.

#include "BossBase.h"
#include "EnemyHealthBar.h"
#include "WidgetComponent.h"
#include "BossLauncher.h"
#include "BossMelee.h"
#include "ArenaEndDoor.h"
#include "Dungeon_Assault_UE4.h"
#include "MinionSpawner.h"
#include "DACoin.h"

// Sets default values
ABossBase::ABossBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABossBase::BeginPlay()
{
	Super::BeginPlay();

	UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();

	if(WidgetComp)
	{
		BaseHealthBar = Cast<UEnemyHealthBar>(WidgetComp->GetUserWidgetObject());

		if (BaseHealthBar)
		{
			BaseHealthBar->SetHealthBar();
			BaseHealthBar->fMaxHealth = fBossHealth;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast to health bar failed!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lacking the widget comp"));
	}

	SetComponents();

	SetSaveInstance();

	CalculateDifficulty();

	SpawnComponents();
}

// Called every frame
void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossBase::ApplyDamage(float Damage)
{
	fBossHealth -= Damage;

	if (BaseHealthBar)
	{
		BaseHealthBar->UpdateHealthBar(fBossHealth);
	}

	DeathCheck();
}

void ABossBase::SetEndDoor(AArenaEndDoor & DoorRef)
{
	EndDoor = &DoorRef;
}

void ABossBase::SetSaveInstance()
{
	UDASaveGame* GameSaveInstance = Cast<UDASaveGame>(UGameplayStatics::CreateSaveGameObject(UDASaveGame::StaticClass()));

	if (GameSaveInstance)
	{
		SaveGameInstance = GameSaveInstance;

		SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
	}
}

void ABossBase::CalculateDifficulty()
{
	if (SaveGameInstance)
	{
		int32 CurFloor = SaveGameInstance->GameplaySaveData.iLastFloorCompleted;

		if (CurFloor < 10)
		{
			BossSupport = BossComponentDif1;

			if (CurFloor > 1)
			{
				iNumberOfComponentsToSpawn = (int32)CurFloor / 2;
			}
		}
		else if (CurFloor < 20)
		{
			BossSupport = BossComponentDif2;

			CurFloor = CurFloor - 10;

			iNumberOfComponentsToSpawn = (int32)CurFloor / 2;

		}
		else if (CurFloor < 30)
		{
			BossSupport = BossComponentDif3;

			CurFloor = CurFloor - 20;

			iNumberOfComponentsToSpawn = (int32)CurFloor / 2;
		}
		else if (CurFloor < 40)
		{
			BossSupport = BossComponentDif4;

			CurFloor = CurFloor - 30;

			iNumberOfComponentsToSpawn = (int32)CurFloor / 2;
		}
		else
		{
			BossSupport = BossComponentDif5;

			CurFloor = CurFloor - 40;

			iNumberOfComponentsToSpawn = (int32)CurFloor / 2;
		}
	}
}

void ABossBase::DeathCheck()
{
	if (fBossHealth <= 0)
	{
		for (int i = 0; i < SpawnedActors.Num(); i++)
		{
			if (SpawnedActors.IsValidIndex(i))
			{
				if (SpawnedActors[i] != nullptr)
				{
					GetWorld()->GetTimerManager().ClearAllTimersForObject(SpawnedActors[i]);

					SpawnedActors[i]->Destroy();
				}
			}
		}

		EndDoor->ActivateDoor();

		if (SaveGameInstance)
		{
			SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

			if (Coin)
			{
				FRotator SpawnRot = FRotator(0.0, -90.0, 90.0);

				FVector SpawnVec = FVector(GetActorLocation().X, GetActorLocation().Y, 50.0);

				ADACoin* SpawnedCoin = GetWorld()->SpawnActor<ADACoin>(Coin, SpawnVec, SpawnRot);

				int32 BossValue = SaveGameInstance->GameplaySaveData.iLastFloorCompleted * 50;

				SpawnedCoin->SetValue(BossValue);
			}
		
			int32 iNewFloor = SaveGameInstance->GameplaySaveData.iLastFloorCompleted + 1;

			SaveGameInstance->GameplaySaveData.iLastFloorCompleted = iNewFloor;

			UE_LOG(LogTemp, Warning, TEXT("Saving game, Floor to save: %d"), SaveGameInstance->GameplaySaveData.iLastFloorCompleted);

			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No save game instance"));
		}

		Destroy();
	}
}

void ABossBase::SpawnComponents()
{
	int32 iComponent = 0;

	for (int i = 0; i < iNumberOfComponentsToSpawn; i++)
	{
		int32 iSupportToSpawn = FMath::RandRange(0, (BossSupport.Num() - 1));

		if (BossSupport.IsValidIndex(iSupportToSpawn))
		{
			if (BossSupport[iSupportToSpawn]->IsChildOf(ABossLauncher::StaticClass()) && ComponentSpawns.IsValidIndex(iComponent))
			{
				if (ComponentSpawns[iComponent])
				{
					ABossLauncher* Launcher = GetWorld()->SpawnActor<ABossLauncher>(BossSupport[iSupportToSpawn], ComponentSpawns[iComponent]->GetComponentLocation(), ComponentSpawns[iComponent]->GetComponentRotation());

					SpawnedActors.Add(Launcher);

					iComponent++;
				}
			}

			if (BossSupport[iSupportToSpawn]->IsChildOf(AMinionSpawner::StaticClass()) && ComponentSpawns.IsValidIndex(iComponent))
			{
				if (ComponentSpawns[iComponent])
				{
					AMinionSpawner* Spawner = GetWorld()->SpawnActor<AMinionSpawner>(BossSupport[iSupportToSpawn], ComponentSpawns[iComponent]->GetComponentLocation(), ComponentSpawns[iComponent]->GetComponentRotation());

					SpawnedActors.Add(Spawner);

					iComponent++;
				}
			}

			if (BossSupport[iSupportToSpawn]->IsChildOf(ABossMelee::StaticClass()) && ComponentSpawns.IsValidIndex(iComponent))
			{
				if (ComponentSpawns[iComponent])
				{
					ABossMelee* TempMelee = GetWorld()->SpawnActor<ABossMelee>(BossSupport[iSupportToSpawn], ComponentSpawns[iComponent]->GetComponentLocation(), ComponentSpawns[iComponent]->GetComponentRotation());

					SpawnedActors.Add(TempMelee);

					iComponent++;
				}
			}
				
		}
	}
}

