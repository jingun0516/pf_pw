#include "Notifies/Tools/ANS_Collision.h"
#include "ANS_Collision.h"
#include "../../Characters/BaseCharacter.h"
#include "../../Components/ToolComponent.h"
#include "../../Tools/BaseTool.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY(ANSCollisionLog);

FString UANS_Collision::GetNotifyName_Implementation() const
{
	return FString(L"Collision Enabled");
}

void UANS_Collision::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	UE_LOG(ANSCollisionLog, Log, TEXT("Collision Enabled"));
	if (!ToolComponent) return;
	
	if (ABaseTool* tool = ToolComponent->GetCurTool())
		tool->SetActorEnableCollision(true);
}


void UANS_Collision::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	UE_LOG(ANSCollisionLog, Log, TEXT("Collision Disabled"));
	if (!ToolComponent) return;
	
	if (ABaseTool* tool = ToolComponent->GetCurTool())
		tool->SetActorEnableCollision(false);
}
