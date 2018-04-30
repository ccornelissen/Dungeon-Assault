// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedEquipComponent.h"
#include "DA_Character.h"
#include "RangedProjectile.h"

URangedEquipComponent::URangedEquipComponent()
{

}

void URangedEquipComponent::Attack()
{
	if (bCanFire && MyPlayer)
	{
		bCanFire = false;

		FVector SpawnLoc = FVector(MyPlayer->GetActorLocation().X, MyPlayer->GetActorLocation().Y, MyPlayer->GetActorLocation().Z);

		if (RangedInfo.Projectile)
		{
			ARangedProjectile* CurProjectile = GetWorld()->SpawnActor<ARangedProjectile>(RangedInfo.Projectile, SpawnLoc, MyPlayer->GetActorRotation());

			CurProjectile->SetFireVector(MyPlayer->GetActorForwardVector());

			CurProjectile->SetPlayer(*MyPlayer);
			CurProjectile->MoveProjectile();

			UE_LOG(LogTemp, Warning, TEXT("Firing!"));
		}
	}
}

void URangedEquipComponent::SetWeapon()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	if (RangedInfo.IdleBook)
	{
		SetFlipbook(RangedInfo.IdleBook);
	}
}

void URangedEquipComponent::SetPlayer(ADA_Character &CharacterToSet)
{
	MyPlayer = &CharacterToSet;
}

void URangedEquipComponent::AnimSwitch(ERangedAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case ERangedAnimState::RAS_Idle:

		if (RangedInfo.IdleBook != nullptr)
		{
			SetFlipbook(RangedInfo.IdleBook);
		}

		bCanFire = true;

		return;

	case ERangedAnimState::RAS_Shoot:

		if (RangedInfo.FireBook != nullptr)
		{
			SetFlipbook(RangedInfo.FireBook);
		}

		AnimSwitch(ERangedAnimState::RAS_Reloading);

		return;

	case ERangedAnimState::RAS_Aiming:

		if (RangedInfo.AimBook != nullptr)
		{
			SetFlipbook(RangedInfo.AimBook);
		}


		return;

	case ERangedAnimState::RAS_Reloading:

		if (RangedInfo.ReloadBook != nullptr)
		{
			SetFlipbook(RangedInfo.ReloadBook);
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &URangedEquipComponent::SwitchToIdle, RangedInfo.fReloadTimer, false);

		return;
	}
}

void URangedEquipComponent::SwitchToIdle()
{
	AnimSwitch(ERangedAnimState::RAS_Idle);
}
