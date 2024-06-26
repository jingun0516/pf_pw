// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Building/ToBuild/ToBuildSlotWidget.h"
#include "Widgets/Building/BuildingClickedWidget.h"
#include "Building/DA_ToBuildDataAsset.h"
#include "Characters/Hero.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Components/BuildingComponent.h"
#include "Components/InventoryComponent.h"
#include "Items/BaseItem.h"


void UToBuildSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ToBuildButton->OnClicked.AddDynamic(this, &UToBuildSlotWidget::ToBuildSlotClicked);
}

void UToBuildSlotWidget::InitToBuildSlot(UDA_ToBuildDataAsset* InDaBuilding)
{
	ToBuildSlot->SetBrushFromTexture(InDaBuilding->texture);
	SpawnBuildingClass = InDaBuilding->BuildingClass;
	SpawnBuildingImage = InDaBuilding->texture;

	for (int i = 0; i < InDaBuilding->RequiredItems.Num(); i++)
	{
		RequiredItems.Add(InDaBuilding->RequiredItems[i]);
		ABaseItem* item = GetWorld()->SpawnActor<ABaseItem>(RequiredItems[i]);
		if (item)
		{
			RequiredImages.Add(item->texture);
			RequiredCounts.Add(InDaBuilding->RequiredCounts[i]);
			item->Destroy();
		}
	}
}

void UToBuildSlotWidget::ToBuildSlotClicked()
{
	if (SpawnBuildingClass)
	{
		UE_LOG(LogTemp, Log, TEXT("SpawnBuildingClass: %s"), *SpawnBuildingClass->GetName());
		if (OwnerPlayer->GetStateComponent()->GetState() != E_StateType::E_Idle) return;

		FActorSpawnParameters SpawnParam;
		SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ABaseBuilding* building = GetWorld()->SpawnActor<ABaseBuilding>(SpawnBuildingClass, SpawnParam);
		if (!building) return;
		BuildingClickedWidget = building->GetBuildingClickedWidget();
		if (!BuildingClickedWidget) return;

		BuildingClickedWidget->SetVisibility(ESlateVisibility::Visible);
		BuildingClickedWidget->InterActionWidget = this;
		BuildingClickedWidget->SelectedImage->SetBrushFromTexture(SpawnBuildingImage);
		BuildingClickedWidget->SetSlots(RequiredImages, RequiredCounts);

		if (OwnerPlayer)
		{
			BuildingClickedWidget->SetParentWidget(Cast<UUserWidget>(OwnerPlayer->GetToBuildWidget()));

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
				BuildingClickedWidget->SetHorizonOpacity(i, bCheck);
				BuildingClickedWidget->SetCurText(CurItemCount, i);
			}
			if (passed)
			{
				UE_LOG(LogTemp, Log, TEXT("CanBuild"));
				BuildingClickedWidget->SetSpawnBuildingClass(SpawnBuildingClass);
				BuildingClickedWidget->SetItemClassAndCounts(tempItemArray, tempCountArray);
				BuildingClickedWidget->CanBuild = true;
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("CantBuild"));
			}
		}
	}
}
