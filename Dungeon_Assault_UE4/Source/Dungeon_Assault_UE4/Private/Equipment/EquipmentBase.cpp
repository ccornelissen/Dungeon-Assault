// Fill out your copyright notice in the Description page of Project Settings.

#include "EquipmentBase.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "BossBase.h"
#include "BossLauncher.h"
#include "DA_Character.h"
#include "BossMinion.h"

AEquipmentBase::AEquipmentBase()
{
	
}

void AEquipmentBase::Attack()
{
}

void AEquipmentBase::SetWeapon()
{
	GetWorld()->GetTimerManager().ClearAllTimersForObject(this);

	if (MyFlipbookComp && EquipmentInfo.IdleBook)
	{
		MyFlipbookComp->SetFlipbook(EquipmentInfo.IdleBook);
	}
	
}

float AEquipmentBase::GetLeechPercent()
{
	return EquipmentInfo.fLeechPercent;
}

float AEquipmentBase::GetPoisonPercent()
{
	return EquipmentInfo.fLeechPercent;
}

bool AEquipmentBase::CanReflect()
{
	return EquipmentInfo.bCanReflect;
}

void AEquipmentBase::SetPlayer(ADA_Character &CharacterToSet)
{
	MyPlayer = &CharacterToSet;
}

void AEquipmentBase::AnimSwitch(EEquipAnimState SwitchState)
{
}

FString AEquipmentBase::GetEnumAsString(EEquipmentType EnumValue)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EEquipmentType"), true);

	if (!EnumPtr)
	{
		return FString("Invalid");
	}

	return EnumPtr->GetNameByValue((int64)EnumValue).ToString();
}

void AEquipmentBase::SwitchToIdle()
{
	AnimSwitch(EEquipAnimState::AS_Idle);
}




