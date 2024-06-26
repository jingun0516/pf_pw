#include "Components/Pocketmon/PocketmonComponent.h"
#include "Components/Pocketmon/PocketmonEnum.h"
#include "Components/StatusComponent.h"

#include "Helper.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Characters/Monsters/BaseMonster.h"

#include "CatchActor.h"
#include "CatchFailActor.h"
#include "CatchSuccedActor.h"

#include "Actions/BaseAction.h"
#include "Actions/ThrowAction.h"
#include "Logging/LogMacros.h"

#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonWidget.h"
#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonSlotsWidget.h"
#include "Widgets/Menu/MenuContents/PocketmonWidget/PocketmonSlotWidget.h"

DEFINE_LOG_CATEGORY(PokemonComp);

UPocketmonComponent::UPocketmonComponent()
{
	PokcetmonSlotWidgetClass = Helper::GetClass<UPocketmonSlotWidget>(L"/Game/Widgets/MenuWidget/MenuContents/PocketmonWidget/WB_PocketmonSlot");
}

void UPocketmonComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!OwnerCharacter) return;
	OwnerHero = Cast<AHero>(GetOwner());
	if (!OwnerHero) return;
	
	if (OwnerHero)
	{
		OwnerHero->DPocketmonNextSlot.AddUFunction(this, "PocketmonNextSlot");
		OwnerHero->DPocketmonPrevSlot.AddUFunction(this, "PocketmonPrevSlot");
	}
	
	SetCurrentSlot(EPocketmonSlot::E_First);
	SetNextPrevSlot();
}

float UPocketmonComponent::CalCatchPercent(ABaseMonster* pocketmon)
{
	float hp = pocketmon->GetStatusComponent()->GetHP();
	float maxhp = pocketmon->GetStatusComponent()->GetMaxHP();
	float HPpercent = 1.f - hp / maxhp;

	float AdditionalHPpercent = 0.3f * HPpercent;	// HP차로 변하는 최대 퍼센트 => 30%
	float AdditionalLVpercent = 0.f;

	int PlayerLV = 1;
	int MonsterLV = 1;

	if (OwnerHero)
	{
		if (OwnerHero->GetStatusComponent())
		{
			PlayerLV = OwnerHero->GetStatusComponent()->GetLevel();
			if (pocketmon->GetStatusComponent())
				MonsterLV = pocketmon->GetStatusComponent()->GetLevel();
		}
	}

	float LVpercent = (float)(PlayerLV - MonsterLV);
	AdditionalLVpercent = 0.04f * LVpercent;
	if (AdditionalLVpercent >= 0.2f)		// 레벨차로 변하는 퍼센트 => 20%
		AdditionalLVpercent = 0.2f;
	if (AdditionalLVpercent <= -0.2f)
		AdditionalLVpercent = -0.2f;

	float exFinalPercent = AdditionalHPpercent + AdditionalLVpercent;

	return exFinalPercent;
}

void UPocketmonComponent::PocketmonNextSlot()
{
	if (GetCurrentSlot() == EPocketmonSlot::E_First)
		SetCurrentSlot(EPocketmonSlot::E_Second);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Second)
		SetCurrentSlot(EPocketmonSlot::E_Third);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Third)
		SetCurrentSlot(EPocketmonSlot::E_Forth);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Forth)
		SetCurrentSlot(EPocketmonSlot::E_Fifth);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Fifth)
		SetCurrentSlot(EPocketmonSlot::E_Sixth);

	SetNextPrevSlot();
}

void UPocketmonComponent::PocketmonPrevSlot()
{
	if (GetCurrentSlot() == EPocketmonSlot::E_Second)
		SetCurrentSlot(EPocketmonSlot::E_First);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Third)
		SetCurrentSlot(EPocketmonSlot::E_Second);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Forth)
		SetCurrentSlot(EPocketmonSlot::E_Third);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Fifth)
		SetCurrentSlot(EPocketmonSlot::E_Forth);
	else if (GetCurrentSlot() == EPocketmonSlot::E_Sixth)
		SetCurrentSlot(EPocketmonSlot::E_Fifth);

	SetNextPrevSlot();
}

