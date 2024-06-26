#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "MenuWidget.generated.h"

class AHero;
class UInventoryWidget;
class UPocketmonWidget;

UCLASS()
class PF_PW_API UMenuWidget : public UBasePartsMenuWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;

	FORCEINLINE UInventoryWidget* GetInventoryWidget() { return WB_InventoryWidget; }
	FORCEINLINE UPocketmonWidget* GetPocketmonWidget() { return WB_PocketmonWidget; }
private:
	UPROPERTY(meta = (BindWidget))
	UInventoryWidget* WB_InventoryWidget;

	UPROPERTY(meta = (BindWidget))
	UPocketmonWidget* WB_PocketmonWidget;
};
