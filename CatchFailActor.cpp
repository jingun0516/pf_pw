#include "CatchFailActor.h"
#include "Components/WidgetComponent.h"
#include "Helper.h"
#include "Logging/LogMacros.h"

ACatchFailActor::ACatchFailActor()
{
	FailWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("FailWidget"));
	FailWidget->SetWidgetClass(Helper::GetClass<UUserWidget>(L"/Game/Widgets/PocketmonWidget/WB_CatchFail"));
	FailWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ACatchFailActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(2.f);
}

