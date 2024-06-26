// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include "ToBuildSlotsWidget.generated.h"

class UToBuildSlotWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UToBuildSlotsWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()

	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TMap<int, UToBuildSlotWidget*> ToBuildSlot;
};
