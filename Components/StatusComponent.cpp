#include "Components/StatusComponent.h"
#include "Components/UserStatusComponent.h"
#include "DataTable/ExpToLevelUpDataTable.h"
#include "Helper.h"
#include <Kismet/GameplayStatics.h>
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/MainStatusWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/StatusItemSlotWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/UserStatusWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/InventoryWidget.h"
#include "Widgets/BaseStatus/BaseStatusWidget.h"

UStatusComponent::UStatusComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	LevelUpDataTable = Helper::GetAsset<UDataTable>(L"/Game/DataTable/ExpToLevelUp");
	LevelUpEffect = Helper::GetAsset<UParticleSystem>(L"/Game/Assets/Luos8Elements/Particles/Light/Par_4E_LightDef_01");
}

void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());

	DOnExpAdded.AddUFunction(this, "OnExpAdded");
	DOnLevelUp.AddUFunction(this, "OnLevelUp");
	DOnSetHP.AddUFunction(this, "OnSetHP");
}


void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UStatusComponent::SetHP(float hp)
{
	if (hp <= 0) hp = 0;

	this->HP = hp;

	if (DOnSetHP.IsBound())
		DOnSetHP.Broadcast();
}

void UStatusComponent::SetMaxHP(float Maxhp)
{
	this->MaxHP = Maxhp;

	if (DOnSetHP.IsBound())
		DOnSetHP.Broadcast();
}

void UStatusComponent::LevelUp()
{  
	if (LV >= MaxLV) return;

	UE_LOG(LogTemp, Log, TEXT("LEVEL UP!"));

	if (LV < MaxLV) LV = LV + 1; 
	
	if (LevelUpEffect && OwnerCharacter)
	{
		UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
		(
			this,
			LevelUpEffect,
			OwnerCharacter->GetMesh()->GetSocketLocation(L"root")
		);
		SetHP(GetMaxHP());
	}
	if (DOnLevelUp.IsBound()) DOnLevelUp.Broadcast();
}

void UStatusComponent::AddEXP(int InExp)
{
	SetEXP(GetEXP() + InExp);

	if (DOnExpAdded.IsBound()) DOnExpAdded.Broadcast();
}

void UStatusComponent::OnExpAdded()
{
	if (LevelUpDataTable)
	{
		for (int32 i = 1; i <= 10; i++)
		{
			FLevelUpTableRow* LevelUpTableRow = LevelUpDataTable->FindRow<FLevelUpTableRow>(FName(*(FString::FormatAsNumber(GetLevel()))), FString(""));

			if (!LevelUpTableRow) return;

			if (GetEXP() >= (*LevelUpTableRow).TotalExp)
			{
				LevelUp();
				UE_LOG(LogTemp, Log, TEXT("LEVEL UP!"));
			}
		}
		FLevelUpTableRow* LevelUpTableRowNext = LevelUpDataTable->FindRow<FLevelUpTableRow>(FName(*(FString::FormatAsNumber(GetLevel()))), FString(""));
		FLevelUpTableRow* LevelUpTableRowPrev = LevelUpDataTable->FindRow<FLevelUpTableRow>(FName(*(FString::FormatAsNumber(GetLevel() - 1))), FString(""));

		if (LevelUpTableRowNext)
			NextEXP = (*LevelUpTableRowNext).ExpToNextLevel;
		if(LevelUpTableRowPrev)
			PrevEXP = (*LevelUpTableRowPrev).ExpToNextLevel;
	}

	if (AHero* hero = Cast<AHero>(OwnerCharacter))
	{
		UE_LOG(LogTemp, Log, TEXT("%d %d %d"), GetEXP(), PrevEXP, NextEXP);
		hero->SetExpBar(GetEXP()-PrevEXP, NextEXP);
	}
}

void UStatusComponent::OnLevelUp()
{
	if (AHero* hero = Cast<AHero>(OwnerCharacter))
	{
		hero->SetLevelWidget(GetLevel());
		SetStatusPoint(GetStatusPoint() + 1);
		hero->GetMenuWidget()->GetInventoryWidget()->GetMainStatusWidget()->GetUserStatusWidget()->SetStatusPointText(GetStatusPoint());
	}
}

void UStatusComponent::OnSetHP()
{
	if (AHero* hero = Cast<AHero>(OwnerCharacter))
	{
		if(hero->GetBaseStatusWidget())
			hero->SetHPBar(GetHP(), GetMaxHP());
	}
	if (ABaseMonster* monster = Cast<ABaseMonster>(OwnerCharacter))
	{
		monster->SetMonsterStatus();
		UE_LOG(LogTemp, Error, TEXT("MonsterStatusWidget Complete"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("MonsterStatusWidget asdfasdfasdf"));
	}
}

