// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include <Components/Button.h>
#include <Components/Image.h>
#include "CraftBoxItemWidget.generated.h"

class UBuildingClickedWidget;
class UToolsDataAsset;
class ABaseTool;
class ABaseItem;
/**
 * 
 */
UCLASS()
class PF_PW_API UCraftBoxItemWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;    
	
public:
	UFUNCTION()
	void SpawnTool();

	UFUNCTION()
	void InitCraftBoxSlot(UToolsDataAsset* InDATool);

	UFUNCTION()
	void SetCraftState();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UButton* CraftBoxItemButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UImage* CraftBoxItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseTool> SpawnToolClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UTexture2D* SpawnToolImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	float CraftTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<ABaseItem>> RequiredItems;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<UTexture2D*> RequiredImages;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<int> RequiredCounts;

	UBuildingClickedWidget* CraftBoxClickedWidget;
};
