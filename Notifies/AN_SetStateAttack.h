#pragma once

#include "CoreMinimal.h"
#include "Notifies/AN_HeroBase.h"
#include "AN_SetStateAttack.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UAN_SetStateAttack : public UAN_HeroBase
{
	GENERATED_BODY()

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
