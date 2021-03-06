// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaEndDoor.h"
#include "Dungeon_Assault_UE4.h"
#include "DA_Character.h"
#include "PaperFlipbookComponent.h"

AArenaEndDoor::AArenaEndDoor()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &AArenaEndDoor::OnOverlapBegin);

	BookComponent->bGenerateOverlapEvents = false;

	BookComponent->SetHiddenInGame(true);
}

void AArenaEndDoor::ActivateDoor()
{
	BookComponent->SetHiddenInGame(false);
	BookComponent->bGenerateOverlapEvents = true;
}

void AArenaEndDoor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ADA_Character* OverlapCharacter = Cast<ADA_Character>(OtherActor);

	if (OtherActor)
	{
		if (CurrentState == EDoorState::DS_ArenaEnd)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("SafeArena")));
		}
		else if (CurrentState == EDoorState::DS_SafeArena)
		{
			UGameplayStatics::OpenLevel(GetWorld(), FName(TEXT("Test_Arena")));
		}
	}
}
