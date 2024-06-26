#pragma once

#include "CoreMinimal.h"
#include "AI/BaseAI.h"

class UMonsterStatusDataAsset;

#include "UndeadBear_AI.generated.h"

/**
 *
 */
UCLASS()
class PF_PW_API AUndeadBear_AI : public ABaseAI
{
	GENERATED_BODY()

	AUndeadBear_AI();

	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
