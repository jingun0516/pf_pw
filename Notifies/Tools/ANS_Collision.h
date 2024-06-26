#pragma once

#include "CoreMinimal.h"
#include "Notifies/ANS_HeroBase.h"
#include "Logging/LogMacros.h"
#include "ANS_Collision.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(ANSCollisionLog, Log, All);

class UToolComponent;
class ABaseCharacter;
/**
 * 
 */
UCLASS()
class PF_PW_API UANS_Collision : public UANS_HeroBase
{
	GENERATED_BODY()

protected:
	virtual FString GetNotifyName_Implementation() const override;
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
