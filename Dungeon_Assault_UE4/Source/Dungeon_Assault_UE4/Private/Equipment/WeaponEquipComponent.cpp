// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponEquipComponent.h"
#include "BossBase.h"

UWeaponEquipComponent::UWeaponEquipComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UWeaponEquipComponent::OnOverlapBegin);
}

void UWeaponEquipComponent::Attack()
{
	bGenerateOverlapEvents = true;

	AnimSwitch(EAnimState::AS_Swing);

	StartLoc = GetComponentLocation();

	FVector NewLoc = FVector(StartLoc.X + 40.0f, StartLoc.Y, StartLoc.Z);

	SetWorldLocation(NewLoc);

	SetWorldLocation(StartLoc);

	bGenerateOverlapEvents = false;
}

void UWeaponEquipComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABossBase* HitBoss = nullptr;

	if (OtherActor != nullptr)
	{
		HitBoss = Cast<ABossBase>(OtherActor);
	}

	if (HitBoss != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit"));
		HitBoss->ApplyDamage(fWeaponDamage);
	}
}

void UWeaponEquipComponent::AnimSwitch(EAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case EAnimState::AS_Idle:

		if (IdleBook != nullptr)
		{
			SourceFlipbook = IdleBook;
		}

		return;

	case EAnimState::AS_Swing:

		if (SwingBook != nullptr)
		{
			SourceFlipbook = SwingBook;
		}

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &UWeaponEquipComponent::SwitchToIdle, fSwingTimer, false);
		
		return;
	}
}

void UWeaponEquipComponent::SwitchToIdle()
{
	AnimSwitch(EAnimState::AS_Idle);
}


