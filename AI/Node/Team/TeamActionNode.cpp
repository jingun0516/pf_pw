#include "AI/Node/Team/TeamActionNode.h"
#include "AI/MyTeam/MyTeamAIController.h"
#include "AI/BaseAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/ToolComponent.h"
#include "AI/Enum/EBehaviorKeys.h"

UTeamActionNode::UTeamActionNode()
{
	NodeName = TEXT("TeamAction");
}

EBTNodeResult::Type UTeamActionNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto Controller = Cast<AMyTeamAIController>(OwnerComp.GetAIOwner());
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
