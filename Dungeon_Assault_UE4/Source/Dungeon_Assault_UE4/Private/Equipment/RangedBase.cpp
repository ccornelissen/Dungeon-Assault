// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedBase.h"
#include "EquipmentBase.h"
#include "DA_Character.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "BossMinion.h"
#include "RangedProjectile.h"


ARangedBase::ARangedBase()
{
	MyFlipbookComp = FindComponentByClass<UPaperFlipbookComponent>();

	MyFlipbookComp->bGenerateOverlapEvents = false;

	MyEquipType = EEquipmentType::ET_Ranged;
	MyHandType = EHandType::HT_Off;
}


void ARangedBase::Attack()
{
	if (bCanAttack && MyPlayer)
	{
		bCanAttack = false;

		FVector SpawnLoc = FVector(MyPlayer->GetActorLocation().X, MyPlayer->GetActorLocation().Y, MyPlayer->GetActorLocation().Z);

		if (EquipmentInfo.Projectile)
		{
			ARangedProjectile* CurProjectile = GetWorld()->SpawnActor<ARangedProjectile>(EquipmentInfo.Projectile, SpawnLoc, MyPlayer->GetActorRotation());

			CurProjectile->SetFireVector(MyPlayer->GetActorForwardVector());

			CurProjectile->SetPlayer(*MyPlayer);
			CurProjectile->MoveProjectile();

			UE_LOG(LogTemp, Warning, TEXT("Firing!"));
		}
	}
}

void ARangedBase::AnimSwitch(EEquipAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case EEquipAnimState::AS_Idle:

		if (EquipmentInfo.IdleBook != nullptr)
		{
			MyFlipbookComp->SetFlipbook(EquipmentInfo.IdleBook);
		}

		bCanAttack = true;

		return;

	case EEquipAnimState::AS_Attacking:

		if (EquipmentInfo.AttackBook != nullptr)
		{
			MyFlipbookComp->SetFlipbook(EquipmentInfo.AttackBook);
		}

		AnimSwitch(EEquipAnimState::AS_Reloading);

		return;

	case EEquipAnimState::AS_Reloading:

		if (EquipmentInfo.ReloadBook != nullptr)
		{
			MyFlipbookComp->SetFlipbook(EquipmentInfo.ReloadBook);
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &AEquipmentBase::SwitchToIdle, EquipmentInfo.fAttackTimer, false);

		return;
	}
}