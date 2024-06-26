#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Logging/LogMacros.h"
#include "BaseAction.generated.h"

class ABaseTool;
class ABaseCharacter;
class AHero;

DECLARE_LOG_CATEGORY_EXTERN(ActionLog, Log, All);

UCLASS()
class PF_PW_API UBaseAction : public UObject
{
	GENERATED_BODY()

public:
	void SetOwner(ABaseCharacter* InOwner, ABaseTool* InOwnerTool = nullptr);
	virtual void DoAction();
	virtual void TickAction();
	virtual void EndAction();

	virtual void BeginActionNotify();
	virtual void EndActionNotify();

	TArray<UAnimMontage*> Montages;

protected:
	ABaseCharacter* OwnerCharacter;
	AHero* OwnerHero;
	ABaseTool* OwnerTool;

	void PlayAnimMontageToIndex(int index, float playRate = 1.0f);
};
