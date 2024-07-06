#include "Components/ToolComponent.h"

#include "Tools/BaseTool.h"
#include "Tools/Axe/BaseAxe.h"
#include "Tools/ToolsEnum.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Actions/BaseAction.h"
#include "Actions/BaseAction.h"
#include "Misc/OutputDeviceNull.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Components/BuildingComponent.h"
#include "Tools/InvisibleTool/BaseKick.h"
#include "Helper.h"
#include "Building/BaseBuilding.h"

DEFINE_LOG_CATEGORY(ToolComp);

UToolComponent::UToolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	KickClass = Helper::GetClass<ABaseKick>(L"/Game/Tools/Kick/BP_Kick");
}


void UToolComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!OwnerCharacter) return;
	OwnerHero = Cast<AHero>(GetOwner());
	if (!OwnerHero)return;

	if (OwnerCharacter)
	{
		OwnerCharacter->DDoMainAction.AddUFunction(this, "DoMainAction");
		OwnerCharacter->DEndMainAction.AddUFunction(this, "EndMainAction");
		
		OwnerCharacter->DDoSubAction.AddUFunction(this, "DoSubAction");
		OwnerCharacter->DEndSubAction.AddUFunction(this, "EndSubAction");
	}
	
	/* 델리게이트========================================================= */
	if (OwnerHero)
	{
		OwnerHero->DDoAvoidAction.AddUFunction(this, "DoAvoidAction");
		OwnerHero->DEndAvoidAction.AddUFunction(this, "EndAvoidAction");

		OwnerHero->DDoReloadAction.AddUFunction(this, "DoReloadAction");

		OwnerHero->DDoThrowAction.AddUFunction(this, "DoThrowAction");
		OwnerHero->DDoSpawnAction.AddUFunction(this, "DoSpawnAction");

		OwnerHero->DDoFirstSelect.AddUFunction(this, "DoFirstSelect");
		OwnerHero->DDoSecondSelect.AddUFunction(this, "DoSecondSelect");
		OwnerHero->DDoThirdSelect.AddUFunction(this, "DoThirdSelect");
		OwnerHero->DDoForthSelect.AddUFunction(this, "DoForthSelect");
	}
	DOnToolSlotChanged.AddUFunction(this, "OnToolSlotChanged");
	/* ================================================================== */

	FActorSpawnParameters spawnparameters;
	spawnparameters.Owner = OwnerHero;

	if (OwnerHero && KickClass)
	{
		ABaseKick* kick = GetWorld()->SpawnActor<ABaseKick>(KickClass, OwnerHero->GetActorLocation(), FRotator(), spawnparameters);
		if (kick)
		{
			UE_LOG(ToolComp, Log, TEXT("YES Kick"));
			tempKick = kick;
			tempKick->SetDatas();
			tempKick->SetOwnerHero(OwnerHero);
			tempKick->SetActorEnableCollision(false);
			InitToolSlot(EToolSlot::E_First);
			InitToolSlot(EToolSlot::E_Second);
			InitToolSlot(EToolSlot::E_Third);
			InitToolSlot(EToolSlot::E_Forth);

			EquipTool(EToolSlot::E_First);
		}
	}
	else
		UE_LOG(ToolComp, Log, TEXT("NO Kick"));
}


void UToolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UToolComponent::EquipTool(EToolSlot slot)
{
	DetachTool();
	SetCurrentSlot(slot);
	if (OwnerCharacter && GetCurTool())
	{
		if(OwnerHero) GetCurTool()->SetOwnerHero(OwnerHero);
		GetCurTool()->SetOwner(OwnerCharacter);

		if(OwnerHero)
			OwnerCharacter->SetInfos(GetCurTool());
	}
	AttachTool();
	if (!Cast<AHero>(OwnerCharacter))
		GetCurTool()->SetActorHiddenInGame(true);
}

void UToolComponent::AttachTool()
{
	ABaseTool* Tool = GetCurTool();
	if (!Tool) return;
	FName SocketName = Tool->GetSocketName();

	Tool->SetActorHiddenInGame(false);
	Tool->SetActorRelativeLocation(FVector());
	Tool->AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		SocketName
	);
}

void UToolComponent::DetachTool()
{
	ABaseTool* Tool = GetCurTool();
	//Tool->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	if (!Tool) return;
	Tool->SetActorHiddenInGame(true);
	Tool->SetActorEnableCollision(false);
}

void UToolComponent::AddTool(EToolSlot Slot, ABaseTool* Tool)
{
	Tool->SetOwnerHero(OwnerHero);
	Tool->SetOwner(OwnerCharacter);
	Tool->SpawnActions();
	Tools.Add(Slot, Tool);
	
	if (DOnToolSlotChanged.IsBound()) DOnToolSlotChanged.Broadcast();
}

void UToolComponent::UnEquipTool(EToolSlot Slot)
{
	InitToolSlot(Slot);

	if (DOnToolSlotChanged.IsBound()) DOnToolSlotChanged.Broadcast();
}

void UToolComponent::InitToolSlot(EToolSlot slot)
{
	AddTool(slot, tempKick);
}

