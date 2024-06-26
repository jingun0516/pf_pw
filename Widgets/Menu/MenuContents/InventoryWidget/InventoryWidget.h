// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "InventoryWidget.generated.h"

class UMainInventoryWidget;
class UMainStatusWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UInventoryWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE UMainInventoryWidget* GetMainInventoryWidget() { return WB_MainInventory; }
	FORCEINLINE UMainStatusWidget* GetMainStatusWidget() { return WB_MainStatus; }

private:
	UPROPERTY(meta = (BindWidget))
	UMainInventoryWidget* WB_MainInventory;

	UPROPERTY(meta = (BindWidget))
	UMainStatusWidget* WB_MainStatus;
};
