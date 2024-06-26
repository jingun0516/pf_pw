// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "MainInventoryWidget.generated.h"

class UInventorySlotsWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UMainInventoryWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	UInventorySlotsWidget* GetInventorySlotsWidget() { return WB_InventorySlots; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UInventorySlotsWidget* WB_InventorySlots;
};
