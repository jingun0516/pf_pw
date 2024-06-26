// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "InventorySlotsWidget.generated.h"

class UInventorySlotWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UInventorySlotsWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE TMap<int, UInventorySlotWidget*> GetInventorySlot() { return InventorySlot; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UInventorySlotWidget*> InventorySlot;
};
