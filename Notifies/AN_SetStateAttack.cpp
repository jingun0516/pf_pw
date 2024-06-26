#include "Notifies/AN_SetStateAttack.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"

FString UAN_SetStateAttack::GetNotifyName_Implementation() const
{
	return FString(L"SetAttack");
}

void UAN_SetStateAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if (StateComponent)
		StateComponent->SetState(E_StateType::E_Attacking);
}
