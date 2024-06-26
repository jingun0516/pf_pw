#pragma once

#include "CoreMinimal.h"
#include "Actions/BaseAction.h"
#include "SpawnAction.generated.h"

class ABaseMonsterball;
/**
 *
 */
UCLASS()
class PF_PW_API USpawnAction : public UBaseAction
{
	GENERATED_BODY()

public:
	USpawnAction();

public:
	virtual void DoAction() override;
	virtual void TickAction() override;
	virtual void EndAction() override;
	virtual void BeginActionNotify() override;
	virtual void EndActionNotify() override;

protected:
	TSubclassOf<AActor> monsterball_class;
	ABaseMonsterball* monsterball;
};
