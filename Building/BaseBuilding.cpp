#include "BaseBuilding.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/State/StateComponent.h"
#include "Components/State/StateEnum.h"
#include "Characters/Hero.h"
#include "Characters/BaseCharacter.h"
#include "Building/BuildingStateEnum.h"
#include "Helper.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" 
#include "Logging/LogMacros.h"
#include "Widgets/Building/BaseBuildingWidget.h"
#include "Widgets/Building/WorkTimeActor.h"
#include "Widgets/Building/BuildingClickedWidget.h"
#include "Widgets/YesNoWidget.h"
#include "Building/DA_ToBuildDataAsset.h"


DEFINE_LOG_CATEGORY(BuildingLog);

ABaseBuilding::ABaseBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = Helper::CreateSceneComponent<USceneComponent>(this, "RootSceneComponent");

	mesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "Static Mesh", RootComponent);
	col = Helper::CreateSceneComponent<UBoxComponent>(this, "Box Collision", mesh);

	OwnerCharacter = Cast<ABaseCharacter>(GetOwner());
	OwnerHero = Cast<AHero>(GetOwner());

	WidgetClass = Helper::GetClass<UUserWidget>(TEXT("/Game/Widgets/BuildingWidget/WB_BaseInteraction"));
	YesNoWidgetClass = Helper::GetClass<UYesNoWidget>(TEXT("/Game/Widgets/WB_YesOrNo"));

	SetBuildingState(EBuildingState::E_Idle);

	blueMaterial = Helper::GetAsset<UMaterialInterface>(TEXT("/Game/Materials/M_JustBlue"));
	redMaterial = Helper::GetAsset<UMaterialInterface>(TEXT("/Game/Materials/M_JustRed"));
	greenMaterial = Helper::GetAsset<UMaterialInterface>(TEXT("/Game/Materials/M_JustGreen"));

	BuildingClickedWidgetClass = Helper::GetClass<UBuildingClickedWidget>(TEXT("/Game/Widgets/BuildingWidget/WB_BuildingClicked"));
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();

	TArray<UStaticMeshComponent*> MeshComponents;
	this->GetComponents<UStaticMeshComponent>(MeshComponents);

	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent)
		{
			TArray<UMaterialInterface*> Materials = MeshComponent->GetMaterials();
			MArray = Materials;
		}
	}

	if (!OwnerHero)
	{
		OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	}

	if (WidgetClass)
	{
		BaseInteractionWidget = CreateWidget(GetWorld(), WidgetClass);

		if (BaseInteractionWidget)
		{
			BaseInteractionWidget->AddToViewport();
			BaseInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (InteractioningWidgetClass)
	{
		InteractioningWidget = Cast<UBaseBuildingWidget>(CreateWidget(GetWorld(), InteractioningWidgetClass));

		if (InteractioningWidget)
		{
			InteractioningWidget->AddToViewport();
			InteractioningWidget->SetVisibility(ESlateVisibility::Hidden);
			InteractioningWidget->SetOwnerBuilding(this);
		}
	}

	if (YesNoWidgetClass)
	{
		YesNoWidget = Cast<UYesNoWidget>(CreateWidget(GetWorld(), YesNoWidgetClass));

		if (YesNoWidget)
		{
			YesNoWidget->AddToViewport();
			YesNoWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (BuildingClickedWidgetClass)
	{
		BuildingClickedWidget = Cast<UBuildingClickedWidget>(CreateWidget(GetWorld(), BuildingClickedWidgetClass));

		if (BuildingClickedWidget)
		{
			BuildingClickedWidget->AddToViewport();
			BuildingClickedWidget->SetVisibility(ESlateVisibility::Hidden);
		}
		UE_LOG(LogTemp, Log, TEXT("BuildingClickedWidget Success"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("BuildingClickedWidget Fail"));

	}
	DOnBuildingWorkState.AddUFunction(this, "StartWork");

	SetDatas();
}

void ABaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetBuildingState() == EBuildingState::E_Work)
	{
		if (GetWorkersNum() >= 1)
		{
			CurrentWorkTime += DeltaTime * GetWorkersNum();
			float LeftWorkTime = (GoalWorkTime / (float)GetWorkersNum()) - CurrentWorkTime;
			if (WorkTimeActor)
			{
				WorkTimeActor->SetLeftTime(LeftWorkTime);
			}
			
			if (LeftWorkTime <= 0.f)		// 작업 완료시
			{
				JobsDone();
			}
		}
	}
	else if (GetBuildingState() == EBuildingState::E_Build)
	{
		if (GetWorkersNum() >= 1)
		{
			CurrentWorkTime += DeltaTime * GetWorkersNum();
			float LeftWorkTime = (GoalWorkTime / (float)GetWorkersNum()) - CurrentWorkTime;
			if (WorkTimeActor)
			{
				WorkTimeActor->SetLeftTime(LeftWorkTime);
			}

			if (LeftWorkTime <= 0.f)		// 작업 완료시
			{
				BuildDone();
			}
		}
	}

}

void ABaseBuilding::InterAction()
{
	if (BaseInteractionWidget)
		BaseInteractionWidget->SetVisibility(ESlateVisibility::Hidden);

	if (GetBuildingState() == EBuildingState::E_Idle)
	{
		if (InteractioningWidget)
		{
			InteractioningWidget->SetVisibility(ESlateVisibility::Visible);
			APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
			if (PlayerController)
			{
				TSharedPtr<SWidget> WidgetPtr = InteractioningWidget->TakeWidget(); // UUserWidget을 SWidget으로 변환합니다.

				FInputModeUIOnly InputMode;

				if(OwnerHero)
					OwnerHero->HideAllWidget();
				InputMode.SetWidgetToFocus(WidgetPtr); // 원하는 위젯 지정
				PlayerController->SetInputMode(InputMode);
				PlayerController->bShowMouseCursor = true; // 마우스 커서를 보이게 설정할 수도 있습니다.
			}
		}
	}
	else if (GetBuildingState() == EBuildingState::E_Build)
	{
		if (OwnerHero)
		{
			AddWorkers(OwnerHero);
			UE_LOG(BuildingLog, Log, TEXT("Building InterAction Success"));
		}
	}
}

void ABaseBuilding::SetMovable()
{
	if (RootComponent)
	{
		RootComponent->SetMobility(EComponentMobility::Movable);
		for (auto objects : RootComponent->GetAttachChildren())
		{
			objects->SetMobility(EComponentMobility::Movable);
		}
	}
}

void ABaseBuilding::SetBuildingColor(EBuildingColor color)
{
	TArray<UStaticMeshComponent*> MeshComponents;
	this->GetComponents<UStaticMeshComponent>(MeshComponents);

	UMaterialInterface* NewMaterial = nullptr;

	switch (color)
	{
	case EBuildingColor::E_Normal:
		break;
	case EBuildingColor::E_Blue:
		NewMaterial = blueMaterial;
		break;
	case EBuildingColor::E_Red:
		NewMaterial = redMaterial;
		break;
	case EBuildingColor::E_Green:
		NewMaterial = greenMaterial;
		break;
	}

	for (UStaticMeshComponent* MeshComponent : MeshComponents)
	{
		if (MeshComponent)
		{
			TArray<UMaterialInterface*> Materials = MeshComponent->GetMaterials();

			for (int32 i = 0; i < Materials.Num(); ++i)
			{
				MeshComponent->SetMaterial(i, NewMaterial);
			}
		}
	}
}

void ABaseBuilding::SetDatas()
{
	if (BuildData)
	{
		Durability = BuildData->MaxDurability;
		MaxDurability = BuildData->MaxDurability;
		CurrentWorkTime = 0.f;
		GoalWorkTime = BuildData->GoalWorkTime;
		texture = BuildData->texture;
		if (BuildData->RequiredItems.Num() > 0)
			RequiredItems = BuildData->RequiredItems;
		if (BuildData->RequiredCounts.Num() > 0)
			RequiredCounts = BuildData->RequiredCounts;
	}
}

void ABaseBuilding::SetBuildingState(EBuildingState state)
{
	BuildingState = state;
	if (GetBuildingState() == EBuildingState::E_Work)
	{
		if (DOnBuildingWorkState.IsBound()) 
			DOnBuildingWorkState.Broadcast();
	}
}

FVector ABaseBuilding::GetScaledCol()
{
	return col->GetScaledBoxExtent(); 
}

void ABaseBuilding::JobsDone()
{
	for (auto& worker : Workers)
	{
		worker.Value = nullptr;
	}
	SetBuildingState(EBuildingState::E_WorkDone);
	if (WorkTimeActor)
	{
		WorkTimeActor->SetWorkDone();
	}
	CurrentWorkTime = 0.f;
}

void ABaseBuilding::BuildDone()
{
	for (auto& worker : Workers)
	{
		worker.Value = nullptr;
	}
	SetBuildingState(EBuildingState::E_Idle);
	if (WorkTimeActor)
	{
		WorkTimeActor->SetWorkDone();
	}
	CurrentWorkTime = 0.f; 
	OwnerHero->GetStateComponent()->SetState(E_StateType::E_Idle);
	OwnerHero->GetBuildingComponent()->SpawnBuildingSuccess();
}

void ABaseBuilding::AddWorkers(ABaseCharacter* worker)
{
	if (!worker) return;

	if (GetEmptyWorkerSlot() != EWorkerSlot::E_None)
	{
		Workers.Add(GetEmptyWorkerSlot(), worker);
	}
	else return;
}

int ABaseBuilding::GetWorkersNum()
{
	int worknum = 0;
	for (auto& worker : Workers)
	{
		if (worker.Value != nullptr)
			worknum++;
	}
	return worknum;
}

void ABaseBuilding::StartWork()
{
	UE_LOG(BuildingLog, Log, TEXT("Start WorkWait!"));
	WorkTimeActor = GetWorld()->SpawnActor<AWorkTimeActor>(GetActorLocation(), FRotator());
	WorkTimeActor->SetLeftTime(10.f);
}

EWorkerSlot ABaseBuilding::GetEmptyWorkerSlot()
{
	if (!Workers.FindRef(EWorkerSlot::E_First)) return EWorkerSlot::E_First;
	if (!Workers.FindRef(EWorkerSlot::E_Second)) return EWorkerSlot::E_Second;
	if (!Workers.FindRef(EWorkerSlot::E_Third)) return EWorkerSlot::E_Third;
	if (!Workers.FindRef(EWorkerSlot::E_Forth)) return EWorkerSlot::E_Forth;
	if (!Workers.FindRef(EWorkerSlot::E_Fifth)) return EWorkerSlot::E_Fifth;
	return EWorkerSlot::E_None;
}
