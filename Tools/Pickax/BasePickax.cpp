#include "Tools/Pickax/BasePickax.h"

ABasePickax::ABasePickax()
{
	HandleSocketName = "PickAxSocket";
	ToolType = EToolType::E_Pickax;
	
}

void ABasePickax::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePickax::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABasePickax::SetDatas()
{
	Super::SetDatas();
}
