#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonSlotWidget.h"

void UPocketmonSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPocketmonSlotWidget::SetMonsterLV(int LV)
{
	MonsterLV->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(LV)));
}

void UPocketmonSlotWidget::SetMonsterName(FText name)
{
	MonsterName->SetText(name);
}

void UPocketmonSlotWidget::SetHPProgressBar(float percent)
{
	HPProgressBar->SetPercent(percent);
}

void UPocketmonSlotWidget::SetHPText(float HP, float MaxHP)
{
	HPText->SetText(FText::Format(FText::FromString(TEXT("{0}/{1}")), FText::AsNumber(HP), FText::AsNumber(MaxHP)));
}

void UPocketmonSlotWidget::SetHungerProgressBar(float percent)
{
	HungerProgressBar->SetPercent(percent);
}

void UPocketmonSlotWidget::SetMonsterImage(UTexture2D* image)
{
	MonsterImage->SetBrushFromTexture(image);
}
