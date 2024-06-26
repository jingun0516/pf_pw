// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/Image.h>
#include "StatusItemSlotWidget.generated.h"

class UImage;
enum class EToolSlot;
/**
 * 
 */
UCLASS()
class PF_PW_API UStatusItemSlotWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	void SetToolImage(UTexture2D* texture);

	FORCEINLINE void SetSlot(EToolSlot InSlot) { slotEnum = InSlot; }
	FORCEINLINE EToolSlot GetSlot() { return slotEnum; }

private:
	UPROPERTY(meta = (BindWidget))
	UImage* ToolImage;

	FSlateBrush baseImage;
	EToolSlot slotEnum;
};
