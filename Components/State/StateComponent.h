#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateComponent.generated.h"

enum class E_StateType : UINT8;
class ABaseCharacter;

DECLARE_MULTICAST_DELEGATE(FOnHit);
DECLARE_MULTICAST_DELEGATE(FOnDead);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PF_PW_API UStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UStateComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void SetState(E_StateType state);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FORCEINLINE E_StateType GetState() { return CurState; }

	FOnHit DOnHit;
	FOnDead DOnDead;

	UFUNCTION()
	void OnHitFunc();
	
	UFUNCTION()
	void OnDeadFunc();

private:
	E_StateType CurState;
	ABaseCharacter* OwnerCharacter;
		
};
