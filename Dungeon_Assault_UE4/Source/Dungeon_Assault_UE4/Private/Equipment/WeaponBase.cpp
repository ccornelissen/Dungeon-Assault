// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponBase.h"
#include "EquipmentBase.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"
#include "BossMinion.h"

AWeaponBase::AWeaponBase()
{
	MyFlipbookComp = FindComponentByClass<UPaperFlipbookComponent>();

	MyFlipbookComp->bGenerateOverlapEvents = false;

	MyFlipbookComp->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBase::OnOverlapBegin);

	MyEquipType = EEquipmentType::ET_Melee;
	MyHandType = EHandType::HT_Main;
}

void AWeaponBase::Attack()
{
	Super::Attack();

	if (bCanAttack)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attacking!"));

		bCanAttack = false;
		MyFlipbookComp->bGenerateOverlapEvents = true;

		AnimSwitch(EEquipAnimState::AS_Attacking);

		StartLoc = GetActorLocation();

		FVector NewLoc = FVector(StartLoc.X + 40.0f, StartLoc.Y, StartLoc.Z);

		SetActorLocation(NewLoc);

		SetActorLocation(StartLoc);
	}
}

void AWeaponBase::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABossBase* HitBoss = Cast<ABossBase>(OtherActor);

		if (HitBoss != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Boss"));
			HitBoss->ApplyDamage(EquipmentInfo.fWeaponDamage);
			MyFlipbookComp->bGenerateOverlapEvents = false;

			if (EquipmentInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(EquipmentInfo.fLeechPercent * EquipmentInfo.fWeaponDamage);
			}

			return;
		}

		ABossMinion* HitMinion = Cast<ABossMinion>(OtherActor);

		if (HitMinion != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Minion"));
			HitMinion->ApplyDamage(EquipmentInfo.fWeaponDamage);
			MyFlipbookComp->bGenerateOverlapEvents = false;

			if (EquipmentInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(EquipmentInfo.fLeechPercent * EquipmentInfo.fWeaponDamage);
			}

			return;
		}

		ABossLauncher* HitLauncher = Cast<ABossLauncher>(OtherActor);

		if (HitLauncher != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Launcher"));
			HitLauncher->ApplyDamage(EquipmentInfo.fWeaponDamage);
			MyFlipbookComp->bGenerateOverlapEvents = false;

			if (EquipmentInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(EquipmentInfo.fLeechPercent * EquipmentInfo.fWeaponDamage);
			}

			return;
		}
	}
}

void AWeaponBase::AnimSwitch(EEquipAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case EEquipAnimState::AS_Idle:

		MyFlipbookComp->bGenerateOverlapEvents = false;

		if (EquipmentInfo.IdleBook != nullptr)
		{
			MyFlipbookComp->SetFlipbook(EquipmentInfo.IdleBook);
		}

		bCanAttack = true;

		return;

	case  EEquipAnimState::AS_Attacking:

		if (EquipmentInfo.AttackBook != nullptr)
		{
			MyFlipbookComp->SetFlipbook(EquipmentInfo.AttackBook);
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &AEquipmentBase::SwitchToIdle, EquipmentInfo.fAttackTimer, false);

		return;
	}
}
