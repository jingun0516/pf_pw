#include "Tools/InvisibleTool/BaseKick.h"
#include "Actions/BaseAction.h"
#include "Actions/BaseSwingAction.h"
#include "Actions/ActionDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Helper.h"

ABaseKick::ABaseKick()
{
	HandleSocketName = "KickSocket";

	ToolType = EToolType::E_ETC;
	Actions = Cast<UActionDataAsset>(StaticLoadObject(UActionDataAsset::StaticClass(), nullptr, TEXT("/Game/Actions/DA_Kick")));
}

void ABaseKick::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseKick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseKick::SetDatas()
{
	Super::SetDatas();
}
