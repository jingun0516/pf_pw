
#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "BaseSubAction.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UBaseSubAction : public UBaseAction
{
	GENERATED_BODY()

protected:
	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;

	TSubclassOf<AActor> monsterball_class;
};
