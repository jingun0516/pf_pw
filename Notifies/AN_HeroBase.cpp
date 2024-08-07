#include "Notifies/AN_HeroBase.h"
#include "../Characters/BaseCharacter.h"
#include "../Components/ToolComponent.h"
#include "../Components/StatusComponent.h"
#include "../Components/State/StateComponent.h"
#include "Logging/LogMacros.h"

DEFINE_LOG_CATEGORY(NotifyLog);

void UAN_HeroBase::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	Owner = Cast<ABaseCharacter>(MeshComp->GetOwner());

	if (!Owner) return;
	
	if (Owner->GetToolComponent())
		ToolComponent = Owner->GetToolComponent();
	if (Owner->GetStatusComponent())
		StatusComponent = Owner->GetStatusComponent();
	if (Owner->GetStateComponent())
		StateComponent = Owner->GetStateComponent();
	
}
