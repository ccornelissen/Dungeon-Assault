// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEquipComponent.h"
#include "BossBase.h"
#include "BossLauncher.h"

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

void UWeaponEquipComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != nullptr)
	{
		ABossBase* HitBoss = Cast<ABossBase>(OtherActor);

		if (HitBoss != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Boss"));
			HitBoss->ApplyDamage(fWeaponDamage);
			bGenerateOverlapEvents = false;
		}

		ABossLauncher* HitLauncher = Cast<ABossLauncher>(OtherActor);

		if (HitLauncher != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Launcher"));
			HitLauncher->ApplyDamage(fWeaponDamage);
			bGenerateOverlapEvents = false;

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

		if (IdleBook != nullptr)
		{
			SetFlipbook(IdleBook);
		}

		bCanSwing = true;

		return;

	case EWeaponAnimState::AS_Swing:

		if (SwingBook != nullptr)
		{
			SetFlipbook(SwingBook);
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &UWeaponEquipComponent::SwitchToIdle, fSwingTimer, false);
		
		return;
	}
}

void UWeaponEquipComponent::SwitchToIdle()
{
	AnimSwitch(EWeaponAnimState::AS_Idle);
}


