#include "AI/Node/BaseAINode.h"
#include "AI/BaseAIController.h"
#include "AI/BaseAI.h"

EBTNodeResult::Type UBaseAINode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Controller = Cast<ABaseAIController>(OwnerComp.GetAIOwner());
	AICharacter = Controller->GetAICharacter();

	if (!Controller || !AICharacter) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}
