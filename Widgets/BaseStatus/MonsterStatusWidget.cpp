// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/BaseStatus/MonsterStatusWidget.h"
#include "Characters/BaseCharacter.h"
#include "Components/StatusComponent.h"

void UMonsterStatusWidget::SetMonsterName(FText InName)
{
	if(MonsterName)
		MonsterName->SetText(InName);
	if (TeamMonster)
		TeamMonster->SetText(InName);
}

void UMonsterStatusWidget::SetHP(ABaseCharacter* InMonster)
{
	float InCurHP = InMonster->GetStatusComponent()->GetHP();
	float InMaxHP = InMonster->GetStatusComponent()->GetMaxHP();

	if(CurHP)
		CurHP->SetText(FText::AsNumber(InCurHP));
	if(MaxHP)
		MaxHP->SetText(FText::AsNumber(InMaxHP));
	if(MonsterHPBar)
		MonsterHPBar->SetPercent(InCurHP / InMaxHP);
}

void UMonsterStatusWidget::SetTeamMonsterName()
{
	MonsterName->SetVisibility(ESlateVisibility::Hidden);
	MonsterName_1->SetVisibility(ESlateVisibility::Hidden);
	MonsterName_2->SetVisibility(ESlateVisibility::Hidden);
	
	TeamMonster->SetVisibility(ESlateVisibility::Visible);
	TeamMonster_1->SetVisibility(ESlateVisibility::Visible);
	TeamMonster_2->SetVisibility(ESlateVisibility::Visible);
}
