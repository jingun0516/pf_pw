// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/Image.h>
#include "MainStatusWidget.generated.h"

class UStatusItemSlotWidget;
class UUserStatusWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UMainStatusWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()
	
public:
	UStatusItemSlotWidget* GetTool1() { return Tool1; }
	UStatusItemSlotWidget* GetTool2() { return Tool2; }
	UStatusItemSlotWidget* GetTool3() { return Tool3; }
	UStatusItemSlotWidget* GetTool4() { return Tool4; }

	FORCEINLINE UUserStatusWidget* GetUserStatusWidget() { return WB_UserStatus; }

private:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UStatusItemSlotWidget* Tool1;
	UPROPERTY(meta = (BindWidget))
	UStatusItemSlotWidget* Tool2;
	UPROPERTY(meta = (BindWidget))
	UStatusItemSlotWidget* Tool3;
	UPROPERTY(meta = (BindWidget))
	UStatusItemSlotWidget* Tool4;

	UPROPERTY(meta = (BindWidget))
	UUserStatusWidget* WB_UserStatus;
};
