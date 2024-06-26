// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BaseStatus/BaseStatusWidget.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Characters/Hero.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Components/StatusComponent.h"

void UBaseStatusWidget::NativeOnInitialized()
{
	PlayerCharacter = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	PocketmonComponent = PlayerCharacter->GetPocketmonComponent();
}

void UBaseStatusWidget::SetPocketmon()
{
	if (PocketmonComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("YES PocketmonComponent"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("NO PocketmonComponent"));

	}
	if (ABaseMonster* PrevMonster = PocketmonComponent->GetPocketmon(PocketmonComponent->GetPrevSlot()))
	{
		UTexture2D* prevTexture = PrevMonster->GetTexture();
		PrevMonSlot->SetBrushFromTexture(prevTexture);
		UE_LOG(LogTemp, Log, TEXT("PrevMonBrushed"));
	}
	else
		PrevMonSlot->SetBrushFromTexture(nullptr);
	
	if (ABaseMonster* CurMonster = PocketmonComponent->GetCurPocketmon())
	{
		UTexture2D* curTexture = CurMonster->GetTexture();
		CurMonSlot->SetBrushFromTexture(curTexture);
		UE_LOG(LogTemp, Log, TEXT("CurMonBrushed"));
		CurMonName->SetText(CurMonster->GetMonName());
		CurMonLV->SetText(FText::FromString(FString::Printf(TEXT("%d"), CurMonster->GetStatusComponent()->GetLevel())));
	}
	else
	{
		CurMonSlot->SetBrushFromTexture(nullptr); 
		CurMonName->SetText(FText::FromString("Empty Slot"));
		CurMonLV->SetText(FText::FromString("-"));
	}
	
	if (ABaseMonster* NextMonster = PocketmonComponent->GetPocketmon(PocketmonComponent->GetNextSlot()))
	{
		UTexture2D* nextTexture = NextMonster->GetTexture();
		NextMonSlot->SetBrushFromTexture(nextTexture);
		UE_LOG(LogTemp, Log, TEXT("NextMonBrushed"));
	}
	else
		NextMonSlot->SetBrushFromTexture(nullptr);
	
}

void UBaseStatusWidget::SetHPBar(float HP, float MaxHP)
{
	HPProgressBar->SetPercent(HP / MaxHP);
}

void UBaseStatusWidget::SetEXPBar(int EXP, int NextEXP)
{
	EXPProgressBar->SetPercent((float)EXP / (float)NextEXP);
}

void UBaseStatusWidget::SetCharacterLV(int LV)
{
	CharacterLV->SetText(FText::AsNumber(LV));

}
