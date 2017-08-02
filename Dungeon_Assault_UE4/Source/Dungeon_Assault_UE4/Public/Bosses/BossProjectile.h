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

UCLASS()
class DUNGEON_ASSAULT_UE4_API ABossProjectile : public APaperFlipbookActor
{
	GENERATED_BODY()

	ABossProjectile();

	void MoveProjectile();
	
	void Explode();

	void DestroyProjectile();

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereCollision = nullptr;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


public:
	void SetPlayer(ADA_Character& PlayerToSet);

	
protected:
	
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovement = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fExplositionScale = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fDamage = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fMovementSpeed = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fLifeSpan = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	float fExplosionAnimationLength = 0.5f;

private:
	ADA_Character* Player;
	
	FTimerHandle LifeTimerHandle;

	FTimerHandle AnimTimerHandle;
};
