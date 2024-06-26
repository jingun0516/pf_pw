// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "PocketmonWidget.generated.h"

class UPocketmonSlotsWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UPocketmonWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()
	
public:
	UPocketmonSlotsWidget* GetPocketmonSlotsWidget() { return WB_PocketmonSlots; }

private:
	UPROPERTY(meta = (BindWidget))
	UPocketmonSlotsWidget* WB_PocketmonSlots;
};
