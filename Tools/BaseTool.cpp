#include "Tools/BaseTool.h"
#include "Tools/ToolsDataAsset.h"

#include "Characters/Hero.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/BaseCharacter.h"

#include "Actions/BaseAction.h"
#include "Actions/ActionDataAsset.h"
#include "Components/ToolComponent.h"
#include "Components/SceneComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InventoryComponent.h"
#include "Resources/BaseResource.h"
#include "Blueprint/UserWidget.h"
#include "Logging/LogMacros.h"
#include "Helper.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h" 

DEFINE_LOG_CATEGORY(ToolLog);

ABaseTool::ABaseTool()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABaseTool::BeginPlay()
{
	Super::BeginPlay();

	countable = ECountableType::E_UnCountable;

	PlayerC = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	SetDatas();
}

void ABaseTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseTool::SpawnActions()
{
	if (Actions->MainAction)
	{
		if(!MainAction)
			MainAction = NewObject<UBaseAction>(this, Actions->MainAction);
		if (MainAction)
		{
			MainAction->SetOwner(Cast<ABaseCharacter>(GetOwner()), this);
		}
		if (!Actions->MainMontages.IsEmpty())
		{
			for (auto action : Actions->MainMontages)
			{
				MainAction->Montages.Add(action);
			}
		}
	}
	if (Actions->SubAction)
	{
		if(!SubAction)
		SubAction = NewObject<UBaseAction>(this, Actions->SubAction);
		if(SubAction)
			SubAction->SetOwner(Cast<ABaseCharacter>(GetOwner()), this);
		if (!Actions->SubMontages.IsEmpty())
		{
			for (auto action : Actions->SubMontages)
			{
				SubAction->Montages.Add(action);
			}
		}
	}
	if (Actions->ReloadAction)
	{
		if(!ReloadAction)
			ReloadAction = NewObject<UBaseAction>(this, Actions->ReloadAction);
		if(ReloadAction)
			ReloadAction->SetOwner(Cast<ABaseCharacter>(GetOwner()), this);
		if (!Actions->ReloadMontages.IsEmpty())
		{
			for (auto action : Actions->ReloadMontages)
			{
				ReloadAction->Montages.Add(action);
			}
		}
	}
	if (Actions->ThrowAction)
	{
		if(!ThrowAction)
			ThrowAction = NewObject<UBaseAction>(this, Actions->ThrowAction);
		if (ThrowAction)
			ThrowAction->SetOwner(Cast<ABaseCharacter>(GetOwner()), this);
		if (!Actions->ThrowMontages.IsEmpty())
		{
			for (auto action : Actions->ThrowMontages)
			{
				ThrowAction->Montages.Add(action);
			}
		}
	}
	if (Actions->SpawnAction)
	{
		if(!SpawnAction)
			SpawnAction = NewObject<UBaseAction>(this, Actions->SpawnAction);
		if (SpawnAction)
			SpawnAction->SetOwner(Cast<ABaseCharacter>(GetOwner()), this);
		if (!Actions->SpawnMontages.IsEmpty())
		{
			for (auto action : Actions->SpawnMontages)
			{
				SpawnAction->Montages.Add(action);
			}
		}
	}
}

void ABaseTool::SetDatas()
{
	ToolName = Data->ToolName;
	HandleSocketName = Data->HandleSocketName;
	ToolType = Data->ToolType;
	Damage = Data->Damage;
	DamageToTree = Data->DamageToTree;
	DamageToRock = Data->DamageToRock;
	Weight = Data->Weight;
	Durability = Data->Durability;
	MaxDurability = Data->MaxDurability;
	texture = Data->texture;
	SoundCue = Data->SoundCue;
	if (Data->RequiredItems.Num() > 0)
		RequiredItems = Data->RequiredItems;
	if (Data->RequiredCounts.Num() > 0)
		RequiredCounts = Data->RequiredCounts;
}

void ABaseTool::InterAction()
{
	BaseWidget->SetVisibility(ESlateVisibility::Hidden);

	if (!OwnerHero) return;
	
	if (OwnerHero->GetToolComponent()->IsEmptySlot() != EToolSlot::E_None)	// 슬롯이 비어있을 경우
	{
		if (OwnerHero->GetToolComponent()->GetCurrentSlot() == OwnerHero->GetToolComponent()->IsEmptySlot())	// 현재 빈 손일 경우
		{
			OwnerHero->GetToolComponent()->AddTool(OwnerHero->GetToolComponent()->IsEmptySlot(), this);
			OwnerHero->GetToolComponent()->EquipTool(OwnerHero->GetToolComponent()->GetCurrentSlot());
		}
		else
		{
			OwnerHero->GetToolComponent()->AddTool(OwnerHero->GetToolComponent()->IsEmptySlot(), this);
			SetActorHiddenInGame(true);
			SetActorEnableCollision(false);
		}
	}
	else
	{
		OwnerHero->GetInventoryComponent()->AddItems(this);
	}
	
}

void ABaseTool::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (!GetOwner()) return;	// 장착된 무기가 아닐 경우 return;
	
	FVector OverlapPoint;

	if (OtherActor && OtherActor != this && OtherActor != GetOwner())
	{
		TArray<UPrimitiveComponent*> OverlappingComponents;
		OtherActor->GetOverlappingComponents(OverlappingComponents);

		// 오버랩 컴포넌트가 있는지 확인하고 오버랩된 지점을 가져옵니다.
		for (UPrimitiveComponent* Component : OverlappingComponents)
		{
			//FVector OverlapPoint;

			// 오버랩 지점을 가져옵니다.
			Component->GetClosestPointOnCollision(GetActorLocation(), OverlapPoint);
		}
	}

	if (ABaseCharacter* DCharacter = Cast<ABaseCharacter>(OtherActor))
	{
		if (Cast<ABaseCharacter>(GetOwner()))
		{
			OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
		}
		if (OwnerCharacter)
		{
			OwnerCharacter->OnApplyDamage(DCharacter, this, 0.f);
			UE_LOG(ToolLog, Log, TEXT("Attacked : %s"), *OtherActor->GetName());
		}
		else
		{
			UE_LOG(ToolLog, Warning, TEXT("ToolOverlap - > No OwnerCharacter"));

		}
	}
	if (ABaseResource* resource = Cast<ABaseResource>(OtherActor))			
	{
		if (OwnerCharacter)
		{
			OwnerCharacter->OnApplyDamage(resource, this, 0.f);

			UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
			(
				this,
				resource->GetGather(),
				OverlapPoint
			);
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), resource->GetSound(), OverlapPoint);
		}
	}
	
}

void ABaseTool::NotifyActorEndOverlap(AActor* OtherActor)
{	
	Super::NotifyActorEndOverlap(OtherActor);
}
