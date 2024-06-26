#include "Widgets/Building/ExitButtonWidget.h"

void UExitButtonWidget::NativeOnInitialized()
{
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_ExitButton")));
}
