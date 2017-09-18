// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "WeaponEquipComponent.h"
#include "ShieldEquipComponent.h"
#include "ArmorEquipComponent.h"
#include "HelmetEquipComponent.h"

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

int32 UMenuWidget::ChangeEquipment(UImage* ImageToSet, TArray<TSubclassOf<UPaperFlipbookComponent>> EquipmentArray, int32 i)
{
	if (EquipmentArray.Num() > 0)
	{
		if (i > EquipmentArray.Num() - 1)
		{
			i = 0;
		}
		else if (i < 0)
		{
			i = EquipmentArray.Num() - 1;
		}

		if (EquipmentArray.IsValidIndex(i))
		{
			if (EquipmentArray[i]->IsChildOf(UWeaponEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = EquipmentArray[i]->GetDefaultObject<UWeaponEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}

			if (EquipmentArray[i]->IsChildOf(UShieldEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = EquipmentArray[i]->GetDefaultObject<UShieldEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}

			if (EquipmentArray[i]->IsChildOf(UHelmetEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = EquipmentArray[i]->GetDefaultObject<UHelmetEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}

			if (EquipmentArray[i]->IsChildOf(UArmorEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = EquipmentArray[i]->GetDefaultObject<UArmorEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}
		}
	}

	return i;
}



