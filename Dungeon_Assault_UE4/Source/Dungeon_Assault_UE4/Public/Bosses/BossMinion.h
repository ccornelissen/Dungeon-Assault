// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossMinion.generated.h"

class ADA_Character;

USTRUCT(BlueprintType)
struct FMinionVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float fMinionDamage = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float fAttackRange = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	bool bDieAfterAttack = true;

	UPROPERTY(EditDefaultsOnly, Category = "Minion")
	float fMinionHealth = 10.0f;
};

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossMinion : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossMinion();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Attack(ADA_Character* ThePlayer);

	UPROPERTY(EditDefaultsOnly, Category = "Minion Variables")
	FMinionVariables MinionInfo;

	void ApplyDamage(float DamageToTake);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	
};
