#include "Widgets/YesNoWidget.h"
#include <Components/Button.h>
#include "Characters/BaseCharacter.h"
#include "Building/BaseBuilding.h"
#include "Widgets/Building/CraftBox/CraftBoxItemWidget.h"
#include "Helper.h"


void UYesNoWidget::NativeOnInitialized()
{
	NoButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_NoButton")));
	YesButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_YesButton")));

	if (NoButton)
		NoButton->OnClicked.AddDynamic(this, &UYesNoWidget::NoButtonClicked);
	else UE_LOG(LogTemp, Log, TEXT("NONO Button"));
	if (YesButton)
		YesButton->OnClicked.AddDynamic(this, &UYesNoWidget::YesButtonClicked);
}

void UYesNoWidget::NoButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UYesNoWidget::YesButtonClicked()
{
	if (GetNextDo() == ENextDo::E_Craft)
	{
		DoCraft();
	}

	SetVisibility(ESlateVisibility::Hidden);
}

void UYesNoWidget::SetNextWidget(UUserWidget* InNextWidget)
{
}

void UYesNoWidget::DoCraft()
{
	if (UCraftBoxItemWidget* widget = Cast<UCraftBoxItemWidget>(NextWidget))
	{
		widget->SpawnTool();
		widget->GetParentWidget()->SetVisibility(ESlateVisibility::Hidden);

		SET_GAME_MODE_GAME_ONLY()
			/*
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			FInputModeGameOnly InputMode;

			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = false; // 마우스 커서를 보이게 설정할 수도 있습니다.
		}
		*/

	}
}
