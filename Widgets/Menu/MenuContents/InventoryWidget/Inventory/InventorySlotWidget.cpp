// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/MenuContents/InventoryWidget/Inventory/InventorySlotWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragDrop.h"
#include "Components/InventoryComponent.h"
#include "Characters/Hero.h"
#include "Items/BaseItem.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/StatusItemSlotWidget.h"
#include "Components/ToolComponent.h"
#include "Tools/BaseTool.h"


void UInventorySlotWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	baseImage = InvenImage->GetBrush();
}

FReply UInventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{ 
	FEventReply reply;

	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	UE_LOG(LogTemp, Log, TEXT("LeftClick Detected Slot Index: %d"), index);
	if (baseImage != InvenImage->GetBrush())
	{
		if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
		{
			reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
			UE_LOG(LogTemp, Log, TEXT("Drag Detected"));
		}
	}
	return reply.NativeReply;
}

void UInventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
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

bool UInventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDrop* oper = Cast<UDragDrop>(InOperation);

	if (!oper) return false;
	if (UInventorySlotWidget* slot = Cast<UInventorySlotWidget>(oper->Payload))
	{
		FSlateBrush tempBrush = InvenImage->GetBrush();
		FText tempText = InvenText->GetText();

		if (slot)
		{
			ABaseItem* tempItem = OwnerHero->GetInventoryComponent()->GetItem(index);		  // 원래 있던 것
			ABaseItem* dropItem = OwnerHero->GetInventoryComponent()->GetItem(slot->index);   // 드랍될 것

			UE_LOG(LogTemp, Log, TEXT("tempItem Index: %d     dropItem Index: %d"), index, slot->index);

			if (dropItem)
				OwnerHero->GetInventoryComponent()->SetItem(index, dropItem);
			else
				OwnerHero->GetInventoryComponent()->SetNullItem(index);
			if (tempItem)
				OwnerHero->GetInventoryComponent()->SetItem(slot->index, tempItem);
			else
				OwnerHero->GetInventoryComponent()->SetNullItem(slot->index);
		}
		UE_LOG(LogTemp, Log, TEXT("%s"), *this->GetName());
	}
	else if (UStatusItemSlotWidget* toolSlot = Cast<UStatusItemSlotWidget>(oper->Payload))
	{
		ABaseItem* tempItem = OwnerHero->GetInventoryComponent()->GetItem(index);
		ABaseTool* dropTool = OwnerHero->GetToolComponent()->GetTool(toolSlot->GetSlot());

		if (ABaseTool* tempTool = Cast<ABaseTool>(tempItem))
		{
			if (OwnerHero->GetToolComponent()->GetCurrentSlot() == toolSlot->GetSlot())
			{
				OwnerHero->GetToolComponent()->DetachTool();
			}
			OwnerHero->GetToolComponent()->AddTool(toolSlot->GetSlot(), tempTool);
			OwnerHero->GetInventoryComponent()->SetItem(index, dropTool);
			if (OwnerHero->GetToolComponent()->GetCurrentSlot() == toolSlot->GetSlot())
			{
				OwnerHero->GetToolComponent()->EquipTool(OwnerHero->GetToolComponent()->GetCurrentSlot());
			}
		}
		else if (OwnerHero->GetInventoryComponent()->GetEmptySlot() != -1)
		{
			int emptySlot = OwnerHero->GetInventoryComponent()->GetEmptySlot();
			OwnerHero->GetInventoryComponent()->AddItems(Cast<ABaseItem>(dropTool));
			OwnerHero->GetToolComponent()->UnEquipTool(toolSlot->GetSlot());
		}
		
	}
	return true;
}



void UInventorySlotWidget::SetInvenText(int count)
{
	FString TextToSet = FString::Printf(TEXT("%d"), count);
	InvenText->SetText(FText::FromString(TextToSet));
}

void UInventorySlotWidget::SetInvenImage(UTexture2D* texture)
{
	InvenImage->SetBrushFromTexture(texture);
}
