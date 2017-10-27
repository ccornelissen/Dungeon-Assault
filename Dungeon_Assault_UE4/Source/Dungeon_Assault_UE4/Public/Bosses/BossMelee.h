// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BossMelee.generated.h"

UENUM()
enum class EBossMeleeAnimState : uint8
{
	AS_Idle,
	AS_Swing,
	AS_Max
};

class UPaperFlipbookComponent;
class UPaperFlipbook;
class ADACoin;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossMelee : public APaperFlipbookActor
{
	GENERATED_BODY()

	ABossMelee();

	void Attack();

	UPaperFlipbookComponent* BookComponent;
	
	//How often does the boss swing
	FTimerHandle SwingTimerHandle;

	//To reset animation after its complete
	FTimerHandle SwingResetHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float fDamage = 20.0f;

	float fMaxDamage;

	//How ofter the boss will swing
	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float fSwingReload = 10.0f;
	
	//How long it takes for the boss to swing
	UPROPERTY(EditDefaultsOnly, Category = "Melee")
	float fSwingAnimLength = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* IdleBook;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UPaperFlipbook* SwingBook;

	EBossMeleeAnimState CurrentAnimState = EBossMeleeAnimState::AS_Idle;

	void AnimSwitch(EBossMeleeAnimState SwitchState);

	void SwitchToIdle();

	UPROPERTY(EditDefaultsOnly, Category = "Player Coin")
	TSubclassOf<ADACoin> Coin = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Player Coin")
	float CoinModifier = 5.0f;

private:
	void DestroyMelee();

	void SpawnCoin();

};
