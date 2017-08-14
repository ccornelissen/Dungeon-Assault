// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossBase.generated.h"

class UEnemyHealthBar;
class ABossLauncher;
class ABossMelee;
class USceneComponent;

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

	UFUNCTION(BlueprintImplementableEvent, Category = "BossComponents")
	void SetComponents();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UEnemyHealthBar* BaseHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BossComponents")
	TArray<USceneComponent*> ArmComponents;

	UPROPERTY(EditDefaultsOnly, Category = "BossComponents")
	TSubclassOf<ABossLauncher> LauncherToSpawn = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "BossComponents")
	TSubclassOf<ABossMelee> MeleeToSpawn = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BossComponents")
	USceneComponent* TailComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BossComponents")
	USceneComponent* HeadComponent;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float fBossHealth = 100.0f;
	
	void DeathCheck();

	TArray<AActor*> SpawnedActors;

	void SpawnComponents();
};
