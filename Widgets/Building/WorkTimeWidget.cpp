#include "Widgets/Building/WorkTimeWidget.h"
#include "Components/TextBlock.h"

void UWorkTimeWidget::NativeOnInitialized()
{
	LeftWorkTime = Cast<UTextBlock>(GetWidgetFromName(TEXT("BP_LeftWorkTime")));
	Image = Cast<UImage>(GetWidgetFromName(TEXT("BP_Image")));
}

void UWorkTimeWidget::SetLeftWorkTime(float leftworktime)
{
	if (LeftWorkTime)
	{
		LeftWorkTime->SetText(FText::Format(FText::FromString(TEXT("LeftWorkTime\n{ 0 } seconds")), FText::AsNumber(leftworktime)));
	}
}
