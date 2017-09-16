// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"
#include "Image.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMenuWidget::SetHoveredColor(UTextBlock* TextToSet)
{
	TextToSet->SetColorAndOpacity(HoveredColor);
}

void UMenuWidget::SetUnhoveredColor(UTextBlock* TextToSet)
{
	TextToSet->SetColorAndOpacity(UnhoveredColor);
}

void UMenuWidget::ChangeEquipment(UImage* ImageToSet, TArray<UImage*> ImageArray, int i)
{
	if (ImageArray.Num() > 0)
	{
		if (i > ImageArray.Num() - 1)
		{
			i = 0;
		}
		else if (i < 0)
		{
			i = ImageArray.Num() - 1;
		}

		if (ImageArray.IsValidIndex(i))
		{
			ImageToSet = ImageArray[i];
		}
	}
}



