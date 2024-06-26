#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ANS_HeroBase.generated.h"

class UToolComponent;
class UStatusComponent;
class UStateComponent;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class PF_PW_API UANS_HeroBase : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
	UPROPERTY()
	ABaseCharacter* Owner;

	UPROPERTY()
	UToolComponent* ToolComponent;

	UPROPERTY()
	UStatusComponent* StatusComponent;

	UPROPERTY()
	UStateComponent* StateComponent;
};
