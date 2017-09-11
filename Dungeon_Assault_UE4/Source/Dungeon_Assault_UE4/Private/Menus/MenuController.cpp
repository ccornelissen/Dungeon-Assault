// Fill out your copyright notice in the Description page of Project Settings.

#include "MenuController.h"
#include "MenuWidget.h"

void AMenuController::BeginPlay()
{
	Super::BeginPlay();

	//Setup player UI
	if (MenuUIToCreate != nullptr)
	{
		UMenuWidget* MenuUI = CreateWidget<UMenuWidget>(this, MenuUIToCreate);

		FInputModeGameAndUI Mode;
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Mode.SetHideCursorDuringCapture(false);

		MenuUI->AddToViewport(9999);
	}

	bShowMouseCursor = true;

	SetVirtualJoystickVisibility(false);
}




