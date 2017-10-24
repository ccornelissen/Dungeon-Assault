// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "DACoin.generated.h"

class UPaperFlipbookComponent;
/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API ADACoin : public APaperFlipbookActor
{
	GENERATED_BODY()

	ADACoin();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
public:
	void SetValue(int32 ValueToSet);

private:
	int32 iValue = 0;

	UPaperFlipbookComponent* BookComponent = nullptr;
	
};
