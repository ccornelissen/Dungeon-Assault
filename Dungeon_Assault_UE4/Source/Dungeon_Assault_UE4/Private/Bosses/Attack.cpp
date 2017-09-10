// Fill out your copyright notice in the Description page of Project Settings.

#include "Attack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DA_Character.h"
#include "BossMinion.h"

EBTNodeResult::Type UAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	ADA_Character* Player = Cast<ADA_Character>(BlackboardComp->GetValueAsObject(PlayerKey.SelectedKeyName));

	ABossMinion* AttackingMinion = Cast<ABossMinion>(OwnerComp.GetAIOwner()->GetPawn());

	if (Player && AttackingMinion)
	{
		float DistanceBetween = FVector::Dist(Player->GetActorLocation(), AttackingMinion->GetActorLocation());

		if (DistanceBetween > AttackingMinion->MinionInfo.fAttackRange)
		{
			AttackingMinion->Attack(Player);
		}
	}

	return EBTNodeResult::Succeeded;
}
