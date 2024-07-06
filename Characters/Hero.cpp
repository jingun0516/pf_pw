#include "Characters/Hero.h"

#include "BlueprintEditor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Helper.h"
#include "Camera/CameraComponent.h"
#include "Logging/LogMacros.h"
#include "Misc/OutputDeviceNull.h"
#include "Tools/BaseTool.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ToolComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InventoryComponent.h"
#include "Components/BuildingComponent.h"
#include "Components/StatusComponent.h"
#include "Components/UserStatusComponent.h"

#include "Building/DA_ToBuildDataAsset.h"
#include "Input/InputDataAsset.h"
#include "Blueprint/UserWidget.h"

#include "Widgets/Menu/MenuWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/InventoryWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/MainStatusWidget.h"
#include "Widgets/Menu/MenuContents/InventoryWidget/Status/StatusItemSlotWidget.h"
#include "Widgets/BaseStatus/BaseStatusWidget.h"

#include "Widgets/Building/ToBuild/ToBuildWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Monsters/BaseMonster.h"
#include "AI/BaseAI.h"

DEFINE_LOG_CATEGORY(HeroLog);

AHero::AHero()
{
	PrimaryActorTick.bCanEverTick = true;
	bUseControllerRotationYaw = true;

	CreateCamera();

	//GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
	//	(L"/Game/Template/Mannequins/Meshes/SKM_Quinn"));
	
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Meshes/Hero/Hero_FullBody")); 
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	InputData = Helper::GetAsset<UInputDataAsset>(L"/Game/Characters/Hero/Input/DA_Input");
	
	MenuClass = Helper::GetClass<UMenuWidget>(L"/Game/Widgets/MenuWidget/WB_Menu");
	ToBuildClass = Helper::GetClass<UToBuildWidget>(L"/Game/Widgets/BuildingWidget/ToBuild/WB_ToBuild");
	BaseStatusClass = Helper::GetClass<UBaseStatusWidget>(L"/Game/Widgets/BaseStatusWidget/WB_BaseStatusWidget");
	UserStatusComponent = Helper::CreateActorComponent<UUserStatusComponent>(this, "UserStatus Component");

	Head = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, L"Head", GetMesh());
	UpperBody = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, L"UpperBody", GetMesh());
	LowerBody = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, L"LowerBody", GetMesh());
	Hand = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, L"Hand", GetMesh());
	Shoes = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, L"Shoes", GetMesh());
	
	Head->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Meshes/Hero/Hero_Head1"));

	Head->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));
	UpperBody->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));
	LowerBody->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));
	Hand->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));
	Shoes->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Animations/ABP_Default1"));

	Head->SetLeaderPoseComponent(GetMesh());
	UpperBody->SetLeaderPoseComponent(GetMesh());
	LowerBody->SetLeaderPoseComponent(GetMesh());
	Hand->SetLeaderPoseComponent(GetMesh());
	Shoes->SetLeaderPoseComponent(GetMesh());

	SetInfoWithData(InputData);
	SetCharacterMovement();
}

void AHero::BeginPlay()
{
	Super::BeginPlay();
	SetInfoWithData(InputData);
	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController != nullptr)
	{
		UEnhancedInputLocalPlayerSubsystem* SubSystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>
			(PlayerController->GetLocalPlayer());

		if (SubSystem != nullptr)
			SubSystem->AddMappingContext(KeyMappingContext, 0);
	}
	if (MenuClass)
	{
		MenuWidget = CreateWidget<UMenuWidget>(GetWorld(), MenuClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
			MenuWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (BaseStatusClass)
	{
		BaseStatusWidget = Cast<UBaseStatusWidget>(CreateWidget(GetWorld(), BaseStatusClass));

		if (BaseStatusWidget)
		{
			BaseStatusWidget->AddToViewport();
			BaseStatusWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		}
	}

	if (ToBuildClass)
	{
		ToBuildWidget = CreateWidget<UToBuildWidget>(GetWorld(), ToBuildClass);
		if (ToBuildWidget)
		{
			ToBuildWidget->AddToViewport();
			ToBuildWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	
}

void AHero::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);
}

void AHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent =
		Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent != nullptr)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AHero::Move);						// Triggered: Pressed 

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AHero::Look);

		MAPPING_CLICK(EnhancedInputComponent, MainAction, AHero::DoMainAction, AHero::EndMainAction);
		MAPPING_CLICK(EnhancedInputComponent, SubAction, AHero::DoSubAction, AHero::EndSubAction);
		MAPPING_TRIGGERED(EnhancedInputComponent, ReloadAction, AHero::DoReloadAction);		// 누를 때
		MAPPING_TRIGGERED(EnhancedInputComponent, InterAction, AHero::DoInterAction);

		MAPPING_TRIGGERED(EnhancedInputComponent, ThrowAction, AHero::DoThrowAction);		// 누를 때
		MAPPING_TRIGGERED(EnhancedInputComponent, SpawnAction, AHero::DoSpawnAction);

		MAPPING_TRIGGERED(EnhancedInputComponent, FirstSelect, AHero::DoFirstSelect);
		MAPPING_TRIGGERED(EnhancedInputComponent, SecondSelect, AHero::DoSecondSelect);
		MAPPING_TRIGGERED(EnhancedInputComponent, ThirdSelect, AHero::DoThirdSelect);
		MAPPING_TRIGGERED(EnhancedInputComponent, ForthSelect, AHero::DoForthSelect);

		MAPPING_TRIGGERED(EnhancedInputComponent, PocketmonNextSlot, AHero::DoPocketmonNextSlot);
		MAPPING_TRIGGERED(EnhancedInputComponent, PocketmonPrevSlot, AHero::DoPocketmonPrevSlot);
	}
}

