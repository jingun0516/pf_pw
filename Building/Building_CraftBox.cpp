
#include "Building/Building_CraftBox.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Widgets/Building/CraftBox/CraftBoxWidget.h"
#include "Helper.h"
#include "Building/BuildingStateEnum.h"
#include "Tools/BaseTool.h"
#include "Characters/Hero.h"
#include "Widgets/Building/WorkTimeActor.h"
#include "Widgets/Building/CraftBox/CraftBoxClickedWidget.h"

ABuilding_CraftBox::ABuilding_CraftBox()
{
	InteractioningWidgetClass = Helper::GetClass<UBaseBuildingWidget>(TEXT("/Game/Widgets/BuildingWidget/CraftBox/WB_CraftBox"));
}

void ABuilding_CraftBox::BeginPlay()
{
	Super::BeginPlay();

	Cast<UCraftBoxWidget>(InteractioningWidget)->InitCraftBoxSlots();
}

void ABuilding_CraftBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding_CraftBox::JobsDone()
{
	Super::JobsDone();

	//GetWorld()->SpawnActor<ABaseTool>(GetToolClass(), OwnerHero->GetActorLocation(), FRotator());
}

void ABuilding_CraftBox::StartWork()
{
	Super::StartWork();

	GetWorkTimeActor()->SetImage(ToolImage);
}

void ABuilding_CraftBox::InterAction()
{
	Super::InterAction();

	if (GetBuildingState() == EBuildingState::E_WorkDone)
	{
		ABaseTool* tool = GetWorld()->SpawnActor<ABaseTool>(GetToolClass(), OwnerHero->GetActorLocation(), FRotator());
		if (tool)
		{
			tool->SetOwner(OwnerHero);
			tool->SetOwnerHero(OwnerHero);
			tool->InterAction();
		}
		SetBuildingState(EBuildingState::E_Idle);
		WorkTimeActor->Destroy();
	}
}
