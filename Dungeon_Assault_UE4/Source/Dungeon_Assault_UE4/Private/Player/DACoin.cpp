// Fill out your copyright notice in the Description page of Project Settings.

#include "DACoin.h"
#include "DA_Character.h"
#include "PaperFlipbookComponent.h"

ADACoin::ADACoin()
{
	BookComponent = FindComponentByClass<UPaperFlipbookComponent>();

	BookComponent->OnComponentBeginOverlap.AddDynamic(this, &ADACoin::OnOverlapBegin);

}

void ADACoin::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ADA_Character* HitCharacter = Cast<ADA_Character>(OtherActor);

	if (HitCharacter)
	{
		HitCharacter->AddCoins(iValue);

		Destroy();
	}
}

void ADACoin::SetValue(int32 ValueToSet)
{
	iValue = ValueToSet;
}


