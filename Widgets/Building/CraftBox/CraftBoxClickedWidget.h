// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Image.h>
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Components/HorizontalBox.h>
#include "CraftBoxClickedWidget.generated.h"

/**
 * 
 */
class ABaseItem;

UCLASS()
class PF_PW_API UCraftBoxClickedWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION()
	void NoButtonClicked();

	UFUNCTION()
	void YesButtonClicked();

	void SetSlots(TArray<UTexture2D*> itemsImage, TArray<int> counts);
	void SetCurText(int cnt, int index);
	void SetHorizonOpacity(int num, bool bCheck);

	UFUNCTION()
	void DoSubItemsForCraft();

private:
	UPROPERTY(meta = (BindWidget))
	UImage* SelectedImage;

	UPROPERTY(meta = (BindWidget))
	UImage* Slot1Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Slot2Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Slot3Image;

	UPROPERTY(meta = (BindWidget))
	UImage* Slot4Image;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurCount1;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurCount2;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurCount3;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* CurCount4;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RequiredCount1;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RequiredCount2;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RequiredCount3;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* RequiredCount4;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* Horizon1;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* Horizon2;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* Horizon3;
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* Horizon4;

	bool CanCraft = false;
	TArray<TSubclassOf<ABaseItem>> itemClass;
	TArray<int> itemCounts;

	UPROPERTY(meta = (BindWidget))
	UButton* YesButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NoButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* InterActionWidget;
};
