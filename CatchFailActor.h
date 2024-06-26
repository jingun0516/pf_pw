#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchFailActor.generated.h"

class UWidgetComponent;

UCLASS()
class PF_PW_API ACatchFailActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatchFailActor();

protected:
	virtual void BeginPlay() override;

	UWidgetComponent* FailWidget;
};
