#include "Widgets/YesOrNoWidget.h"


void UYesOrNoWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	NoButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_NoButton")));
	YesButton = Cast<UButton>(GetWidgetFromName(TEXT("BP_YesButton")));

	if (NoButton)
		NoButton->OnClicked.AddDynamic(this, &UYesOrNoWidget::NoButtonClicked);
	else UE_LOG(LogTemp, Log, TEXT("NONO Button"));
	if(YesButton)
		YesButton->OnClicked.AddDynamic(this, &UYesOrNoWidget::YesButtonClicked);
}

void UYesOrNoWidget::NoButtonClicked()
{
	//this->SetVisibility(ESlateVisibility::Hidden);
	this->Destruct();
}

void UYesOrNoWidget::YesButtonClicked()
{

}

void UYesOrNoWidget::SetNextWidget(UUserWidget* InNextWidget)
{
	NextWidget = InNextWidget;
}
