// Fill out your copyright notice in the Description page of Project Settings.

#include "BossProjectile.h"
#include "DA_Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"
#include "PaperFlipbookComponent.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Exploding"));

	//SphereCollision->SetSphereRadius(SphereCollision->GetScaledSphereRadius() * fExplositionScale, true);

	GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
}

void ABossProjectile::DestroyProjectile()
{
	Destroy();
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
	ADA_Character* HitCharacter = Cast<ADA_Character>(OtherActor);

	if (HitCharacter)
	{
		HitCharacter->DATakeDamage(fDamage);

		BookComponent->SetPhysicsLinearVelocity(FVector::ZeroVector);

		GetWorld()->GetTimerManager().SetTimer(AnimTimerHandle, this, &ABossProjectile::DestroyProjectile, fExplosionAnimationLength, false);
	}
}
