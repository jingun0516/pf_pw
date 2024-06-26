// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/Menu/MenuContents/InventoryWidget/Status/UserStatusWidget.h"
#include "Characters/Hero.h"
#include "Components/StatusComponent.h"
#include "Components/UserStatusComponent.h"

void UUserStatusWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ButtonArray.Add(HPButton);
	ButtonArray.Add(StaminaButton);
	ButtonArray.Add(AttackButton);
	ButtonArray.Add(DefButton);
	ButtonArray.Add(WorkTimeButton);
	ButtonArray.Add(WeightButton);

	for (auto button : ButtonArray)
	{
		button->SetVisibility(ESlateVisibility::Hidden);
	}
	HPButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnHPButtonClicked);
	StaminaButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnStaminaButtonClicked);
	AttackButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnAttackButtonClicked);
	DefButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnDefButtonClicked);
	WorkTimeButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnWorkTimeButtonClicked);
	WeightButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnWeightButtonClicked);

	StatusButton->OnClicked.AddDynamic(this, &UUserStatusWidget::OnStatusButtonClicked);
}

void UUserStatusWidget::SetPlayerLevelText(int lv)
{
	PlayerLevelText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(lv)));
}

void UUserStatusWidget::SetExpToNextLevelText(int exp)
{
	ExpToNextLevelText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(exp)));
}

void UUserStatusWidget::SetEXPProgressBar(float percent)
{
	EXPProgressBar->SetPercent(percent);
}

void UUserStatusWidget::SetStatusPointText(int point)
{
	StatusPointText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetHPPointText(int point)
{
	HPText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetStaminaPointText(int point)
{
	StaminaText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetAttackPointText(int point)
{
	AttackText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetDefPointText(int point)
{
	DefText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetWorkTimePointText(int point)
{
	WorkTimeText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::SetWeightPointText(int point)
{
	WeightText->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(point)));
}

void UUserStatusWidget::OnStatusButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("Clicked"));

	int statusPoint = OwnerHero->GetStatusComponent()->GetStatusPoint();

	if (bButtonsVisible)
	{
		for (auto button : ButtonArray)
		{
			button->SetVisibility(ESlateVisibility::Hidden);
		}
		bButtonsVisible = false;
	}
	else
	{
		if (statusPoint > 0)
		{
			for (auto button : ButtonArray)
			{
				button->SetVisibility(ESlateVisibility::Visible);
			}
			bButtonsVisible = true;
		}
	}
}

void UUserStatusWidget::OnHPButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddHPPoint(100);
	int hpPoint = UserStatusComponent->GetHPPoint();
	SetHPPointText(hpPoint);
	SubStatusPoint();

}

void UUserStatusWidget::OnStaminaButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddStaminaPoint(100);
	int StaminaPoint = UserStatusComponent->GetStaminaPoint();
	SetStaminaPointText(StaminaPoint);

	SubStatusPoint();
}

void UUserStatusWidget::OnAttackButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddAttackPoint(100);
	int AttackPoint = UserStatusComponent->GetAttackPoint();
	SetAttackPointText(AttackPoint);

	SubStatusPoint();
}

void UUserStatusWidget::OnDefButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddDefPoint(100);
	int DefPoint = UserStatusComponent->GetDefPoint();
	SetDefPointText(DefPoint);

	SubStatusPoint();
}

void UUserStatusWidget::OnWorkTimeButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddWorkTimePoint(100);
	int WorkTimePoint = UserStatusComponent->GetWorkTimePoint();
	SetWorkTimePointText(WorkTimePoint);

	SubStatusPoint();
}

void UUserStatusWidget::OnWeightButtonClicked()
{
	UUserStatusComponent* UserStatusComponent = OwnerHero->GetUserStatusComponent();

	UserStatusComponent->AddWeightPoint(100);
	int WeightPoint = UserStatusComponent->GetWeightPoint();
	SetWeightPointText(WeightPoint);

	SubStatusPoint();
}

void UUserStatusWidget::SubStatusPoint()
{
	UStatusComponent* StatusComponent = OwnerHero->GetStatusComponent();
	int StatusPoint = StatusComponent->GetStatusPoint();
	int tempPoint = StatusPoint - 1;

	StatusComponent->SetStatusPoint(tempPoint);
	SetStatusPointText(tempPoint);
	if (tempPoint <= 0)
	{
		for (auto button : ButtonArray)
			button->SetVisibility(ESlateVisibility::Hidden);
	}
}
