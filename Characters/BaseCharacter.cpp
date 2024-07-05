// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/BaseCharacter.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Helper.h"

#include "Components/CapsuleComponent.h"
#include "Components/ToolComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/StatusComponent.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/InventoryComponent.h"

#include "Tools/BaseTool.h"

#include "DamagedActor.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Blueprint/UserWidget.h"

#include "Resources/BaseResource.h"
#include "Resources/BaseRock.h"
#include "Resources/BaseTree.h"

#include "Logging/LogMacros.h"
#include <Kismet/GameplayStatics.h>
#include <Components/TextBlock.h>
#include "Engine/CollisionProfile.h"

#include "AI/BaseAI.h"
#include "Characters/Hero.h"

DEFINE_LOG_CATEGORY(CharacterLog);

ABaseCharacter::ABaseCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	StatusComponent = Helper::CreateActorComponent<UStatusComponent>(this, "Status Component");
	ToolComponent = Helper::CreateActorComponent<UToolComponent>(this, "Tool Component");
	StateComponent = Helper::CreateActorComponent<UStateComponent>(this, "State Component");
	BuildingComponent = Helper::CreateActorComponent<UBuildingComponent>(this, "Building Component");
	PocketmonComponent = Helper::CreateActorComponent<UPocketmonComponent>(this, "Pocketmon Component");
	InventoryComponent = Helper::CreateActorComponent<UInventoryComponent>(this, "Inventory Component");

	DamageWidgetClass = Helper::GetClass<UUserWidget>(L"/Game/Widgets/WB_DamageWidget");
	//SetCharacterMovement();
}

void ABaseCharacter::CalDamageDirection(FVector ActorLocation, FVector DCLocation, FVector forwardVector)
{
	double angle = Helper::GetAngleBetweenActors(ActorLocation, DCLocation, forwardVector);

	if (angle >= 360-45 && angle < 45)
	{
		direction = 0; //  DamageDirection::Forward;
	}
	else if (angle >= 45 && angle >= 45 + 90)
	{
		direction = 1; // DamageDirection::Right;
	}
	else if (angle >= 45 + 90 && angle >= 45 + 90 + 90)
	{
		direction = 2; // DamageDirection::Back;
	}
	else
	{
		direction = 3; // DamageDirection::Left;
	}
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerC = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DamageCauser->GetOwner() == this) return 0.f;

	if (Cast<AHero>(this))
	{
		if (ABaseMonster* monster = Cast<ABaseMonster>(DamageCauser->GetOwner()))
		{
			if (!(monster->GetIsWild())) return 0.f;		// 야생의 몬스터가 아닐 경우 플레이어 데미지 X
			if (ABaseAI* aiMonster = Cast<ABaseAI>(monster))
			{
				if (!(aiMonster->GetCanAttack())) return 0.f;	// 공격 불가 상태일 시 데미지 X
			}
		}
	}
	if (ABaseMonster* monster = Cast<ABaseMonster>(this))
	{
		if (!(monster->GetIsWild()))			
		{
			if (Cast<AHero>(DamageCauser->GetOwner()))		// 야생의 몬스터가 아닐 경우 플레이어가 때리지 못함
				return 0.f;
		}
	}

	UE_LOG(CharacterLog, Log, TEXT("%s"), *DamageCauser->GetName());
	float GotDamage = DamageAmount - GetStatusComponent()->GetArmor();
	if ((GetStateComponent()->GetState() != E_StateType::E_Dead) && EventInstigator->GetOwner() != this)
	{
		if (GetStatusComponent())
		{
			float HP = GetStatusComponent()->GetHP();
			float NextHP = HP - GotDamage;
			UE_LOG(CharacterLog, Log, TEXT("NextHP : %f"), NextHP);
			GetStatusComponent()->SetHP(NextHP);
			/*
			FVector DCLocation = DamageCauser->GetActorLocation();
			FVector ActorLocation = this->GetActorLocation();
			FVector forwardVector = this->GetActorForwardVector();

			CalDamageDirection(ActorLocation, DCLocation, forwardVector);
			*/
			
			if (NextHP <= 0)
			{
				GetStateComponent()->SetState(E_StateType::E_Dead);
				if (Cast<ABaseCharacter>(DamageCauser->Owner) == PlayerC)
				{
					PlayerC->GetStatusComponent()->AddEXP(GetStatusComponent()->GetEXP());
					UE_LOG(CharacterLog, Log, TEXT("Added EXP: %d"), GetStatusComponent()->GetEXP());
				}
			}
			else
				GetStateComponent()->SetState(E_StateType::E_Hit);

			if (ADamagedActor* DActor = GetWorld()->SpawnActor<ADamagedActor>(GetActorLocation(), FRotator()))
			{
				DActor->SetDamage(GotDamage);
			}
		}
	}
	UE_LOG(CharacterLog, Log, TEXT("GotDamage: %f"), GotDamage);
	return GotDamage;
}

void ABaseCharacter::OnApplyDamage(AActor* DamagedActor, AActor* DamagedCauser, float Damage)
{
	if (!GetStatusComponent()) return;

	float dmg = GetStatusComponent()->GetDamage();
	float dmgToTree = GetStatusComponent()->GetDamageToTree();
	float dmgToRock = GetStatusComponent()->GetDamageToRock();

	if (ABaseCharacter* DCharacter = Cast<ABaseCharacter>(DamagedActor))
	{
		UGameplayStatics::ApplyDamage(DCharacter, dmg, GetController(), DamagedCauser, NULL);
	}
	
	if (ABaseResource* DResource = Cast<ABaseResource>(DamagedActor))
	{
		if(Cast<ABaseAI>(this))
			UGameplayStatics::ApplyDamage(DResource, dmg, GetController(), DamagedCauser, NULL);
		else
		{
			if (ABaseTree* tree = Cast<ABaseTree>(DResource))
			{
				UGameplayStatics::ApplyDamage(DResource, dmgToTree, GetController(), DamagedCauser, NULL);
			}
			if (ABaseRock* rock = Cast<ABaseRock>(DResource))
			{
				UGameplayStatics::ApplyDamage(DResource, dmgToRock, GetController(), DamagedCauser, NULL);
			}
		}
	}
}

void ABaseCharacter::SetInfos(ABaseTool* tool)
{
	if (!tool) return;
	if (GetStatusComponent())
	{
		GetStatusComponent()->SetDamage(tool->GetDamage());
		GetStatusComponent()->SetDamageToTree(tool->GetDamageToTree());
		GetStatusComponent()->SetDamageToRock(tool->GetDamageToRock());
	}
}

void ABaseCharacter::SetCharacterMovement()
{
}

void ABaseCharacter::DoMainAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoMainAction);
}

void ABaseCharacter::EndMainAction()
{
	MULTICAST_DELEGATE_BROADCAST(DEndMainAction);
}

void ABaseCharacter::DoSubAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoSubAction);
}

void ABaseCharacter::EndSubAction()
{
	MULTICAST_DELEGATE_BROADCAST(DEndSubAction);
}
