#include "CatchSuccedActor.h"
#include "Components/WidgetComponent.h"
#include "Helper.h"
#include "Logging/LogMacros.h"

ACatchSuccedActor::ACatchSuccedActor()
{
	SucceedWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("SucceedWidget"));
	SucceedWidget->SetWidgetClass(Helper::GetClass<UUserWidget>(L"/Game/Widgets/PocketmonWidget/WB_CatchSucceed"));
	SucceedWidget->SetWidgetSpace(EWidgetSpace::Screen);

}

void ACatchSuccedActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(2.f);
}
