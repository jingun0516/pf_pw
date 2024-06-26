#include "Notifies/AN_Destroy.h"
#include "Characters/BaseCharacter.h"

FString UAN_Destroy::GetNotifyName_Implementation() const
{
	return FString(L"Destroy");
}

void UAN_Destroy::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	if(Owner)
		Owner->Destroy();
}
