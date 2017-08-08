// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossBase.generated.h"

class UEnemyHealthBar;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossBase();

	virtual void Tick(float DeltaTime) override;

	void ApplyDamage(float Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UEnemyHealthBar* BaseHealthBar = nullptr;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float fBossHealth = 100.0f;
	
	void DeathCheck();
};
