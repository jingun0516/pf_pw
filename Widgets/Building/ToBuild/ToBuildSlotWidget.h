// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Image.h>
#include <Components/Button.h>
#include "ToBuildSlotWidget.generated.h"

class ABaseItem;
class UBuildingClickedWidget;
class UDA_ToBuildDataAsset;
/**
 * 
 */
UCLASS()
class PF_PW_API UToBuildSlotWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable)
	void InitToBuildSlot(UDA_ToBuildDataAsset* InDaBuilding);

	UFUNCTION()
	void ToBuildSlotClicked();

private:
	UBuildingClickedWidget* BuildingClickedWidget;

	UPROPERTY(meta = (BindWidget))
	UImage* ToBuildSlot;

	UPROPERTY(meta = (BindWidget))
	UButton* ToBuildButton;
	
	TSubclassOf<ABaseBuilding> SpawnBuildingClass;

	UTexture2D* SpawnBuildingImage;

	TArray<TSubclassOf<ABaseItem>> RequiredItems;
	TArray<UTexture2D*> RequiredImages;
	TArray<int> RequiredCounts;
};
