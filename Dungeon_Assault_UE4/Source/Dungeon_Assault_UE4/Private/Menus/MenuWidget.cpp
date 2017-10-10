// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "Button.h"
#include "Slider.h"
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
}

///////////////////////////
//GENERAL//
///////////////////////////

void UMenuWidget::SetupSaveGame(UDASaveGame * GameSaveInstance)
{
	if (GameSaveInstance)
	{
		SaveGameInstance = GameSaveInstance;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);

		SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
	}
}

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

void UMenuWidget::SaveGame()
{
	if (SaveGameInstance)
	{
		SaveGameInstance->MenuSaveData.iSavedMainWep = iMainWeapon;

		SaveGameInstance->MenuSaveData.iSavedMainOffhand = iMainOffhand;

		SaveGameInstance->MenuSaveData.iSavedHelmet = iHelmets;

		SaveGameInstance->MenuSaveData.iSavedArmor = iArmor;

		SaveGameInstance->MenuSaveData.iSavedSecondaryWeapon = iSecondWeapon;

		SaveGameInstance->MenuSaveData.iSavedSecondaryOffhand = iSecondOffhand;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
	}
}

///////////////////////////
//Options//
///////////////////////////


void UMenuWidget::OptionScreenSetup(USlider * ResSlide, USlider * MusicSlide, USlider * SFXSlide, UButton * EnableDynRes, UButton * DisableDynRes, UButton * StickControl, UButton * TouchControl)
{
	if (ResSlide)
	{
		if (SaveGameInstance)
		{
			ResSlide->SetValue(SaveGameInstance->MenuSaveData.SavedResolution);

			ChangeResolution(ResSlide->Value);
		}
	}

	if (MusicSlide)
	{
		if (SaveGameInstance)
		{
			MusicSlide->SetValue(SaveGameInstance->MenuSaveData.SaveMusicVolume);

			ChangeMusicMultiplier(MusicSlide->Value);
		}
	}

	if (SFXSlide)
	{
		if (SaveGameInstance)
		{
			SFXSlide->SetValue(SaveGameInstance->MenuSaveData.SavedSFXVolume);

			ChangeSFXMultiplier(SFXSlide->Value);
		}
	}

	if (EnableDynRes)
	{
		if (SaveGameInstance)
		{
			if (SaveGameInstance->MenuSaveData.SavedDynamicResState == EDynamicResState::DS_Disabled)
			{
				EnableDynRes->SetBackgroundColor(DisabledColor);
			}
		}
	}

	if (DisableDynRes)
	{
		if (SaveGameInstance)
		{
			if (SaveGameInstance->MenuSaveData.SavedDynamicResState == EDynamicResState::DS_Enabled)
			{
				DisableDynRes->SetBackgroundColor(DisabledColor);
			}
		}
	}

	if (StickControl)
	{
		if (SaveGameInstance)
		{
			if (SaveGameInstance->MenuSaveData.SavedControlState == EControlState::CS_Touch)
			{
				StickControl->SetBackgroundColor(DisabledColor);
			}
		}
	}

	if (TouchControl)
	{
		if (SaveGameInstance)
		{
			if (SaveGameInstance->MenuSaveData.SavedControlState == EControlState::CS_Joystick)
			{
				TouchControl->SetBackgroundColor(DisabledColor);
			}
		}
	}

}

