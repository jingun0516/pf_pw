#pragma once

#include "CoreMinimal.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include <Components/ScrollBox.h>
#include "PocketmonSlotsWidget.generated.h"

class ABaseMonster;
class UPocketmonSlotWidget;
class UScrollBox;
/**
 * 
 */
UCLASS()
class PF_PW_API UPocketmonSlotsWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	void AddPocketmon(UPocketmonSlotWidget* widget);

private:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* PocketmonSlotsScrollBox;

	bool bFull = false;

	int counts = 0;
};
