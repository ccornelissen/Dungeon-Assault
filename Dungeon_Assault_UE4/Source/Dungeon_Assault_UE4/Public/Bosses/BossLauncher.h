// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BossLauncher.generated.h"

class ABossProjectile;
class ADA_Character;
class UEnemyHealthBar;
class ABossBase;

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossLauncher : public APaperFlipbookActor
{
	GENERATED_BODY()
	ABossLauncher();
	
public:
	void FireProjectile();

	void ApplyDamage(float fDamage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	UEnemyHealthBar* LauncherHealthBar = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Launcher")
	float fLauncherHealth = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABossProjectile> Projectile = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fSpawnDistance = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fReloadTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fHealth = 45.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	USceneComponent* FireFromComponent = nullptr;

	FTimerHandle ReloadTimerHandle;

private:
	void DestroyLauncher();

	ADA_Character* Player;
	ABossBase* MainBoss;
};
