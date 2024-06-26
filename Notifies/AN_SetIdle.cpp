#include "Notifies/AN_SetIdle.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"

FString UAN_SetIdle::GetNotifyName_Implementation() const
{
	return FString(L"SetIdle");
}

void UAN_SetIdle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(StateComponent)
		StateComponent->SetState(E_StateType::E_Idle);
}
