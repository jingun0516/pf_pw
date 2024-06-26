#pragma once

#include "CoreMinimal.h"
#include "Tools/BaseTool.h"
#include "BasePickax.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API ABasePickax : public ABaseTool
{
	GENERATED_BODY()

public:
	ABasePickax();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetDatas() override;
};
