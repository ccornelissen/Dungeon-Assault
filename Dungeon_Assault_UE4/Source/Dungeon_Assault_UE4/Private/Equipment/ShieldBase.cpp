// Fill out your copyright notice in the Description page of Project Settings.

#include "ShieldBase.h"
#include "EquipmentBase.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"
#include "BossMinion.h"

AShieldBase::AShieldBase()
{
	MyFlipbookComp = FindComponentByClass<UPaperFlipbookComponent>();

	MyFlipbookComp->bGenerateOverlapEvents = false;

	MyFlipbookComp->OnComponentBeginOverlap.AddDynamic(this, &AShieldBase::OnOverlapBegin);

	MyEquipType = EEquipmentType::ET_Shield;
	MyHandType = EHandType::HT_Off;
}

void AShieldBase::Block()
{
	AnimSwitch(EEquipAnimState::AS_Blocking);
}

void AShieldBase::UnBlock()
{
	AnimSwitch(EEquipAnimState::AS_Idle);
}

void AShieldBase::SetIdlePoint(USceneComponent &SceneRef)
{
	IdlePoint = &SceneRef;
}

void AShieldBase::SetBlockingPoint(USceneComponent &SceneRef)
{
	BlockingPoint = &SceneRef;
}

void AShieldBase::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// //	if (OtherActor)
	// //	{
	// 	//	ABossProjectile* InComingProjectile = Cast<ABossProjectile>(OtherActor);
	// 
	// 	//	if (InComingProjectile)
	// 	//	{
	// 	//		UE_LOG(LogTemp, Warning, TEXT("Shielding Projectile"))
	// //
	// 	//		InComingProjectile->Stop();
	// 	//		InComingProjectile->DestroyProjectile();
	// 	//	}
	// 	//}
	// 
}

void AShieldBase::AnimSwitch(EEquipAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (SwitchState)
	{
	case EEquipAnimState::AS_Blocking:

		if (BlockingPoint)
		{
			FVector BlockPosition = BlockingPoint->GetComponentLocation();

			FRotator BlockRotation = BlockingPoint->GetComponentRotation();

			UE_LOG(LogTemp, Warning, TEXT("Blocking"));

			SetActorLocation(BlockPosition);
			SetActorRotation(BlockRotation);
		}

		MyFlipbookComp->bGenerateOverlapEvents = true;

		return;

	case EEquipAnimState::AS_Idle:

		if (IdlePoint)
		{
			FVector IdlePosition = IdlePoint->GetComponentLocation();
			FRotator IdleRotation = IdlePoint->GetComponentRotation();

			UE_LOG(LogTemp, Warning, TEXT("UnBlocking"));

			SetActorLocation(IdlePosition);
			SetActorRotation(IdleRotation);
		}

		MyFlipbookComp->bGenerateOverlapEvents = false;

		return;
	}
}