void UToolComponent::OnToolSlotChanged()
{
	OwnerHero->ToolSlotChanged(GetTool(EToolSlot::E_First), GetTool(EToolSlot::E_Second), GetTool(EToolSlot::E_Third), GetTool(EToolSlot::E_Forth));
}

EToolSlot UToolComponent::IsEmptySlot()
{
	if (Tools.FindRef(EToolSlot::E_First) == tempKick) return EToolSlot::E_First;
	if (Tools.FindRef(EToolSlot::E_Second) == tempKick) return EToolSlot::E_Second;
	if (Tools.FindRef(EToolSlot::E_Third) == tempKick) return EToolSlot::E_Third;
	if (Tools.FindRef(EToolSlot::E_Forth) == tempKick) return EToolSlot::E_Forth;
	return EToolSlot::E_None;
}

bool UToolComponent::CheckEmptySlot(EToolSlot slot)
{
	if (Cast<ABaseKick>(GetTool(slot))) 
		return true; 
	return false;
}

void UToolComponent::ToolInteraction(ABaseTool* tool)		// 무기 습득
{
	if(OwnerHero)
		UE_LOG(ToolComp, Log, TEXT("Tool Comp Interaction"));
	tool->SetOwnerHero(OwnerHero);
	tool->SetOwner(OwnerHero);
	tool->InterAction();
}

void UToolComponent::DoMainAction()
{
	if (!GetCurTool()) return;
	
	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Build)
	{
		if (!(OwnerCharacter->GetBuildingComponent()->CanSpawnBuilding())) return;	// Building이 가능한 상태일 경우
		
		OwnerCharacter->GetBuildingComponent()->SpawnBuildingStart();
		return;
		
	}

	if (GetCurTool()->MainAction)
	{
		CurrentAction = GetCurTool()->MainAction;
		GetCurTool()->MainAction->DoAction();
		return;
	}
}

void UToolComponent::EndMainAction()
{
	if (!GetCurTool()) return;
	if (!(GetCurTool()->MainAction)) return;
	
	GetCurTool()->MainAction->EndAction();
	
}

void UToolComponent::DoSubAction()
{
	if (!GetCurTool()) return;

	if (OwnerCharacter->GetStateComponent()->GetState() == E_StateType::E_Build)
	{
		OwnerCharacter->GetBuildingComponent()->BuildingCancel();
		return;
	}

	if (GetCurTool()->SubAction)
	{
		GetCurTool()->SubAction->DoAction();
		CurrentAction = GetCurTool()->SubAction;
	}
}

void UToolComponent::EndSubAction()
{
	if (!GetCurTool()) return;

	if (GetCurTool()->SubAction)
	{
		GetCurTool()->SubAction->EndAction();
	}
}

void UToolComponent::DoAvoidAction()
{
}

void UToolComponent::EndAvoidAction()
{
}

void UToolComponent::DoReloadAction()
{
}

void UToolComponent::DoThrowAction()
{
	if (!GetCurTool()) return;
	if (GetCurTool()->ThrowAction)
	{
		GetCurTool()->ThrowAction->DoAction();
		CurrentAction = GetCurTool()->ThrowAction;
	}
}

void UToolComponent::DoSpawnAction()
{
	if (!GetCurTool()) return;

	if (GetCurTool()->SpawnAction)
	{
		GetCurTool()->SpawnAction->DoAction();
		CurrentAction = GetCurTool()->SpawnAction;
	}
}

void UToolComponent::DoFirstSelect()
{
	if (!(OwnerHero->GetStateComponent()->GetState() == E_StateType::E_Idle)) return;
	
	if (GetTool(EToolSlot::E_First))
	{
		UE_LOG(ToolComp, Log, TEXT("First"));
		if (CurrentSlot != EToolSlot::E_First)
			EquipTool(EToolSlot::E_First);
	}
	
}

void UToolComponent::DoSecondSelect()
{
	if (!(OwnerHero->GetStateComponent()->GetState() == E_StateType::E_Idle)) return;
	
	if (GetTool(EToolSlot::E_Second))
	{
		UE_LOG(ToolComp, Log, TEXT("Second"));
		if (CurrentSlot != EToolSlot::E_Second)
			EquipTool(EToolSlot::E_Second);
	}
}

void UToolComponent::DoThirdSelect()
{
	if (!(OwnerHero->GetStateComponent()->GetState() == E_StateType::E_Idle)) return;
	
	if (GetTool(EToolSlot::E_Third))
	{
		UE_LOG(ToolComp, Log, TEXT("Third"));
		if (CurrentSlot != EToolSlot::E_Third)
			EquipTool(EToolSlot::E_Third);
	}
}

void UToolComponent::DoForthSelect()
{
	if (!(OwnerHero->GetStateComponent()->GetState() == E_StateType::E_Idle)) return;
	
	if (GetTool(EToolSlot::E_Forth))
	{
		if (CurrentSlot != EToolSlot::E_Forth)
			EquipTool(EToolSlot::E_Forth);
	}
}

