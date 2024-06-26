#include "AI/Node/Wild/ActionNode.h"
#include "AI/EnemyAI/EnemyAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ToolComponent.h"
#include "AI/Enum/EBehaviorKeys.h"

UActionNode::UActionNode()
{
	NodeName = TEXT("EnemyAction");
}

EBTNodeResult::Type UActionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	ABaseAI* AICharacter = Controller->GetAICharacter();

	if (static_cast<uint8>(Controller->get_blackboard()->GetValueAsEnum(TEXT("ActionTypeKey"))) == static_cast<uint8>(EActionTypeKeys::E_Main))
	{
		AICharacter->GetToolComponent()->DoMainAction();
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
}
