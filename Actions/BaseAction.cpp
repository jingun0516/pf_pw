#include "Actions/BaseAction.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Resources/BaseResource.h"
#include "Components/StatusComponent.h"
#include "Components/CapsuleComponent.h"
#include "Tools/BaseTool.h"

DEFINE_LOG_CATEGORY(ActionLog);

void UBaseAction::SetOwner(ABaseCharacter* InOwner, ABaseTool* InOwnerTool)
{
	OwnerCharacter = InOwner;
	if(InOwnerTool)
		OwnerTool = InOwnerTool;
	OwnerHero = Cast<AHero>(OwnerCharacter);
}

void UBaseAction::DoAction()
{
}

void UBaseAction::TickAction()
{
}

void UBaseAction::EndAction()
{
}

void UBaseAction::BeginActionNotify()
{
}

void UBaseAction::EndActionNotify()
{
}

void UBaseAction::PlayAnimMontageToIndex(int index, float playRate)
{
	if (Montages[index])
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *Montages[index]->GetName());
		OwnerCharacter->GetMesh()->GetAnimInstance()->Montage_Play(Montages[index], playRate);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO Montage That index"));
	}
	
}
