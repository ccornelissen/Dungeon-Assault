// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookComponent.h"
#include "ShieldEquipComponent.generated.h"

/**
 * 
 */

class ADA_Character;

UENUM()
enum class EShieldState : uint8
{
	SS_Side,
	SS_Blocking,
	SS_Max
};


USTRUCT(BlueprintType)
struct FShieldVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	bool bCanReflect = false;

	UPROPERTY(EditDefaultsOnly, Category = "Shield")
	float fBlockPercent = 100.0f;
};


UCLASS(Blueprintable)
class DUNGEON_ASSAULT_UE4_API UShieldEquipComponent : public UPaperFlipbookComponent
{
	GENERATED_BODY()

	UShieldEquipComponent();

public:

	void Block();

	void UnBlock();

	void SetIdle(FVector InVec, FRotator InRot);

	void SetBlocking(FVector InVec, FRotator InRot);

	UPROPERTY(EditDefaultsOnly, Category = "ShieldInfo")
	FShieldVariables ShieldInfo;

	void SetPlayer(ADA_Character &InPlayer);

private:
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FVector IdlePosition;
	FRotator IdleRotation;

	FVector BlockPosition;
	FRotator BlockRotation;

	ADA_Character* MyPlayer = nullptr;
	
	EShieldState CurrentState = EShieldState::SS_Side;
	
	void StateSwitch(EShieldState SwitchState);
};
