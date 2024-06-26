#pragma once

#include "CoreMinimal.h"
#include "Notifies/AN_HeroBase.h"
#include "AN_BeginActionNotify.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UAN_BeginActionNotify : public UAN_HeroBase
{
	GENERATED_BODY()

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
