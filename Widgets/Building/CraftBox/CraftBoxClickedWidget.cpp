#include "Widgets/Building/CraftBox/CraftBoxClickedWidget.h"
#include "Widgets/Building/CraftBox/CraftBoxItemWidget.h"
#include "Items/BaseItem.h"
#include "Helper.h"
#include "Characters/Hero.h"
#include "Components/InventoryComponent.h"
#include "Widgets/BaseStatus/BaseStatusWidget.h"

void UCraftBoxClickedWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NoButton)
		NoButton->OnClicked.AddDynamic(this, &UCraftBoxClickedWidget::NoButtonClicked);
	if (YesButton)
		YesButton->OnClicked.AddDynamic(this, &UCraftBoxClickedWidget::YesButtonClicked);
}

void UCraftBoxClickedWidget::NoButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UCraftBoxClickedWidget::YesButtonClicked()
{
	if (CanCraft)
	{
		UE_LOG(LogTemp, Log, TEXT("CanCraft"));
		if (UCraftBoxItemWidget* widget = Cast<UCraftBoxItemWidget>(InterActionWidget))
		{
			widget->SpawnTool();
			widget->GetParentWidget()->SetVisibility(ESlateVisibility::Hidden);

			SET_GAME_MODE_GAME_ONLY()
		}
		UE_LOG(LogTemp, Log, TEXT("ItemClassNum: %d      ItemCountsNum: %d"), itemClass.Num(), itemCounts.Num());
		DoSubItemsForCraft();
		itemClass.Empty();
		itemCounts.Empty();

		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CanNotCraft"));
	}
	CanCraft = false;
}

void UCraftBoxClickedWidget::SetSlots(TArray<UTexture2D*> itemsImage, TArray<int> counts)
{
	Horizon1->SetVisibility(ESlateVisibility::Hidden);
	Horizon2->SetVisibility(ESlateVisibility::Hidden);
	Horizon3->SetVisibility(ESlateVisibility::Hidden);
	Horizon4->SetVisibility(ESlateVisibility::Hidden);

	if (itemsImage.Num() >= 1)
	{
		Horizon1->SetVisibility(ESlateVisibility::HitTestInvisible);
		Slot1Image->SetVisibility(ESlateVisibility::Visible);
		Slot1Image->SetBrushFromTexture(itemsImage[0]);
		RequiredCount1->SetText(FText::AsNumber(counts[0]));
	}
	if (itemsImage.Num() >= 2)
	{
		Horizon2->SetVisibility(ESlateVisibility::HitTestInvisible);
		Slot2Image->SetVisibility(ESlateVisibility::Visible);
		Slot2Image->SetBrushFromTexture(itemsImage[1]);
		RequiredCount2->SetText(FText::AsNumber(counts[1]));
	}
	if (itemsImage.Num() >= 3)
	{
		Horizon3->SetVisibility(ESlateVisibility::HitTestInvisible);
		Slot3Image->SetVisibility(ESlateVisibility::Visible);
		Slot3Image->SetBrushFromTexture(itemsImage[2]);
		RequiredCount3->SetText(FText::AsNumber(counts[2]));
	}
	if (itemsImage.Num() == 4)
	{
		Horizon4->SetVisibility(ESlateVisibility::HitTestInvisible);
		Slot4Image->SetVisibility(ESlateVisibility::Visible);
		Slot4Image->SetBrushFromTexture(itemsImage[3]);
		RequiredCount4->SetText(FText::AsNumber(counts[3]));
	}

}

void UCraftBoxClickedWidget::SetCurText(int cnt, int index)
{
	switch (index)
	{
	case 0:
		CurCount1->SetText(FText::AsNumber(cnt));
		break;
	case 1:
		CurCount2->SetText(FText::AsNumber(cnt));
		break;
	case 2:
		CurCount3->SetText(FText::AsNumber(cnt));
		break;
	case 3:
		CurCount4->SetText(FText::AsNumber(cnt));
		break;
	}
}

void UCraftBoxClickedWidget::SetHorizonOpacity(int num, bool bCheck)
{
	switch (num)
	{
	case 0:
		if(bCheck)
			Horizon1->SetRenderOpacity(1.f);
		else
			Horizon1->SetRenderOpacity(0.2f);
		break;
	case 1:
		if (bCheck)
			Horizon2->SetRenderOpacity(1.f);
		else
			Horizon2->SetRenderOpacity(0.2f);
		break;
	case 2:
		if (bCheck)
			Horizon3->SetRenderOpacity(1.f);
		else
			Horizon3->SetRenderOpacity(0.2f);
		break;
	case 3:
		if (bCheck)
			Horizon4->SetRenderOpacity(1.f);
		else
			Horizon4->SetRenderOpacity(0.2f);
		break;
	}
}

void UCraftBoxClickedWidget::DoSubItemsForCraft()
{
	if (!OwnerPlayer) return;
	if (!OwnerPlayer->GetInventoryComponent()) return;

	for (int i = 0; i < itemClass.Num(); i++)
	{
		OwnerPlayer->GetInventoryComponent()->SubItems(itemClass[i], itemCounts[i]);
	}
}
