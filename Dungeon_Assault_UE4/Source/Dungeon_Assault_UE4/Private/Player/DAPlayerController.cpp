// Fill out your copyright notice in the Description page of Project Settings.

#include "DAPlayerController.h"
#include "DAPlayerUI.h"
#include "DA_Character.h"

void ADAPlayerController::BeginPlay()
{
	//Setup player UI
	if (PlayerUIToCreate != nullptr)
	{
		UDAPlayerUI* PlayerUI = CreateWidget<UDAPlayerUI>(this, PlayerUIToCreate);

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		Mode.SetHideCursorDuringCapture(false);

		PlayerUI->AddToViewport(9999);

		ADA_Character* ControlledCharacter = Cast<ADA_Character>(GetControlledPawn());

		if (ControlledCharacter)
		{
			ControlledCharacter->SetPlayerUI(*PlayerUI);
		}
	}
	
}
