#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseBuildingWidget.generated.h"

class ABaseBuilding;
class AHero;
class UInfosDataAsset;
class UYesNoWidget;
/**
 * 
 */
UCLASS()
class PF_PW_API UBaseBuildingWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetOwnerBuilding(ABaseBuilding* building);

	virtual void ExitWidgetFunc();

	UFUNCTION()
	FORCEINLINE void SetParentWidget(UUserWidget* widget) { ParentWidget = widget; }

	UFUNCTION()
	FORCEINLINE UUserWidget* GetParentWidget() { return ParentWidget; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ABaseBuilding* OwnerBuilding;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AHero* OwnerPlayer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UInfosDataAsset* InfoDatas;

	UYesNoWidget* YesNoWidget;

	UUserWidget* ParentWidget;
};
