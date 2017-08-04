// Fill out your copyright notice in the Description page of Project Settings.

#include "BossLauncher.h"
#include "BossProjectile.h"
#include "DA_Character.h"
#include "EngineUtils.h"


ABossLauncher::ABossLauncher()
{
	FireFromComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FireFromComponent"));
	FireFromComponent->SetupAttachment(RootComponent);
}


void ABossLauncher::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);

	FireFromComponent->SetRelativeLocation(FVector::ZeroVector);

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}
}

void ABossLauncher::FireProjectile()
{
	FVector SpawnLoc = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	ABossProjectile* CurProjectile = GetWorld()->SpawnActor<ABossProjectile>(Projectile, SpawnLoc, GetActorRotation());
	
	FRotator Rot = FRotationMatrix::MakeFromX(GetActorLocation() - Player->GetActorLocation()).Rotator();

	FireFromComponent->SetRelativeRotation(Rot);

	FVector VectorToSet = FVector(FireFromComponent->GetForwardVector().Y, FireFromComponent->GetForwardVector().Z, 0.0f);

	CurProjectile->SetFireVector(VectorToSet);

	if (Player)
	{
		CurProjectile->SetPlayer(*Player);

		CurProjectile->MoveProjectile();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Launcher isn't get a reference to the player"));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);
}
