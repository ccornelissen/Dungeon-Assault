// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"

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



