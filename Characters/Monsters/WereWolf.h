#pragma once

#include "CoreMinimal.h"
#include "Characters/Monsters/BaseMonster.h"
#include "WereWolf.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API AWereWolf : public ABaseMonster
{
	GENERATED_BODY()

public:
	AWereWolf();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetCharacterMovement() override;
};
