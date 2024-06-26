#include "Notifies/Actions/AN_EndActionNotify.h"
#include "Characters/BaseCharacter.h"
#include "Components/ToolComponent.h"
#include "Tools/BaseTool.h"
#include "Actions/BaseAction.h"

FString UAN_EndActionNotify::GetNotifyName_Implementation() const
{
	return FString(L"EndAction");
}

void UAN_EndActionNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (Owner)
	{
		if (ToolComponent)
		{
			if (ToolComponent->CurrentAction)
			{
				ToolComponent->CurrentAction->EndActionNotify();
			}
		}
	}
}
