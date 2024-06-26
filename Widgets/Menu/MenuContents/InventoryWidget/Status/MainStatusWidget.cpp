// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/MenuContents/InventoryWidget/Status/MainStatusWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/StatusItemSlotWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/UserStatusWidget.h"
#include "Tools/ToolsEnum.h"

void UMainStatusWidget::NativeOnInitialized()
{
	GetTool1()->SetSlot(EToolSlot::E_First);
	GetTool2()->SetSlot(EToolSlot::E_Second);
	GetTool3()->SetSlot(EToolSlot::E_Third);
	GetTool4()->SetSlot(EToolSlot::E_Forth);
}
