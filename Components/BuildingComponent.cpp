#include "Components/BuildingComponent.h"
#include "Components/ToolComponent.h"
#include "Components/InventoryComponent.h"
#include "Building/BaseBuilding.h"
#include "Characters/BaseCharacter.h"
#include "Characters/Hero.h"
#include "Building/Building_CraftBox.h"
#include <Kismet/GameplayStatics.h>
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Widgets/Building/WorkTimeActor.h"
#include "Building/BuildingStateEnum.h"
#include "Widgets/Building/BuildingClickedWidget.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	if (!OwnerCharacter) return;

	OwnerHero = Cast<AHero>(GetOwner());
	if (!OwnerHero) return;
	
	FActorSpawnParameters SpawnParameter;
	SpawnParameter.Owner = GetOwner();
}


void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!OwnerHero) return;
	if (!(OwnerHero->GetStateComponent())) return;

	if (OwnerHero->GetStateComponent()->GetState() == E_StateType::E_Build)
	{
		if (tempBuilding)
		{
			if (tempBuilding->GetBuildingState() == EBuildingState::E_Idle)
			{
				float MaxV = tempBuilding->GetScaledCol().X;
				if (MaxV < tempBuilding->GetScaledCol().Y)
					MaxV = tempBuilding->GetScaledCol().Y;
				
				float locationZ = OwnerHero->GetActorLocation().Z;
				FVector tempPos;
				tempPos = OwnerHero->GetActorLocation() + OwnerHero->GetActorForwardVector() * (MaxV + 500.f) - locationZ;

				tempBuilding->SetActorLocation(tempPos);
				if (CanSpawnBuilding())
					tempBuilding->SetBuildingColor(EBuildingColor::E_Blue);
				else
					tempBuilding->SetBuildingColor(EBuildingColor::E_Red);
			}
		}
	}
}

void UBuildingComponent::BulidingInteraction(ABaseBuilding* building)
{
	building->InterAction();
}

bool UBuildingComponent::CanSpawnBuilding()
{
	if (!tempBuilding || !OwnerHero) return true;

	TArray<AActor*> OverlappingActors;
	tempBuilding->GetOverlappingActors(OverlappingActors);
	for (auto actors : OverlappingActors)
	{
		if (actors != tempBuilding || actors != OwnerHero)
		{
			return false;
		}
	}

	return true;
}

void UBuildingComponent::SpawnBuilding(TSubclassOf<ABaseBuilding> ToBuild)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 충돌에 관계없이 스폰
	BuildingToMake = ToBuild;
	tempBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingToMake, SpawnParams);
	if (tempBuilding)
	{
		tempBuilding->SetActorEnableCollision(true);
		tempBuilding->SetMovable();
	}
}

void UBuildingComponent::SpawnBuildingStart()
{
	if (!tempBuilding) return;
	if (!BuildingToMake) return;

	tempBuilding->SetBuildingState(EBuildingState::E_Build);
	tempBuilding->SetBuildingColor(EBuildingColor::E_Green);

	AWorkTimeActor* tempWorkTimeActor = GetWorld()->SpawnActor<AWorkTimeActor>(tempBuilding->GetActorLocation(), FRotator());
	tempWorkTimeActor->SetLeftTime(tempBuilding->GetGoalWorkTime());
	if (tempBuilding->GetTexture())
		tempWorkTimeActor->SetImage(tempBuilding->GetTexture());
	tempBuilding->SetWorkTimeActor(tempWorkTimeActor);

	if (tempBuilding)
	{
		tempBuilding->SetActorEnableCollision(true);
		UE_LOG(LogTemp, Log, TEXT("%s BuildingStart"), *tempBuilding->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("new Building Spawn Fail"));
	}
	
	for (int i = 0; i < tempBuilding->GetRequiredItems().Num(); i++)
	{
		OwnerHero->GetInventoryComponent()->SubItems(tempBuilding->GetRequiredItems()[i], tempBuilding->GetRequiredCounts()[i]);
	}
}

void UBuildingComponent::SpawnBuildingSuccess()
{
	FVector BuildLocation = tempBuilding->GetActorLocation();
	FRotator BuildRotator = tempBuilding->GetActorRotation();
	tempBuilding->Destroy();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = OwnerHero;
	ABaseBuilding* newBuilding = GetWorld()->SpawnActor<ABaseBuilding>(BuildingToMake, BuildLocation, BuildRotator, SpawnParams);
	newBuilding->SetBuildingState(EBuildingState::E_Idle);
}

void UBuildingComponent::BuildingCancel()
{
	OwnerHero->GetStateComponent()->SetState(E_StateType::E_Idle);
	tempBuilding->Destroy();
}
