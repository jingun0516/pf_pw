#include "Tools/Sword/BaseSword.h"
#include "Actions/BaseAction.h"
#include "Actions/BaseSwingAction.h"
#include "Actions/ActionDataAsset.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Helper.h"
#include "BaseSword.h"

ABaseSword::ABaseSword()
{
	HandleSocketName = "SwordSocket";

	ToolType = EToolType::E_Sword;
	Actions = Cast<UActionDataAsset>(StaticLoadObject(UActionDataAsset::StaticClass(), nullptr, TEXT("/Game/Actions/DA_Sword")));
}

void ABaseSword::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseSword::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseSword::SetDatas()
{
	Super::SetDatas();
}
