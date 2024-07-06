// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/Image.h>
#include <Components/TextBlock.h>
#include "InventorySlotWidget.generated.h"

class UDragDropOperation;
/**
 * 
 */
UCLASS()
class PF_PW_API UInventorySlotWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation);

	void SetInvenText(int count);
	void SetInvenImage(UTexture2D* texture);

	UFUNCTION(BlueprintCallable)
	void SetIndex(int InIndex) { index = InIndex; }

	FORCEINLINE int GetIndex() { return index; }

	FORCEINLINE void BrushInvenImage(UTexture2D* texture) { InvenImage->SetBrushFromTexture(texture); }
	FORCEINLINE void SetInvenTextVisibility(bool visible) {
		if (visible) InvenText->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		else InvenText->SetVisibility(ESlateVisibility::Hidden);
	}

private:
	UPROPERTY(meta = (BindWidget))
	UImage* InvenImage;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* InvenText;

	int index;
	bool bIsDragging;
	FVector2D DragStartPosition;
	FVector2D DragEndPosition;
	UInventorySlotWidget* tempWidget;
	FSlateBrush baseImage;
};
