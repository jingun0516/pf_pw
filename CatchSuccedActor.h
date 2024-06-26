#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchSuccedActor.generated.h"

class UWidgetComponent;

UCLASS()
class PF_PW_API ACatchSuccedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatchSuccedActor();

protected:
	virtual void BeginPlay() override;

	UWidgetComponent* SucceedWidget;
};
