// Fill out your copyright notice in the Description page of Project Settings.

#include "GetPlayerTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DA_Character.h"
#include "EngineUtils.h"


EBTNodeResult::Type UGetPlayerTask::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	ADA_Character* Player = nullptr;

	for (TActorIterator<ADA_Character> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		Player = *ActorItr;
	}

	if (Player)
	{
		BlackboardComp->SetValueAsObject(PlayerKey.SelectedKeyName, Player);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failing"));

		return EBTNodeResult::Failed;
	}


	return EBTNodeResult::Succeeded;
}
