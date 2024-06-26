// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Image.h>
#include <Components/Button.h>
#include <Components/EditableTextBox.h>
#include <Components/HorizontalBox.h>
#include "BuildingClickedWidget.generated.h"

/**
 *
 */
class ABaseItem;

UCLASS()
class PF_PW_API UBuildingClickedWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	FORCEINLINE UUserWidget* GetInterActionWidget() { return InterActionWidget; }
	FORCEINLINE void SetInterActionWidget(UUserWidget* widget) { InterActionWidget = widget; }

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

	FORCEINLINE void SetItemClassAndCounts(TArray<TSubclassOf<ABaseItem>> InitemClass, TArray<int> InitemCounts)
	{
		this->itemClass = InitemClass;
		this->itemCounts = InitemCounts;
	}
	FORCEINLINE void SetSpawnBuildingClass(TSubclassOf<ABaseBuilding> InBuildingClass) { SpawnBuildingClass = InBuildingClass; }
	bool CanBuild = false;
	bool CanCraft = false;
	TArray<TSubclassOf<ABaseItem>> itemClass;
	TArray<int> itemCounts;

	TSubclassOf<ABaseBuilding> SpawnBuildingClass;

	UPROPERTY(meta = (BindWidget))
	UButton* YesButton;

	UPROPERTY(meta = (BindWidget))
	UButton* NoButton;

	UFUNCTION()
	void NoButtonClicked();

	UFUNCTION()
	void YesButtonClicked();

	void SetSlots(TArray<UTexture2D*> itemsImage, TArray<int> counts);
	void SetCurText(int cnt, int index);
	void SetHorizonOpacity(int num, bool bCheck);

	UFUNCTION()
	void DoSubItemsForCraft();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UUserWidget* InterActionWidget;

	UUserWidget* GetParentWidget() { return ParentWidget; }
	void SetParentWidget(UUserWidget* InParentWidget) { ParentWidget = InParentWidget; }
	UUserWidget* ParentWidget;
};
