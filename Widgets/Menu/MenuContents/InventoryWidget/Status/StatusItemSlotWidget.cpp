// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/MenuContents/InventoryWidget/Status/StatusItemSlotWidget.h"
#include <Blueprint/WidgetBlueprintLibrary.h>
#include <DragDrop.h>
#include <Items/BaseItem.h>
#include "Characters/Hero.h"
#include "Components/InventoryComponent.h"
#include "Components/ToolComponent.h"
#include <Widgets/Menu/MenuContents/InventoryWidget/Inventory/InventorySlotWidget.h>
#include "Tools/ToolsEnum.h"
#include "Tools/BaseTool.h"

void UStatusItemSlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	baseImage = ToolImage->GetBrush();
}

FReply UStatusItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Log, TEXT("LeftClick Detected"));
	if (!OwnerHero->GetToolComponent()->CheckEmptySlot(GetSlot()))
	{
		if (baseImage != ToolImage->GetBrush())
		{
			if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
			{
				reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
				UE_LOG(LogTemp, Log, TEXT("Drag Detected"));
			}
		}
	}
	return reply.NativeReply;
}

void UStatusItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDrop* DragDrop = NewObject<UDragDrop>();

	DragDrop->WidgetReference = this;
	DragDrop->DropOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition());

	DragDrop->DefaultDragVisual = this;
	DragDrop->Pivot = EDragPivot::MouseDown;
	DragDrop->Payload = this;

	OutOperation = DragDrop;
}

bool UStatusItemSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDrop* oper = Cast<UDragDrop>(InOperation);

	if (!oper) return false;
	UInventorySlotWidget* slot = Cast<UInventorySlotWidget>(oper->Payload);
	FSlateBrush tempBrush = ToolImage->GetBrush();
	
	if (slot)
	{
		ABaseTool* tempItem = OwnerHero->GetToolComponent()->GetTool(GetSlot());				// 장착되어 있던 도구
		ABaseItem* dropItem = OwnerHero->GetInventoryComponent()->GetItem(slot->GetIndex());	// 새로 장착될 도구

		if (ABaseTool* dropTool = Cast<ABaseTool>(dropItem))
		{
			if (!OwnerHero->GetToolComponent()->CheckEmptySlot(GetSlot()))		// 비어있지 않다면
			{
				if (tempItem)
					OwnerHero->GetInventoryComponent()->SetItem(slot->GetIndex(), Cast<ABaseItem>(tempItem));
				UE_LOG(LogTemp, Log, TEXT("asdfasdfsdf"));
			}
			else
			{
				OwnerHero->GetInventoryComponent()->SetNullItem(slot->GetIndex());
			}

			if (dropTool)
			{
				if (OwnerHero->GetToolComponent()->GetCurrentSlot() == GetSlot())
				{
					OwnerHero->GetToolComponent()->DetachTool();
				}
				OwnerHero->GetToolComponent()->AddTool(GetSlot(), dropTool);
				if (OwnerHero->GetToolComponent()->GetCurrentSlot() == GetSlot())
				{
					OwnerHero->GetToolComponent()->EquipTool(OwnerHero->GetToolComponent()->GetCurrentSlot());
				}
			}
		}
	}
	else if (UStatusItemSlotWidget* itemSlot = Cast<UStatusItemSlotWidget>(oper->Payload))
	{
		ABaseTool* tempItem = OwnerHero->GetToolComponent()->GetTool(GetSlot());				// 장착되어 있던 도구
		ABaseTool* dropItem = OwnerHero->GetToolComponent()->GetTool(itemSlot->GetSlot());	// 새로 장착될 도구

		if (tempItem && dropItem)
		{
			if (OwnerHero->GetToolComponent()->GetCurrentSlot() == GetSlot() || OwnerHero->GetToolComponent()->GetCurrentSlot() == itemSlot->GetSlot())
			{
				OwnerHero->GetToolComponent()->DetachTool();
			}
			OwnerHero->GetToolComponent()->AddTool(GetSlot(), dropItem);
			OwnerHero->GetToolComponent()->AddTool(itemSlot->GetSlot(), tempItem);

			if (OwnerHero->GetToolComponent()->GetCurrentSlot() == GetSlot() || OwnerHero->GetToolComponent()->GetCurrentSlot() == itemSlot->GetSlot())
			{
				OwnerHero->GetToolComponent()->EquipTool(OwnerHero->GetToolComponent()->GetCurrentSlot());
			}
		}
	}
	
	UE_LOG(LogTemp, Log, TEXT("%s"), *this->GetName());

	return true;
}

void UStatusItemSlotWidget::SetToolImage(UTexture2D* texture)
{
	ToolImage->SetBrushFromTexture(texture);
}
