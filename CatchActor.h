#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatchActor.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(CatchLog, Log, All);

class AHero;
class UWidgetComponent;
class UParticleSystem;

UCLASS()
class PF_PW_API ACatchActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatchActor();

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick(float DeltaSecond) override;

public:
	UFUNCTION()
	void SetCatchInfo(float Start, float End, int num, ABaseMonster* InMonster);

	UFUNCTION()
	void CheckCatchFunc(float percent);

	UFUNCTION()
	void OnCatchDestroyed(AActor* DestroyedActor);

private:
	UWidgetComponent* CatchWidget;
	UMaterialInterface* BaseMaterial;
	UMaterialInstanceDynamic* MI_RoundProgressbar;
	float StartPercent = 0.f;
	float EndPercent = 0.f;
	float CurPercent = 0.f;
	int CurNum = 0;
	bool CheckCatch = false;
	ABaseMonster* monster;
	AHero* OwnerHero;
	UParticleSystem* effect;
};
