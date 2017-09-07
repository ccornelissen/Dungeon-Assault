// Fill out your copyright notice in the Description page of Project Settings.

#include "BossProjectile.h"
#include "DA_Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "PaperFlipbookComponent.h"
#include "WeaponEquipComponent.h"
#include "ShieldEquipComponent.h"

ABossProjectile::ABossProjectile()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &ABossProjectile::OnOverlapBegin);
	BookComponent->SetNotifyRigidBodyCollision(true);
	BookComponent->SetSimulatePhysics(true);
	BookComponent->SetMassOverrideInKg(NAME_None, 3.0f, true);
	BookComponent->SetEnableGravity(false);
	
}

void ABossProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &ABossProjectile::Explode, fLifeSpan, false);
}

void ABossProjectile::MoveProjectile()
{
	if (Player)
	{
		BookComponent->SetSimulatePhysics(true);

		BookComponent->AddImpulse(FireVector * fMovementForce);

	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile isn't get a reference to the player"));
	}
}

void ABossProjectile::Explode()
{
	GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
}

void ABossProjectile::DestroyProjectile()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	Destroy();
}

void ABossProjectile::Stop()
{
	BookComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);
}


void ABossProjectile::SetPlayer(ADA_Character& PlayerToSet)
{
	Player = &PlayerToSet;
}

void ABossProjectile::SetFireVector(FVector VectorToSet)
{
	FireVector = VectorToSet;
}

void ABossProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	UShieldEquipComponent* HitComp = Cast<UShieldEquipComponent>(OtherComp);

	UWeaponEquipComponent* WeapComp = Cast<UWeaponEquipComponent>(OtherComp);

	ADA_Character* HitCharacter = Cast<ADA_Character>(OtherActor);

	bool bWeaponDeflect = false;

	if (WeapComp)
	{
		bWeaponDeflect = WeapComp->CanDeflect();
	}

	if (bWeaponDeflect)
	{
		fDamage = 0.0f;

		UE_LOG(LogTemp, Warning, TEXT("Reflecting"));

		Stop();

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
	}
	else if (HitComp)
	{
		fDamage = 0.0f;

		Stop();

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
	}
	else if (HitCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile Damaging player"));
		HitCharacter->DATakeDamage(fDamage);

		Stop();

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
	}
}
