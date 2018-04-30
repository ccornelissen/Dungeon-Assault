// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "RangedProjectile.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FProjectileVariables
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float fTravelSpeed = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float fDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Specials")
	float fLeechPercent = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Specials")
	float fPoisonDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	bool bExplodes = false;

	UPROPERTY(EditDefaultsOnly, Category = "Explosion")
	float fExplosionDamage = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Life")
	float fLifeSpan = 15.0f;
};

class UProjectileMovementComponent;
class USphereComponent;
class UPaperFlipbookComponent;
class ADA_Character;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ARangedProjectile : public APaperFlipbookActor
{
	GENERATED_BODY()

	ARangedProjectile();
	
	void HitTarget();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void SetFireVector(FVector VectorToSet);

	void MoveProjectile();

	void DestroyProjectile();

	void Stop();

	void SetPlayer(ADA_Character &CharacterToSet);

	UPaperFlipbookComponent* BookComponent;

	UPROPERTY(EditDefaultsOnly, Category = "WeaponInfo")
	FProjectileVariables ProjectileInfo;

protected:
	virtual void BeginPlay() override;
	
private:
	FVector FireVector;

	FTimerHandle LifeTimerHandle;

	FTimerHandle AnimTimerHandle;

	ADA_Character* MyPlayer;
	
};