void AHero::SetCharacterMovement()
{
	Super::SetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = false;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 600.0f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}

void AHero::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);

		const FVector FwdDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(FwdDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AHero::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(LookAxisVector.Y);
		AddControllerYawInput(LookAxisVector.X);
	}
}

void AHero::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (ABaseItem* item = Cast<ABaseItem>(OtherActor))
	{
		if (!item->GetOwner())
		{
			if (item->BaseWidget)
				item->BaseWidget->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else if (ABaseBuilding* building = Cast<ABaseBuilding>(OtherActor))
	{
		if (building->BaseInteractionWidget)
			building->BaseInteractionWidget->SetVisibility(ESlateVisibility::Visible);
		
	}
}

void AHero::NotifyActorEndOverlap(AActor* OtherActor)
{
	if (ABaseItem* item = Cast<ABaseItem>(OtherActor))
	{
		if (!item->GetOwner())
		{
			if (item->BaseWidget)
				item->BaseWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	else if (ABaseBuilding* building = Cast<ABaseBuilding>(OtherActor))
	{
		if (building->BaseInteractionWidget)
			building->BaseInteractionWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

float AHero::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (ABaseMonster* monster = Cast<ABaseMonster>(DamageCauser->GetOwner()))
	{
		if (!(monster->GetIsWild())) return 0.f;		// 야생의 몬스터가 아닐 경우 플레이어 데미지 X
		
		if (ABaseAI* aiMonster = Cast<ABaseAI>(monster))
		{
			if (!(aiMonster->GetCanAttack())) return 0.f;	// 공격 불가 상태일 시 데미지 X
		}
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AHero::CreateCamera()
{
	CameraArm = CreateDefaultSubobject<USpringArmComponent>("Camera Arm");
	CameraArm->SetupAttachment(RootComponent);

	CameraArm->TargetArmLength = 400.0f;
	CameraArm->bUsePawnControlRotation = true;

	Camera = Helper::CreateSceneComponent<UCameraComponent>(this, "Camera", CameraArm);
	Camera->bUsePawnControlRotation = false;
}

void AHero::SetInfoWithData(UInputDataAsset* inData)
{
	if (inData)
	{
		JumpAction = inData->JumpAction;
		MoveAction= inData->MoveAction;
		LookAction= inData->LookAction;
		MainAction= inData->MainAction;
		SubAction=inData->SubAction; 
		ReloadAction= inData->ReloadAction;
		ThrowAction=inData->ThrowAction;
		SpawnAction=inData->SpawnAction;
		InterAction=inData->InterAction;
		FirstSelect=inData->FirstSelect;
		SecondSelect= inData->SecondSelect;
		ThirdSelect=inData->ThirdSelect;
		ForthSelect=inData->ForthSelect;
		PocketmonNextSlot=inData->PocketmonNextSlot;
		PocketmonPrevSlot=inData->PocketmonPrevSlot;
	}
	else
	{
		UE_LOG(HeroLog, Warning, TEXT("No Input Data!! Check Data!!"));
	}
}

#pragma region Actions
void AHero::DoReloadAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoReloadAction);
}

void AHero::DoAvoidAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoAvoidAction);
}

void AHero::EndAvoidAction()
{
	MULTICAST_DELEGATE_BROADCAST(DEndAvoidAction);
}
void AHero::DoInterAction()
{
	TArray<AActor*> OverlappingActors;
	// 현재 액터와 겹치는 모든 액터를 가져옴
	this->GetOverlappingActors(OverlappingActors);

	if (OverlappingActors.Num() <= 0) return;

	for (auto actor : OverlappingActors)
	{
		if (ABaseItem* item = Cast<ABaseItem>(actor))
		{
			if (ABaseTool* tool = Cast<ABaseTool>(item))
			{
				GetToolComponent()->ToolInteraction(tool);
				break;
			}
			else
			{
				GetInventoryComponent()->AddItems(item);
				break;
			}
		}
		else if (ABaseBuilding* building = Cast<ABaseBuilding>(actor))
		{
			GetBuildingComponent()->BulidingInteraction(building);
			break;
		}
	}

	UE_LOG(LogTemp, Log, TEXT("Overlapping Actor : %s "), *OverlappingActors[0]->GetName());
}
void AHero::DoSpawnAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoSpawnAction);
}
void AHero::DoThrowAction()
{
	MULTICAST_DELEGATE_BROADCAST(DDoThrowAction);
}
void AHero::DoFirstSelect()
{
	MULTICAST_DELEGATE_BROADCAST(DDoFirstSelect);
}
void AHero::DoSecondSelect()
{
	MULTICAST_DELEGATE_BROADCAST(DDoSecondSelect);
}
void AHero::DoThirdSelect()
{
	MULTICAST_DELEGATE_BROADCAST(DDoThirdSelect);
}
void AHero::DoForthSelect()
{
	MULTICAST_DELEGATE_BROADCAST(DDoForthSelect);
}
void AHero::DoPocketmonNextSlot()
{
	MULTICAST_DELEGATE_BROADCAST(DPocketmonNextSlot);
}
void AHero::DoPocketmonPrevSlot()
{
	MULTICAST_DELEGATE_BROADCAST(DPocketmonPrevSlot);
}
#pragma endregion

