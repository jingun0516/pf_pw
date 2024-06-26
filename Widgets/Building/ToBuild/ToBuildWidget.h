#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include "ToBuildWidget.generated.h"

class UToBuildSlotsWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UToBuildWidget : public UBaseBuildingWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	UToBuildSlotsWidget* WB_ToBuildSlots;
};
