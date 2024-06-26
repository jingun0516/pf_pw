#include "Widgets/Building/CraftBox/CraftBoxWidget.h"
#include "Widgets/Building/CraftBox/CraftBoxItemWidget.h"

#include "Building/BaseBuilding.h"
#include "Characters/Hero.h"
#include "Widgets/Building/ExitButtonWidget.h"
#include "CraftBoxWidget.h"
#include <Components/ScaleBox.h>
#include <Components/HorizontalBox.h>
#include "Tools/ToolsDataAsset.h"


#include "InfosDataAsset.h"

void UCraftBoxWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ExitWidget = Cast<UExitButtonWidget>(GetWidgetFromName(TEXT("BP_ExitWidget")));
	VerticalBox = Cast<UVerticalBox>(GetWidgetFromName(TEXT("BP_VerticalBox")));

	ExitWidget->ExitButton->OnClicked.AddDynamic(this, &UCraftBoxWidget::ExitWidgetFunc);
}

void UCraftBoxWidget::ExitWidgetFunc()
{
	Super::ExitWidgetFunc();
}

void UCraftBoxWidget::InitCraftBoxSlots()
{
	if (InfoDatas)
	{
		for (int i = 0; i < InfoDatas->ToolArray.Num(); i++)
		{
			if (InfoDatas->ToolArray[i])
			{
				CraftBoxSlot[i]->InitCraftBoxSlot(InfoDatas->ToolArray[i]);
				CraftBoxSlot[i]->SetOwnerBuilding(OwnerBuilding);
				CraftBoxSlot[i]->SetParentWidget(this);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("No InfoDatas"));
	}

}
