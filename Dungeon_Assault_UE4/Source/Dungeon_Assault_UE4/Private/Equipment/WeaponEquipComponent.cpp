// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEquipComponent.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"

UWeaponEquipComponent::UWeaponEquipComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UWeaponEquipComponent::OnOverlapBegin);
}

void UWeaponEquipComponent::Attack()
{
	if (bCanSwing)
	{
		bCanSwing = false;
		bGenerateOverlapEvents = true;

		AnimSwitch(EWeaponAnimState::AS_Swing);

		StartLoc = GetComponentLocation();

		FVector NewLoc = FVector(StartLoc.X + 40.0f, StartLoc.Y, StartLoc.Z);

		SetWorldLocation(NewLoc);

		SetWorldLocation(StartLoc);
	}
}

void UWeaponEquipComponent::SetWeapon()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	SetFlipbook(WeaponInfo.IdleBook);
}

float UWeaponEquipComponent::GetLeechPercent()
{
	return WeaponInfo.fLeechPercent;
}

bool UWeaponEquipComponent::CanDeflect()
{
	return WeaponInfo.bCanDeflect;
}

void UWeaponEquipComponent::SetPlayer(ADA_Character & CharacterToSet)
{
	MyPlayer = &CharacterToSet;
}

void UWeaponEquipComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABossBase* HitBoss = Cast<ABossBase>(OtherActor);

		if (HitBoss != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Boss"));
			HitBoss->ApplyDamage(WeaponInfo.fWeaponDamage);
			bGenerateOverlapEvents = false;

			if (WeaponInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(WeaponInfo.fLeechPercent * WeaponInfo.fWeaponDamage);
			}
		}

		ABossLauncher* HitLauncher = Cast<ABossLauncher>(OtherActor);

		if (HitLauncher != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Launcher"));
			HitLauncher->ApplyDamage(WeaponInfo.fWeaponDamage);
			bGenerateOverlapEvents = false;

			if (WeaponInfo.fLeechPercent > 0 && MyPlayer != nullptr)
			{
				UE_LOG(LogTemp, Warning, TEXT("Leeching"));

				MyPlayer->Heal(WeaponInfo.fLeechPercent * WeaponInfo.fWeaponDamage);
			}
		}
	}
}

void UWeaponEquipComponent::AnimSwitch(EWeaponAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case EWeaponAnimState::AS_Idle:

		bGenerateOverlapEvents = false;

		if (WeaponInfo.IdleBook != nullptr)
		{
			SetFlipbook(WeaponInfo.IdleBook);
		}

		bCanSwing = true;

		return;

	case EWeaponAnimState::AS_Swing:

		if (WeaponInfo.SwingBook != nullptr)
		{
			SetFlipbook(WeaponInfo.SwingBook);
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &UWeaponEquipComponent::SwitchToIdle, WeaponInfo.fSwingTimer, false);
		
		return;
	}
}

void UWeaponEquipComponent::SwitchToIdle()
{
	AnimSwitch(EWeaponAnimState::AS_Idle);
}