void AHero::ToolSlotChanged(ABaseTool* Tool1, ABaseTool* Tool2, ABaseTool* Tool3, ABaseTool* Tool4)
{
	if (MenuWidget)
	{
		if(Tool1->GetTexture())
			MenuWidget->GetInventoryWidget()->GetMainStatusWidget()->GetTool1()->SetToolImage(Tool1->GetTexture());
		if (Tool2->GetTexture())
			MenuWidget->GetInventoryWidget()->GetMainStatusWidget()->GetTool2()->SetToolImage(Tool2->GetTexture());
		if (Tool3->GetTexture())
			MenuWidget->GetInventoryWidget()->GetMainStatusWidget()->GetTool3()->SetToolImage(Tool3->GetTexture());
		if (Tool4->GetTexture())
			MenuWidget->GetInventoryWidget()->GetMainStatusWidget()->GetTool4()->SetToolImage(Tool4->GetTexture());
	}
}

void AHero::SetHPBar(float HP, float MaxHP)
{
	if (BaseStatusWidget)
		BaseStatusWidget->SetHPBar(GetStatusComponent()->GetHP(), GetStatusComponent()->GetMaxHP());

	UE_LOG(HeroLog, Log, TEXT("CurHP: %f / MaxHP: %f"), GetStatusComponent()->GetHP(), GetStatusComponent()->GetMaxHP());
}

void AHero::SetExpBar(int EXP, int NextEXP)
{
	if(BaseStatusWidget)
		BaseStatusWidget->SetEXPBar(GetStatusComponent()->GetPrevEXP(), GetStatusComponent()->GetNextEXP());
}

void AHero::SetLevelWidget(int LV)
{
	if (BaseStatusWidget)
		BaseStatusWidget->SetCharacterLV(GetStatusComponent()->GetLevel());
}

void AHero::SetBaseStatusWidgetVisible(bool bIsVisible)
{
	if (BaseStatusWidget)
	{
		if (bIsVisible)
			BaseStatusWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
		else
		{
			BaseStatusWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void AHero::HideAllWidget()
{
	if (MenuWidget)
	{
		MenuWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (ToBuildWidget)
	{
		ToBuildWidget->SetVisibility(ESlateVisibility::Hidden);
	}
	if (BaseStatusWidget)
	{
		BaseStatusWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void AHero::OnPocketmonSlotChanged()
{
	if (UBaseStatusWidget* baseWidget = Cast<UBaseStatusWidget>(BaseStatusWidget))
	{
		baseWidget->SetPocketmon();
		UE_LOG(HeroLog, Log, TEXT("baseWidget"));
	}
	else
	{
		UE_LOG(HeroLog, Log, TEXT("No baseWidget"));

	}
}
