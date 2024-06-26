#include "Widgets/Building/CraftBox/CraftBoxItemWidget.h"
#include "Tools/ToolsDataAsset.h"
#include "Building/Building_CraftBox.h"
#include "Building/BuildingStateEnum.h"
#include "../../YesNoWidget.h"
#include "Widgets/Building/WorkTimeWidget.h"
#include "Widgets/Building/BuildingClickedWidget.h"
#include "Characters/Hero.h"
#include "Components/InventoryComponent.h"
#include "Items/BaseItem.h"


void UCraftBoxItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	CraftBoxItemButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_CraftBoxItemButton")));
	CraftBoxItemImage= Cast<UImage>(GetWidgetFromName(TEXT("BP_CraftBoxItemImage")));

	CraftBoxItemButton->OnClicked.AddDynamic(this, &UCraftBoxItemWidget::SetCraftState);
}

void UCraftBoxItemWidget::SpawnTool()
{
	if (SpawnToolClass)
	{
		ABuilding_CraftBox* CraftBox = Cast<ABuilding_CraftBox>(OwnerBuilding);

		if (!CraftBox) return;

		if (CraftBox->GetBuildingState() == EBuildingState::E_Idle)
		{
			CraftBox->SetBuildingState(EBuildingState::E_Work);
			CraftBox->SetToolClass(SpawnToolClass);
			CraftBox->SetGoalWorkTime(CraftTime);

			if (OwnerPlayer)
			{
				if(Cast<ABaseCharacter>(OwnerPlayer))
					CraftBox->AddWorkers(Cast<ABaseCharacter>(OwnerPlayer));

				UE_LOG(LogTemp, Log, TEXT("CraftBoxItemWidget Yes OwnerPlayer"), CraftBox->GetWorkersNum());
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("CraftBoxItemWidget No OwnerPlayer"));
			}
		}
		UE_LOG(LogTemp, Log, TEXT("%s"), *SpawnToolClass.Get()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *this->GetName());
	}
}

void UCraftBoxItemWidget::InitCraftBoxSlot(UToolsDataAsset* InDATool)
{
	CraftBoxItemImage->SetBrushFromTexture(InDATool->texture);
	SpawnToolClass = InDATool->ToolClass;
	SpawnToolImage = InDATool->texture;
	CraftTime = InDATool->CraftTime;

	ABaseItem* item;

	for (int i = 0; i < InDATool->RequiredItems.Num(); i++)
	{
		RequiredItems.Add(InDATool->RequiredItems[i]);
		item = GetWorld()->SpawnActor<ABaseItem>(RequiredItems[i]);
		if (item)
		{
			RequiredImages.Add(item->texture);
			RequiredCounts.Add(InDATool->RequiredCounts[i]);
			item->Destroy();
		}
	}
}

void UCraftBoxItemWidget::SetCraftState()
{
	if (SpawnToolClass)
	{
		ABuilding_CraftBox* CraftBox = Cast<ABuilding_CraftBox>(OwnerBuilding);

		if (!CraftBox) return;

		if (CraftBox->GetBuildingState() == EBuildingState::E_Idle)
		{
			if (CraftBox->GetBuildingClickedWidget())
			{
				UE_LOG(LogTemp, Log, TEXT("ClickedWidget Yes"));
				CraftBox->SetToolImage(SpawnToolImage);
				CraftBoxClickedWidget = CraftBox->GetBuildingClickedWidget();
				CraftBoxClickedWidget->SetVisibility(ESlateVisibility::Visible);
				CraftBoxClickedWidget->InterActionWidget = this;
				CraftBoxClickedWidget->SelectedImage->SetBrushFromTexture(SpawnToolImage);
				CraftBoxClickedWidget->SetSlots(RequiredImages, RequiredCounts);
				
				if (OwnerPlayer)
				{
					bool passed = true;

					TArray<TSubclassOf<ABaseItem>> tempItemArray;
					TArray<int> tempCountArray;

					for (int i = 0; i < RequiredItems.Num(); i++)
					{
						int CurItemCount = OwnerPlayer->GetInventoryComponent()->GetNumsOfItem(RequiredItems[i]);
						bool bCheck = (CurItemCount >= RequiredCounts[i]); 
						tempItemArray.Add(RequiredItems[i]);
						tempCountArray.Add(RequiredCounts[i]);
						if (!bCheck)
						{
							passed = false;
						}
						CraftBoxClickedWidget->SetHorizonOpacity(i, bCheck);
						CraftBoxClickedWidget->SetCurText(CurItemCount, i);
					}
					if (passed)
					{
						CraftBoxClickedWidget->itemClass = tempItemArray;
						CraftBoxClickedWidget->itemCounts = tempCountArray;
						CraftBoxClickedWidget->CanCraft = true;
					}
				}
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("%s"), *this->GetName());
	}

}
