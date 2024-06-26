// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/BasePartsMenuWidget.h"
#include "Characters/Hero.h"


void UBasePartsMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}
