#include "BuildingClickedWidget.h"
#include "Widgets/Building/BuildingClickedWidget.h"
#include "Widgets/Building/CraftBox/CraftBoxItemWidget.h"
#include "Widgets/Building/ToBuild/ToBuildWidget.h"
#include "Widgets/BaseStatus/BaseStatusWidget.h"
#include "Items/BaseItem.h"
#include "Helper.h"
#include "Characters/Hero.h"
#include "Components/InventoryComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"

void UBuildingClickedWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (NoButton)
		NoButton->OnClicked.AddDynamic(this, &UBuildingClickedWidget::NoButtonClicked);
	if (YesButton)
		YesButton->OnClicked.AddDynamic(this, &UBuildingClickedWidget::YesButtonClicked);
}

void UBuildingClickedWidget::NoButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	if (GetParentWidget())
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			TSharedPtr<SWidget> WidgetPtr = GetParentWidget()->TakeWidget(); // UUserWidget을 SWidget으로 변환합니다.

			FInputModeUIOnly InputMode;

			InputMode.SetWidgetToFocus(WidgetPtr); // 원하는 위젯 지정
			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true; // 마우스 커서를 보이게 설정할 수도 있습니다.
			UE_LOG(LogTemp, Log, TEXT("asdfasdf"));
		}
	}
}

void UBuildingClickedWidget::YesButtonClicked()
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
		
		OwnerPlayer->GetBaseStatusWidget()->SetVisibility(ESlateVisibility::HitTestInvisible);
		
	}
	else if (CanBuild)
	{
		OwnerPlayer->GetToBuildWidget()->SetVisibility(ESlateVisibility::Hidden);
		OwnerPlayer->GetBaseStatusWidget()->SetVisibility(ESlateVisibility::HitTestInvisible);

		SET_GAME_MODE_GAME_ONLY()
		OwnerPlayer->GetBuildingComponent()->SpawnBuilding(SpawnBuildingClass);
		OwnerPlayer->GetStateComponent()->SetState(E_StateType::E_Build);

		UE_LOG(LogTemp, Log, TEXT("CanBuild"));

		SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("CanNotCraft Or CanNotBuild"));
	}
	CanCraft = false;
}

void UBuildingClickedWidget::SetSlots(TArray<UTexture2D*> itemsImage, TArray<int> counts)
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

void UBuildingClickedWidget::SetCurText(int cnt, int index)
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

void UBuildingClickedWidget::SetHorizonOpacity(int num, bool bCheck)
{
	switch (num)
	{
	case 0:
		if (bCheck)
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

void UBuildingClickedWidget::DoSubItemsForCraft()
{
	if (!OwnerPlayer) return;
	if (!OwnerPlayer->GetInventoryComponent()) return;

	for (int i = 0; i < itemClass.Num(); i++)
	{
		OwnerPlayer->GetInventoryComponent()->SubItems(itemClass[i], itemCounts[i]);
	}
}
