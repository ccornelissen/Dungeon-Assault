// Fill out your copyright notice in the Description page of Project Settings.

#include "BossProjectile.h"
#include "DA_Character.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "EngineUtils.h"

ABossProjectile::ABossProjectile()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement Component"));
	ProjectileMovement->bAutoActivate = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(FName("Projectile Collision"));
	SphereCollision->bGenerateOverlapEvents = true;
}

void ABossProjectile::BeginPlay()
{
	GetWorld()->GetTimerManager().SetTimer(LifeTimerHandle, this, &ABossProjectile::Explode, fLifeSpan, false);

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}

	

	MoveProjectile();
	
}

// Called every frame
void ABossProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveProjectile();
}

void ABossProjectile::MoveProjectile()
{
	ProjectileMovement->Activate(true);

	if (Player)
	{
		ProjectileMovement->SetVelocityInLocalSpace(GetActorForwardVector() * fMovementSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Projectile isn't get a reference to the player"));
	}
}

void ABossProjectile::Explode()
{
	SphereCollision->SetSphereRadius(SphereCollision->GetScaledSphereRadius() * fExplositionScale, true);

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

void ABossProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ADA_Character* HitCharacter = Cast<ADA_Character>(OtherActor);

	if (HitCharacter)
	{
		//Apply damage
	}
}
