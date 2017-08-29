// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldEquipComponent.h"
#include "BossProjectile.h"

UShieldEquipComponent::UShieldEquipComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UShieldEquipComponent::OnOverlapBegin);

	bGenerateOverlapEvents = false;
}

void UShieldEquipComponent::Block()
{
	StateSwitch(EShieldState::SS_Blocking);
}

void UShieldEquipComponent::UnBlock()
{
	StateSwitch(EShieldState::SS_Side);
}

void UShieldEquipComponent::SetIdle(FVector InVec, FRotator InRot)
{
	IdlePosition = InVec;
	IdleRotation = InRot;
}

void UShieldEquipComponent::SetBlocking(FVector InVec, FRotator InRot)
{
	BlockPosition = InVec;
	BlockRotation = InRot;
}

void UShieldEquipComponent::SetPlayer(ADA_Character &InPlayer)
{
	MyPlayer = &InPlayer;
}

void UShieldEquipComponent::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor)
	{
		ABossProjectile* InComingProjectile = Cast<ABossProjectile>(OtherActor);

		if (InComingProjectile)
		{
			InComingProjectile->DestroyProjectile();
		}
	}

}

void UShieldEquipComponent::StateSwitch(EShieldState SwitchState)
{
	CurrentState = SwitchState;

	switch (CurrentState)
	{
	case EShieldState::SS_Blocking:

		SetWorldLocation(BlockPosition);
		SetWorldRotation(BlockRotation);

		bGenerateOverlapEvents = true;

		return;

	case EShieldState::SS_Side:

		SetWorldLocation(IdlePosition);
		SetWorldRotation(IdleRotation);

		bGenerateOverlapEvents = false;

		return;

	case EShieldState::SS_Max:

		return;
	}

}
