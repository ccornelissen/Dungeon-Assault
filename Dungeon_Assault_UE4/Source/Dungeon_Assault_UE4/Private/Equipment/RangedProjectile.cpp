// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "PaperFlipbookComponent.h"
#include "RangedEquipComponent.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"
#include "BossMinion.h"

ARangedProjectile::ARangedProjectile()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &ARangedProjectile::OnOverlapBegin);
	BookComponent->SetNotifyRigidBodyCollision(true);
	BookComponent->SetSimulatePhysics(true);
	BookComponent->SetMassOverrideInKg(NAME_None, 3.0f, true);
	BookComponent->SetEnableGravity(false);
}

void ARangedProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &ARangedProjectile::DestroyProjectile, ProjectileInfo.fLifeSpan, false);
}

void ARangedProjectile::HitTarget()
{
	if (MyPlayer)
	{
		//Add health or blah blah
	}
}

void ARangedProjectile::SetFireVector(FVector VectorToSet)
{
	FireVector = VectorToSet;
}

void ARangedProjectile::MoveProjectile()
{
	BookComponent->SetSimulatePhysics(true);

	BookComponent->AddImpulse(FireVector * ProjectileInfo.fTravelSpeed);
}

void ARangedProjectile::DestroyProjectile()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Destroy();
}

void ARangedProjectile::Stop()
{
	BookComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

void ARangedProjectile::SetPlayer(ADA_Character & CharacterToSet)
{
	MyPlayer = &CharacterToSet;
}


void ARangedProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABossBase* HitBoss = Cast<ABossBase>(OtherActor);

		if (HitBoss != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Boss"));
			HitBoss->ApplyDamage(ProjectileInfo.fDamage);

			if (ProjectileInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(ProjectileInfo.fLeechPercent * ProjectileInfo.fDamage);
			}

			return;
		}

		ABossMinion* HitMinion = Cast<ABossMinion>(OtherActor);

		if (HitMinion != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Minion"));
			HitMinion->ApplyDamage(ProjectileInfo.fDamage);

			if (ProjectileInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(ProjectileInfo.fLeechPercent * ProjectileInfo.fDamage);
			}

			return;
		}

		ABossLauncher* HitLauncher = Cast<ABossLauncher>(OtherActor);

		if (HitLauncher != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Launcher"));
			HitLauncher->ApplyDamage(ProjectileInfo.fDamage);

			if (ProjectileInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(ProjectileInfo.fLeechPercent * ProjectileInfo.fDamage);
			}

			return;
		}
	}
}

