// Fill out your copyright notice in the Description page of Project Settings.

#include "BossBase.h"


// Sets default values
ABossBase::ABossBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABossBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossBase::ApplyDamage(float Damage)
{
	fBossHealth -= Damage;

	DeathCheck();
}

void ABossBase::DeathCheck()
{
	if (fBossHealth <= 0)
	{
		Destroy();
	}
}

