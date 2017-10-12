// Fill out your copyright notice in the Description page of Project Settings.

#include "BossBase.h"
#include "EnemyHealthBar.h"
#include "WidgetComponent.h"
#include "BossLauncher.h"
#include "BossMelee.h"
#include "ArenaEndDoor.h"
#include "MinionSpawner.h"

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

		Destroy();
	}
}

void ABossBase::SpawnComponents()
{
	if (HeadComponent && LauncherToSpawn)
	{
		ABossLauncher* BossHead = GetWorld()->SpawnActor<ABossLauncher>(LauncherToSpawn, HeadComponent->GetComponentLocation(), HeadComponent->GetComponentRotation());

		SpawnedActors.Add(BossHead);
	}

	if (TailComponent && SpawnerToSpawn)
	{
		AMinionSpawner* ButtSpawn = GetWorld()->SpawnActor<AMinionSpawner>(SpawnerToSpawn, TailComponent->GetComponentLocation(), TailComponent->GetComponentRotation());

		SpawnedActors.Add(ButtSpawn);
	}
	
	for (int i = 0; i < ArmComponents.Num(); i++)
	{
		if (ArmComponents.IsValidIndex(i) && MeleeToSpawn)
		{
			if (ArmComponents[i] != nullptr)
			{
				ABossMelee* TempMelee = GetWorld()->SpawnActor<ABossMelee>(MeleeToSpawn, ArmComponents[i]->GetComponentLocation(), ArmComponents[i]->GetComponentRotation());

				SpawnedActors.Add(TempMelee);
			}
		}
	}
}

