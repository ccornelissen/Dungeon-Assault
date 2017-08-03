// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperFlipbookActor.h"
#include "BossProjectile.generated.h"

/**
 * 
 */
class UProjectileMovementComponent;
class ADA_Character;
class USphereComponent;
class UPaperFlipbookComponent;

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossProjectile : public APaperFlipbookActor
{
	GENERATED_BODY()

	ABossProjectile();

	void MoveProjectile();
	
	void Explode();

	void DestroyProjectile();

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	void SetPlayer(ADA_Character& PlayerToSet);

	
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fExplositionScale = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fMovementForce = 25.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fMaxSpeed = 7500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fLifeSpan = 15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fExplosionAnimationLength = 0.5f;

private:
	ADA_Character* Player;

	UPaperFlipbookComponent* BookComponent;
	
	FTimerHandle LifeTimerHandle;

	FTimerHandle AnimTimerHandle;
};
