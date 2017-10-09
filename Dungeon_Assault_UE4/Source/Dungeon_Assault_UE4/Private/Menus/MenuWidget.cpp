// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "Button.h"
#include "WeaponEquipComponent.h"
#include "ShieldEquipComponent.h"
#include "ArmorEquipComponent.h"
#include "HelmetEquipComponent.h"
#include "DASaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SaveGameBP)
	{
		SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::CreateSaveGameObjectFromBlueprint(SaveGameBP->GetDefaultObject<UBlueprint>()));
	}
}

///////////////////////////
//GENERAL//
///////////////////////////

void UMenuWidget::SetHoveredColor(UTextBlock* TextToSet)
{
	if (TextToSet)
	{
		TextToSet->SetColorAndOpacity(HoveredColor);
	}
	
}

void UMenuWidget::SetUnhoveredColor(UTextBlock* TextToSet)
{
	if (TextToSet)
	{
		TextToSet->SetColorAndOpacity(UnhoveredColor);
	}
}

///////////////////////////
//Options//
///////////////////////////


void UMenuWidget::ChangeResolution(float fRes)
{
	if (fRes > 0.1f)
	{
		float fX = (1920 * fRes)/1920;
		float fY = (1080 * fRes)/1080;

		FString ResString;

		
		(fX > fY) ? ResString = FString::SanitizeFloat(fX * 100) : ResString = FString::SanitizeFloat(fY * 100);

		sResolution = FString(TEXT("r.ScreenPercentage "));

		sResolution += ResString;
	}
}

void UMenuWidget::ChangeMusicMultiplier(float fMulti)
{
	//Save the float to the player
	float fTemp = fMulti;

	UE_LOG(LogTemp, Warning, TEXT("%f"), fTemp);
}

void UMenuWidget::ChangeSFXMultiplier(float fMulti)
{
	//Save the float to the player
	float fTemp = fMulti;

	UE_LOG(LogTemp, Warning, TEXT("%f"), fTemp);
}

void UMenuWidget::SetDynamicResolution(EDynamicResState StateToSet)
{
	CurDynamicResState = StateToSet;
}

void UMenuWidget::SetControlState(EControlState StateToSet)
{
	CurControlState = StateToSet;
}

void UMenuWidget::ApplyOptions()
{
	APlayerController* PlayerControl = GetWorld()->GetFirstPlayerController();

	if (PlayerControl)
	{
		PlayerControl->ConsoleCommand(*sResolution, true);
	}
}

///////////////////////////
//Equipment Screen//
///////////////////////////

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

///////////////////////////
//Store//
///////////////////////////

void UMenuWidget::BuyCoins(int CoinsPurchased)
{
	//Check if player has required funds/follow purchase flow
	bool bSufficentFunds = true;

	if (bSufficentFunds == true)
	{
		iPlayerFunds += CoinsPurchased;

		UE_LOG(LogTemp, Warning, TEXT("Players Current Funds: %d"), iPlayerFunds);
	}
}

void UMenuWidget::BuyAdFree(UButton* AdFreeButton, UImage* AdFreeImage)
{
	//Check if player has required funds/follow purchase flow
	bool bSufficentFunds = true;

	if (bSufficentFunds == true)
	{
		//Set player variable bAdfree to true
		UE_LOG(LogTemp, Warning, TEXT("This player now owns the game!"));

		if (AdFreeButton)
		{
			AdFreeButton->SetVisibility(ESlateVisibility::Hidden);
			AdFreeButton->SetIsEnabled(false);
		}

		if (AdFreeImage)
		{
			AdFreeImage->SetIsEnabled(true);
			AdFreeImage->SetVisibility(ESlateVisibility::Visible);
		}
	}

}





