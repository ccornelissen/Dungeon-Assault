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

		if (Health < 80)
		{
			HealthBar->SetFillColorAndOpacity(MidHealthColor);
		}
		else if (Health < 30)
		{
			HealthBar->SetFillColorAndOpacity(LowHealthColor);
		}
		else
		{
			HealthBar->SetFillColorAndOpacity(FullHealthColor);
		}
	}
}
