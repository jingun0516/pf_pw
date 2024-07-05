#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "TeamPatrolNode.generated.h"

class AMyTeamAIController;

UCLASS()
class PF_PW_API UTeamPatrolNode : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UTeamPatrolNode();
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

private:
	int cnt = 0;
};
