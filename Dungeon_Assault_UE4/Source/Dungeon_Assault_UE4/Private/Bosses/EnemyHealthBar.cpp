// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyHealthBar.h"
#include "ProgressBar.h"

void UEnemyHealthBar::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEnemyHealthBar::UpdateHealthBar(float Health)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Health / fMaxHealth);

		if (HealthBar->Percent < 0.3)
		{
			HealthBar->SetFillColorAndOpacity(LowHealthColor);
		}
		else if (HealthBar->Percent < 0.8)
		{
			HealthBar->SetFillColorAndOpacity(MidHealthColor);
		}
		else
		{
			HealthBar->SetFillColorAndOpacity(FullHealthColor);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No health bar set on enemy UI component"));
	}
}
