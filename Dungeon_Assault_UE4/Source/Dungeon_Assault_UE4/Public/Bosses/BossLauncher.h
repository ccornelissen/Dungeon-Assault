// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BossLauncher.generated.h"

class ABossProjectile;
class ADA_Character;

/**
 * 
 */
UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossLauncher : public APaperFlipbookActor
{
	GENERATED_BODY()
	
public:
	void FireProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<ABossProjectile> Projectile;
	
	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fReloadTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fHealth = 45.0f;

	FTimerHandle ReloadTimerHandle;

private:
	ADA_Character* Player;
};
