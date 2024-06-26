#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"

class UMonsterStatusDataAsset;

#include "WereWolf_AI.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API AWereWolf_AI : public ABaseAI
{
	GENERATED_BODY()

	AWereWolf_AI();

	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
