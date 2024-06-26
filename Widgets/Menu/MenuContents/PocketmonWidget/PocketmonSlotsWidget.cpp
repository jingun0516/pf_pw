// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonSlotsWidget.h"
#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonSlotWidget.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Components/StatusComponent.h"
#include "Helper.h"

#define MAX_COUNTS 6

void UPocketmonSlotsWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UPocketmonSlotsWidget::AddPocketmon(UPocketmonSlotWidget* widget)
{
	if (bFull)
	{
		widget->Destruct();
		return;
	}

	if(widget)
		PocketmonSlotsScrollBox->AddChild(widget);

	counts++;
	if (counts >= MAX_COUNTS) bFull = true;
	
}
