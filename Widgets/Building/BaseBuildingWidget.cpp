#include "Widgets/Building/BaseBuildingWidget.h"
#include "InfosDataAsset.h"
#include "Building/BaseBuilding.h"
#include "Characters/Hero.h"
#include "Helper.h"
#include "Widgets/Building/WorkTimeWidget.h"
#include "Widgets/YesNoWidget.h"
#include "Widgets/BaseStatus/BaseStatusWidget.h"

void UBaseBuildingWidget::NativeOnInitialized()	// 생성자 역할
{
	Super::NativeOnInitialized();

	OwnerBuilding = Cast<ABaseBuilding>(GetWidgetFromName(TEXT("OwnerBuilding")));
	OwnerPlayer = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());

}

void UBaseBuildingWidget::SetOwnerBuilding(ABaseBuilding* building)
{
	OwnerBuilding = building;
}

void UBaseBuildingWidget::ExitWidgetFunc()
{
	UE_LOG(LogTemp, Log, TEXT("Exit Clicked"));

	SetVisibility(ESlateVisibility::Hidden);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	if (OwnerPlayer)
	{
		OwnerPlayer->GetBaseStatusWidget()->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}
