#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorkTimeActor.generated.h"

class UWidgetComponent;
class AHero;

UCLASS()
class PF_PW_API AWorkTimeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AWorkTimeActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void SetLeftTime(float time);
	void SetImage(UTexture2D* image);
	void SetWorkDone();

private:
	UWidgetComponent* WorkTimeWidget;
	AHero* OwnerHero;
};
