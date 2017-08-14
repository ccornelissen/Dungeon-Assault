// Fill out your copyright notice in the Description page of Project Settings.

#include "BossLauncher.h"
#include "BossProjectile.h"
#include "DA_Character.h"
#include "EngineUtils.h"
#include "EnemyHealthBar.h"
#include "WidgetComponent.h"
#include "BossBase.h"
#include "PaperFlipbookComponent.h"

ABossLauncher::ABossLauncher()
{
	FireFromComponent = CreateDefaultSubobject<USceneComponent>(TEXT("FireFromComponent"));
	FireFromComponent->SetupAttachment(RootComponent);
}


void ABossLauncher::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);

	FireFromComponent->SetRelativeLocation(FVector::ZeroVector);

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}

	for (TActorIterator<ABossBase> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		MainBoss = *ActorItr;
	}

	UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();

	if (WidgetComp)
	{
		LauncherHealthBar = Cast<UEnemyHealthBar>(WidgetComp->GetUserWidgetObject());

		if (LauncherHealthBar)
		{
			LauncherHealthBar->SetHealthBar();

			LauncherHealthBar->fMaxHealth = fLauncherHealth;
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
	
}

void ABossLauncher::FireProjectile()
{
	FVector SpawnLoc = FVector(GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);

	ABossProjectile* CurProjectile = GetWorld()->SpawnActor<ABossProjectile>(Projectile, SpawnLoc, GetActorRotation());
	
	FRotator Rot = FRotationMatrix::MakeFromX(Player->GetActorLocation() - GetActorLocation()).Rotator();

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

	if (CurProjectile->BookComponent && MainBoss)
	{
		CurProjectile->BookComponent->MoveIgnoreActors.Add(MainBoss);

		CurProjectile->BookComponent->MoveIgnoreActors.Add(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Not firing projectile"));
	}
		
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ABossLauncher::FireProjectile, fReloadTime, false);
}

void ABossLauncher::ApplyDamage(float fDamage)
{
	fLauncherHealth -= fDamage;

	if (LauncherHealthBar)
	{
		LauncherHealthBar->UpdateHealthBar(fLauncherHealth);
	}

	if (fLauncherHealth <= 0)
	{
		DestroyLauncher();
	}
}

void ABossLauncher::DestroyLauncher()
{
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimerHandle);

	Destroy();
}
