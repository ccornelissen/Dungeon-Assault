// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMelee.h"
#include "DA_Character.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "ShieldBase.h"
#include "DACoin.h"
#include "Dungeon_Assault_UE4.h"

ABossMelee::ABossMelee()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();
	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossMelee::OnOverlapBegin);
	BookComponent->bGenerateOverlapEvents = false;

}

void ABossMelee::BeginPlay()
{
	Super::BeginPlay();

	fMaxDamage = fDamage;

	GetWorld()->GetTimerManager().SetTimer(SwingTimerHandle, this, &ABossMelee::Attack, fSwingReload);
}

void ABossMelee::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AShieldBase* HitActor = Cast<AShieldBase>(OtherActor);

	ADA_Character* HitCharacter = Cast<ADA_Character>(OtherActor);

	if (HitActor)
	{
		fDamage = 0.0f;
	}
	else if (HitCharacter)
	{
		ADA_Character* Player = Cast<ADA_Character>(OtherActor);

		if (Player)
		{
			Player->DATakeDamage(fDamage);
		}
	}
}

void ABossMelee::Attack()
{
	BookComponent->bGenerateOverlapEvents = true;

	fDamage = fMaxDamage;

	AnimSwitch(EBossMeleeAnimState::AS_Swing);
}

void ABossMelee::AnimSwitch(EBossMeleeAnimState SwitchState)
{
	CurrentAnimState = SwitchState;

	switch (CurrentAnimState)
	{
	case EBossMeleeAnimState::AS_Idle:

		BookComponent->bGenerateOverlapEvents = false;

		if (IdleBook != nullptr)
		{
			BookComponent->SetFlipbook(IdleBook);
		}

		GetWorld()->GetTimerManager().SetTimer(SwingTimerHandle, this, &ABossMelee::Attack, fSwingReload);

		return;

	case EBossMeleeAnimState::AS_Swing:

		if (SwingBook != nullptr)
		{
			BookComponent->SetFlipbook(SwingBook);
		}

		GetWorld()->GetTimerManager().SetTimer(SwingResetHandle, this, &ABossMelee::SwitchToIdle, fSwingAnimLength);

		return;
	}
}

void ABossMelee::SwitchToIdle()
{
	AnimSwitch(EBossMeleeAnimState::AS_Idle);
}

void ABossMelee::DestroyMelee()
{
	SpawnCoin();

	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Destroy();
}

void ABossMelee::SpawnCoin()
{
	UDASaveGame* SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::CreateSaveGameObject(UDASaveGame::StaticClass()));

	SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));

	if (Coin && SaveGameInstance)
	{
		FRotator SpawnRot = FRotator(0.0, -90.0, 90.0);

		FVector SpawnVec = FVector(GetActorLocation().X, GetActorLocation().Y, 50.0);

		ADACoin* SpawnedCoin = GetWorld()->SpawnActor<ADACoin>(Coin, SpawnVec, SpawnRot);

		int32 CoinValue = SaveGameInstance->GameplaySaveData.iLastFloorCompleted * CoinModifier;

		SpawnedCoin->SetValue(CoinValue);
	}
}
