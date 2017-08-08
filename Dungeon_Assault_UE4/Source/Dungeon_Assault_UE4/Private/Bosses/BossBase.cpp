// Fill out your copyright notice in the Description page of Project Settings.

#include "BossBase.h"
#include "EnemyHealthBar.h"
#include "WidgetComponent.h"

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

	UWidgetComponent* WidgetComp = FindComponentByClass<UWidgetComponent>();
	if(WidgetComp)
	{
		BaseHealthBar = Cast<UEnemyHealthBar>(WidgetComp->GetUserWidgetObject());

		if (BaseHealthBar)
		{
			BaseHealthBar->SetHealthBar();
			BaseHealthBar->fMaxHealth = fBossHealth;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cast to health bar failed!"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Lacking the widget comp"));
	}
}

// Called every frame
void ABossBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossBase::ApplyDamage(float Damage)
{
	fBossHealth -= Damage;

	if (BaseHealthBar)
	{
		BaseHealthBar->UpdateHealthBar(fBossHealth);
	}

	DeathCheck();
}

void ABossBase::DeathCheck()
{
	if (fBossHealth <= 0)
	{
		Destroy();
	}
}

