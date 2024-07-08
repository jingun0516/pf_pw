#include "Notifies/Actions/AN_BeginActionNotify.h"
#include "AN_BeginActionNotify.h"
#include "Characters/BaseCharacter.h"
#include "Components/ToolComponent.h"
#include "Tools/BaseTool.h"
#include "Actions/BaseAction.h"

FString UAN_BeginActionNotify::GetNotifyName_Implementation() const
{
	return FString(L"BeginAction");
}

void UAN_BeginActionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (!Owner || !ToolComponent || !ToolComponent->CurrentAction) return;
	
	ToolComponent->CurrentAction->BeginActionNotify();
}
