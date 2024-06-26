#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamagedActor.generated.h"

class UWidgetComponent;

UCLASS()
class PF_PW_API ADamagedActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADamagedActor();

protected:
	virtual void BeginPlay() override;

public:
	void SetDamage(float Damage);

	UWidgetComponent* DamageWidget;
};
