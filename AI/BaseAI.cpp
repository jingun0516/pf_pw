#include "AI/BaseAI.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Helper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AI/BaseAIController.h"
#include "Components/ToolComponent.h"
#include "Tools/ToolsEnum.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Tools/BaseTool.h"
#include "AI/EnemyAI/EnemyAIController.h"
#include "AI/MyTeam/MyTeamAIController.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"

ABaseAI::ABaseAI()
{
	SetCharacterMovement();
}

void ABaseAI::BeginPlay()
{
	Super::BeginPlay();

	if (MonsterToolClass)
	{
		UE_LOG(LogTemp, Log, TEXT("Montser Tool Class Yes"));
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Montser Tool Class No!!!!!!"));
	}

	SetMonsterTool();
	SetupEnemyAIController();
}

void ABaseAI::SetupEnemyAIController()
{
	AEnemyAIController* AIController = GetWorld()->SpawnActor<AEnemyAIController>();
	if (AIController)
	{
		AIController->UnPossess();
		AIController->Possess(this);
		controller = AIController;
	}
}

void ABaseAI::SetupTeamAIController()
{
	AMyTeamAIController* AIController = GetWorld()->SpawnActor<AMyTeamAIController>();
	//GetController()
	if (AIController)
	{
		AIController->UnPossess();
		AIController->Possess(this);
		controller = AIController;
	}
}

void ABaseAI::ActivateAIController(bool bActivate)
{
	if (controller)
	{
		if (bActivate)
		{
			GetCharacterMovement()->SetComponentTickEnabled(true);
			//controller->UnPossess();
			//controller->Possess(this);
			bCanAttack = true;
			UE_LOG(LogTemp, Log, TEXT("Activate Controller Success"));
		}
		else
		{
			GetCharacterMovement()->SetComponentTickEnabled(false);
			bCanAttack = false;
			//controller->UnPossess();
			UE_LOG(LogTemp, Log, TEXT("DeActivate Controller Success"));
		}
	}
}

void ABaseAI::SetCharacterMovement()
{
	Super::SetCharacterMovement();
}

void ABaseAI::SetMonsterTool()
{
	if (MonsterToolClass)
	{
		FActorSpawnParameters SpawnParam;
		SpawnParam.Owner = this;
		MonsterTool = GetWorld()->SpawnActor<ABaseTool>(MonsterToolClass, SpawnParam);
		MonsterTool->SetActorEnableCollision(false);
		MonsterTool->SetOwnerHero(this);
		MonsterTool->SetOwner(this);

		if (GetToolComponent() && MonsterTool)
		{
			GetToolComponent()->AddTool(EToolSlot::E_First, MonsterTool);
			GetToolComponent()->EquipTool(EToolSlot::E_First);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("there is No Monster TOol Class"));
	}
}
