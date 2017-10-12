// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "ArenaEndDoor.generated.h"


UENUM()
enum class EDoorState : uint8
{
	DS_ArenaEnd,
	DS_SafeArena,
	DS_Max
};

class ADA_Character;
class AArenaMapActor;
class UPaperFlipbookComponent;

UCLASS()
class DUNGEON_ASSAULT_UE4_API AArenaEndDoor : public APaperFlipbookActor
{
	GENERATED_BODY()

	AArenaEndDoor();
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Door Type")
	EDoorState CurrentState = EDoorState::DS_ArenaEnd;

	void ActivateDoor();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

private:
	UPaperFlipbookComponent* BookComponent;
};
