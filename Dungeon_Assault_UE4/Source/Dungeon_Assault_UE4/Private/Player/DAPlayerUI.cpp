// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerUI.h"
#include "ProgressBar.h"

void UDAPlayerUI::NativeConstruct()
{
	Super::NativeConstruct();
}

void UDAPlayerUI::UpdateHealthBar(float Health)
{
	if (PlayerHealthBar)
	{
		PlayerHealthBar->SetPercent(Health / fPlayerMaxHealth);

		if (PlayerHealthBar->Percent < 0.3)
		{
			PlayerHealthBar->SetFillColorAndOpacity(LowHealthColor);
		}
		else if (PlayerHealthBar->Percent < 0.8)
		{
			PlayerHealthBar->SetFillColorAndOpacity(MidHealthColor);
		}
		else
		{
			PlayerHealthBar->SetFillColorAndOpacity(FullHealthColor);
		}
	}
}





