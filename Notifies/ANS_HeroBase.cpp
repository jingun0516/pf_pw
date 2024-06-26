#include "Notifies/ANS_HeroBase.h"
#include "../Characters/BaseCharacter.h"
#include "../Components/ToolComponent.h"
#include "../Components/StatusComponent.h"
#include "../Components/State/StateComponent.h"

#include "../Tools/BaseTool.h"

void UANS_HeroBase::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (Owner)
		ToolComponent = Owner->GetToolComponent();

}

void UANS_HeroBase::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UANS_HeroBase::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

}