void UPocketmonComponent::SetNextPrevSlot()
{
	if (GetCurrentSlot() == EPocketmonSlot::E_First)
	{
		PrevSlot = EPocketmonSlot::E_Sixth;
		NextSlot = EPocketmonSlot::E_Second;
	}
	else if (GetCurrentSlot() == EPocketmonSlot::E_Second)
	{
		PrevSlot = EPocketmonSlot::E_First;
		NextSlot = EPocketmonSlot::E_Third;
	}
	else if (GetCurrentSlot() == EPocketmonSlot::E_Third)
	{
		PrevSlot = EPocketmonSlot::E_Second;
		NextSlot = EPocketmonSlot::E_Forth;
	}
	else if (GetCurrentSlot() == EPocketmonSlot::E_Forth)
	{
		PrevSlot = EPocketmonSlot::E_Third;
		NextSlot = EPocketmonSlot::E_Fifth;
	}
	else if (GetCurrentSlot() == EPocketmonSlot::E_Fifth)
	{
		PrevSlot = EPocketmonSlot::E_Forth;
		NextSlot = EPocketmonSlot::E_Sixth;
	}
	else if (GetCurrentSlot() == EPocketmonSlot::E_Sixth)
	{
		PrevSlot = EPocketmonSlot::E_Fifth;
		NextSlot = EPocketmonSlot::E_First;
	}
	if (OwnerHero)
		OwnerHero->OnPocketmonSlotChanged();
}

ABaseMonster* UPocketmonComponent::CheckIsSpawned()
{
	for (auto monster : Pocketmons)
	{
		if (monster.Value->GetSpawnType() == ESpawnedType::E_Spawned)
			return monster.Value;
	}
	return nullptr;
}

EPocketmonSlot UPocketmonComponent::IsEmptySlot()
{
	if (!Pocketmons.FindRef(EPocketmonSlot::E_First)) return EPocketmonSlot::E_First;
	else if (!Pocketmons.FindRef(EPocketmonSlot::E_Second)) return EPocketmonSlot::E_Second;
	else if (!Pocketmons.FindRef(EPocketmonSlot::E_Third)) return EPocketmonSlot::E_Third;
	else if (!Pocketmons.FindRef(EPocketmonSlot::E_Forth)) return EPocketmonSlot::E_Forth;
	else if (!Pocketmons.FindRef(EPocketmonSlot::E_Fifth)) return EPocketmonSlot::E_Fifth;
	else if (!Pocketmons.FindRef(EPocketmonSlot::E_Sixth)) return EPocketmonSlot::E_Sixth;

	return EPocketmonSlot::E_None;
}

void UPocketmonComponent::AddPocketmon(EPocketmonSlot Slot, ABaseMonster* pocketmon)
{
	Pocketmons.Add(Slot, pocketmon);

	pocketmon->SetWild(false);
	pocketmon->SetTeamMonster();

	if (Slot == GetCurrentSlot() || Slot == GetPrevSlot() || Slot == GetNextSlot())
	{
		OwnerHero->OnPocketmonSlotChanged();
	}

	UPocketmonSlotsWidget* SlotsWidget = OwnerHero->GetMenuWidget()->GetPocketmonWidget()->GetPocketmonSlotsWidget();
	UPocketmonSlotWidget* widget = CreateWidget<UPocketmonSlotWidget>(GetWorld(), PokcetmonSlotWidgetClass);

	if (widget && pocketmon)
	{
		widget->SetMonsterLV(pocketmon->GetStatusComponent()->GetLevel());
		widget->SetMonsterName(pocketmon->GetMonName());
		float MonsterHP = pocketmon->GetStatusComponent()->GetHP();
		float MonsterMaxHP = pocketmon->GetStatusComponent()->GetMaxHP();
		widget->SetHPProgressBar(MonsterHP / MonsterMaxHP);
		widget->SetHPText(MonsterHP, MonsterMaxHP);
		//widget->SetHungerProgressBar();
		widget->SetMonsterImage(pocketmon->GetTexture());

		SlotsWidget->AddPocketmon(widget);
	}
}