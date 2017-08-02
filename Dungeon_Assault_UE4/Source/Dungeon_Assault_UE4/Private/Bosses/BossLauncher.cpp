// Fill out your copyright notice in the Description page of Project Settings.

#include "BossLauncher.h"
#include "BossProjectile.h"
#include "DA_Character.h"
#include "EngineUtils.h"

void ABossLauncher::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}
}

void ABossLauncher::FireProjectile()
{
	FVector SpawnLoc = FVector(GetActorLocation().X - 200.0f, GetActorLocation().Y, GetActorLocation().Z);

	ABossProjectile* CurProjectile = GetWorld()->SpawnActor<ABossProjectile>(Projectile, SpawnLoc, GetActorRotation());

	if (Player)
	{
		CurProjectile->SetPlayer(*Player);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Launcher isn't get a reference to the player"));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);
}