void UMenuWidget::ChangeResolution(float fRes)
{
	if (fRes > 0.1f)
	{
		if (SaveGameInstance)
		{
			SaveGameInstance->MenuSaveData.SavedResolution = fRes;
		}

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
	if (SaveGameInstance)
	{
		SaveGameInstance->MenuSaveData.SavedSFXVolume = fMulti;
	}
}

void UMenuWidget::ChangeSFXMultiplier(float fMulti)
{
	//Save the float to the player
	if (SaveGameInstance)
	{
		SaveGameInstance->MenuSaveData.SavedSFXVolume = fMulti;
	}
}

void UMenuWidget::SetDynamicResolution(EDynamicResState StateToSet)
{
	if (SaveGameInstance)
	{
		SaveGameInstance->MenuSaveData.SavedDynamicResState = StateToSet;
	}
}

void UMenuWidget::SetControlState(EControlState StateToSet)
{
	if (SaveGameInstance)
	{
		SaveGameInstance->MenuSaveData.SavedControlState = StateToSet;
	}
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

void UMenuWidget::EquipmentScreenSetup(UImage* MainWep, UImage * MainOff, UImage * HelmImg, UImage * ArmorImg, UImage * SecondWep, UImage * SecondOff)
{
	if (MainWep)
	{
		if (SaveGameInstance)
		{
			iMainWeapon = SaveGameInstance->MenuSaveData.iSavedMainWep;

			WeaponArray = SaveGameInstance->MenuSaveData.OwnedWeapons;

			ChangeEquipment(MainWep, WeaponArray, iMainWeapon);
		}

	}

	if (MainOff)
	{
		if (SaveGameInstance)
		{
			iMainOffhand = SaveGameInstance->MenuSaveData.iSavedMainOffhand;

			OffhandArray = SaveGameInstance->MenuSaveData.OwnedOffhands;

			ChangeEquipment(MainOff, OffhandArray, iMainOffhand);
		}
	}

	if (HelmImg)
	{
		if (SaveGameInstance)
		{
			iHelmets = SaveGameInstance->MenuSaveData.iSavedHelmet;

			HelmetArray = SaveGameInstance->MenuSaveData.OwnedHelmets;

			ChangeEquipment(HelmImg, HelmetArray, iHelmets);
		}
	}

	if (ArmorImg)
	{
		if (SaveGameInstance)
		{
			iArmor = SaveGameInstance->MenuSaveData.iSavedArmor;

			ArmorArray = SaveGameInstance->MenuSaveData.OwnedArmor;

			ChangeEquipment(ArmorImg, ArmorArray, iArmor);
		}
	}

	if (SecondWep)
	{
		if (SaveGameInstance)
		{
			iSecondWeapon = SaveGameInstance->MenuSaveData.iSavedSecondaryWeapon;

			ChangeEquipment(SecondWep, WeaponArray, iSecondWeapon);
		}
	}

	if (SecondOff)
	{
		if (SaveGameInstance)
		{
			iSecondOffhand = SaveGameInstance->MenuSaveData.iSavedSecondaryOffhand;

			ChangeEquipment(SecondOff, OffhandArray, iSecondOffhand);
		}
	}

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

///////////////////////////
//Store//
///////////////////////////

void UMenuWidget::StoreSetup(UImage * StoreWeapon, UImage * StoreArmor, UImage * StoreOffhand, UImage * StoreHelmet, UButton* AdFreeButton, UImage* AdFreeImage)
{
	if (StoreWeapon)
	{
		if (SaveGameInstance)
		{
			iStoreWeapon = SaveGameInstance->MenuSaveData.iLastStoreWeapon;

			StoreWeaponArray = SaveGameInstance->MenuSaveData.StoreWeapons;

			ChangeEquipment(StoreWeapon, StoreWeaponArray, iStoreWeapon);
		}

	}

	if (StoreArmor)
	{
		if (SaveGameInstance)
		{
			iStoreArmor = SaveGameInstance->MenuSaveData.iLastStoreArmor;

			StoreOffhandArray = SaveGameInstance->MenuSaveData.StoreOffhands;

			ChangeEquipment(StoreArmor, StoreOffhandArray, iStoreArmor);
		}
	}

	if (StoreOffhand)
	{
		if (SaveGameInstance)
		{
			iStoreOffhand = SaveGameInstance->MenuSaveData.iLastStoreOffhand;

			StoreOffhandArray = SaveGameInstance->MenuSaveData.StoreOffhands;

			ChangeEquipment(StoreOffhand, StoreOffhandArray, iStoreOffhand);
		}
	}

	if (StoreHelmet)
	{
		if (SaveGameInstance)
		{
			iStoreHelmet = SaveGameInstance->MenuSaveData.iLastStoreHelmet;

			StoreHelmetArray = SaveGameInstance->MenuSaveData.StoreHelmets;

			ChangeEquipment(StoreHelmet, StoreHelmetArray, iStoreHelmet);
		}
	}

	if (AdFreeButton && AdFreeImage)
	{
		if (SaveGameInstance)
		{
			if (SaveGameInstance->MenuSaveData.SavedAdState == EAdState::AS_Purchased)
			{
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
	}

}

void UMenuWidget::BuyCoins(int CoinsPurchased)
{
	//Check if player has required funds/follow purchase flow
	bool bSufficentFunds = true;

	if (bSufficentFunds == true)
	{
		if (SaveGameInstance)
		{
			SaveGameInstance->MenuSaveData.iPlayerCoins += CoinsPurchased;
		}

		SaveGame();
	}
}

void UMenuWidget::BuyAdFree(UButton* AdFreeButton, UImage* AdFreeImage)
{
	//Check if player has required funds/follow purchase flow
	bool bSufficentFunds = true;

	if (bSufficentFunds == true)
	{
		if (SaveGameInstance)
		{
			SaveGameInstance->MenuSaveData.SavedAdState = EAdState::AS_Purchased;
		}

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

		SaveGame();
	}

}





