#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "BaseSwingAction.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UBaseSwingAction : public UBaseAction
{
	GENERATED_BODY()

	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;
};
