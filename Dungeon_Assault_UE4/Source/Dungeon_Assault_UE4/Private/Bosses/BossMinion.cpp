// Fill out your copyright notice in the Description page of Project Settings.

#include "BossMinion.h"
#include "DA_Character.h"
#include "Components/CapsuleComponent.h"


// Sets default values
ABossMinion::ABossMinion()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ABossMinion::ApplyDamage(float DamageToTake)
{
	MinionInfo.fMinionHealth -= DamageToTake;

	if (MinionInfo.fMinionHealth < 0)
	{
		Destroy();
	}
}

// Called when the game starts or when spawned
void ABossMinion::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABossMinion::Attack(ADA_Character* ThePlayer)
{
	UE_LOG(LogTemp, Warning, TEXT("Minion Damaging player"));

	ThePlayer->DATakeDamage(MinionInfo.fMinionDamage);

	if (MinionInfo.bDieAfterAttack)
	{
		Destroy();
	}
}

// Called every frame
void ABossMinion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

