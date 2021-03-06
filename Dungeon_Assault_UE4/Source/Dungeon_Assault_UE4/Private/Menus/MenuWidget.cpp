// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuWidget.h"
#include "TextBlock.h"
#include "Image.h"
#include "Button.h"
#include "Slider.h"
#include "WeaponBase.h"
#include "ShieldBase.h"
#include "RangedBase.h"
#include "EquipmentBase.h"
#include "ArmorEquipComponent.h"
#include "HelmetEquipComponent.h"
#include "Dungeon_Assault_UE4.h"

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

		if (UGameplayStatics::DoesSaveGameExist(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex))
		{
			SaveGameInstance = Cast<UDASaveGame>(UGameplayStatics::LoadGameFromSlot(SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex));
		}
		else
		{
			UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->UserIndex);
		}
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

			UE_LOG(LogTemp, Warning, TEXT("Save Res: %f"), SaveGameInstance->MenuSaveData.SavedResolution);
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
		SaveGameInstance->MenuSaveData.SaveMusicVolume = fMulti;
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

			ChangeWeapon(MainWep, WeaponArray, iMainWeapon);
		}

	}

	if (MainOff)
	{
		if (SaveGameInstance)
		{
			iMainOffhand = SaveGameInstance->MenuSaveData.iSavedMainOffhand;

			OffhandArray = SaveGameInstance->MenuSaveData.OwnedOffhands;

			ChangeWeapon(MainOff, OffhandArray, iMainOffhand);
		}
	}

	if (HelmImg)
	{
		if (SaveGameInstance)
		{
			iHelmets = SaveGameInstance->MenuSaveData.iSavedHelmet;

			HelmetArray = SaveGameInstance->MenuSaveData.OwnedHelmets;

			ChangeArmor(HelmImg, HelmetArray, iHelmets);
		}
	}

	if (ArmorImg)
	{
		if (SaveGameInstance)
		{
			iArmor = SaveGameInstance->MenuSaveData.iSavedArmor;

			ArmorArray = SaveGameInstance->MenuSaveData.OwnedArmor;

			ChangeArmor(ArmorImg, ArmorArray, iArmor);
		}
	}

	if (SecondWep)
	{
		if (SaveGameInstance)
		{
			iSecondWeapon = SaveGameInstance->MenuSaveData.iSavedSecondaryWeapon;

			ChangeWeapon(SecondWep, WeaponArray, iSecondWeapon);
		}
	}

	if (SecondOff)
	{
		if (SaveGameInstance)
		{
			iSecondOffhand = SaveGameInstance->MenuSaveData.iSavedSecondaryOffhand;

			ChangeWeapon(SecondOff, OffhandArray, iSecondOffhand);
		}
	}

}


int32 UMenuWidget::ChangeArmor(UImage* ImageToSet, TArray<TSubclassOf<UPaperFlipbookComponent>> ArmorArray, int32 i)
{
	if (ArmorArray.Num() > 0)
	{
		if (i > ArmorArray.Num() - 1)
		{
			i = 0;
		}
		else if (i < 0)
		{
			i = ArmorArray.Num() - 1;
		}

		if (ArmorArray.IsValidIndex(i))
		{
			if (ArmorArray[i]->IsChildOf(UHelmetEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = ArmorArray[i]->GetDefaultObject<UHelmetEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}

			if (ArmorArray[i]->IsChildOf(UArmorEquipComponent::StaticClass()))
			{
				UTexture2D* TextureToSet = ArmorArray[i]->GetDefaultObject<UArmorEquipComponent>()->MyUITexture;

				if (TextureToSet)
				{
					ImageToSet->SetBrushFromTexture(TextureToSet);
				}
			}
		}
	}

	return i;
}

int32 UMenuWidget::ChangeWeapon(UImage * ImageToSet, TArray<TSubclassOf<APaperFlipbookActor>> WeaponArray, int32 i)
{
	if (WeaponArray.Num() > 0)
	{
		if (i > WeaponArray.Num() - 1)
		{
			i = 0;
		}
		else if (i < 0)
		{
			i = WeaponArray.Num() - 1;
		}

		if (WeaponArray.IsValidIndex(i))
		{
			if (WeaponArray[i]->IsChildOf(AEquipmentBase::StaticClass()))
			{
				UTexture2D* TextureToSet = WeaponArray[i]->GetDefaultObject<AEquipmentBase>()->EquipmentInfo.MyUITexture;

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

			ChangeWeapon(StoreWeapon, StoreWeaponArray, iStoreWeapon);
		}

	}

	if (StoreArmor)
	{
		if (SaveGameInstance)
		{
			iStoreArmor = SaveGameInstance->MenuSaveData.iLastStoreArmor;

			StoreOffhandArray = SaveGameInstance->MenuSaveData.StoreOffhands;

			ChangeArmor(StoreArmor, StoreArmorArray, iStoreArmor);
		}
	}

	if (StoreOffhand)
	{
		if (SaveGameInstance)
		{
			iStoreOffhand = SaveGameInstance->MenuSaveData.iLastStoreOffhand;

			StoreOffhandArray = SaveGameInstance->MenuSaveData.StoreOffhands;

			ChangeWeapon(StoreOffhand, StoreOffhandArray, iStoreOffhand);
		}
	}

	if (StoreHelmet)
	{
		if (SaveGameInstance)
		{
			iStoreHelmet = SaveGameInstance->MenuSaveData.iLastStoreHelmet;

			StoreHelmetArray = SaveGameInstance->MenuSaveData.StoreHelmets;

			ChangeArmor(StoreHelmet, StoreHelmetArray, iStoreHelmet);
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





