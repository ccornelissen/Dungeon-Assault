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

		if (Health < 80)
		{
			PlayerHealthBar->SetFillColorAndOpacity(MidHealthColor);
		}
		else if (Health < 30)
		{
			PlayerHealthBar->SetFillColorAndOpacity(LowHealthColor);
		}
		else
		{
			PlayerHealthBar->SetFillColorAndOpacity(FullHealthColor);
		}
	}
}





