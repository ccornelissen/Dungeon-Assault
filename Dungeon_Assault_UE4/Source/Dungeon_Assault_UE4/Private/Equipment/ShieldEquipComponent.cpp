// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldEquipComponent.h"
#include "BossProjectile.h"

UShieldEquipComponent::UShieldEquipComponent()
{
	OnComponentBeginOverlap.AddDynamic(this, &UShieldEquipComponent::OnOverlapBegin);

	bGenerateOverlapEvents = false;
}

void UShieldEquipComponent::SetShield()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	SetFlipbook(ShieldInfo.IdleBook);
}

void UShieldEquipComponent::Block()
{
	StateSwitch(EShieldState::SS_Blocking);
}

void UShieldEquipComponent::UnBlock()
{
	StateSwitch(EShieldState::SS_Side);
}

void UShieldEquipComponent::SetIdlePoint(USceneComponent &SceneRef)
{
	IdlePoint = &SceneRef;
}

void UShieldEquipComponent::SetBlockingPoint(USceneComponent &SceneRef)
{
	BlockingPoint = &SceneRef;
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
			UE_LOG(LogTemp, Warning, TEXT("Shielding Projectile"))

			InComingProjectile->Stop();
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

		if (BlockingPoint)
		{
			FVector BlockPosition = BlockingPoint->GetComponentLocation();

			FRotator BlockRotation = BlockingPoint->GetComponentRotation();

			SetWorldLocation(BlockPosition);
			SetWorldRotation(BlockRotation);
		}

		bGenerateOverlapEvents = true;

		return;

	case EShieldState::SS_Side:

		if (IdlePoint)
		{
			FVector IdlePosition = IdlePoint->GetComponentLocation();
			FRotator IdleRotation = IdlePoint->GetComponentRotation();

			SetWorldLocation(IdlePosition);
			SetWorldRotation(IdleRotation);
		}

		bGenerateOverlapEvents = false;

		return;

	case EShieldState::SS_Max:

		return;
	}

}
