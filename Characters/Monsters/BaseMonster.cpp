#include "Characters/Monsters/BaseMonster.h"
#include "Helper.h"
#include "Components/Pocketmon/PocketmonEnum.h"
#include "Components/StatusComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Actions/ActionDataAsset.h"
#include "MonsterStatusDataAsset.h"
#include "Logging/LogMacros.h"
#include "Widgets/BaseStatus/MonsterStatusWidget.h"
#include "Components/WidgetComponent.h"


DEFINE_LOG_CATEGORY(MonsterLog);

ABaseMonster::ABaseMonster()
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	//GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//GetMesh()->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	MonsterStatusWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Monster Widget"));

	MonsterStatusClass = Helper::GetClass<UUserWidget>(L"/Game/Widgets/BaseStatusWidget/WB_MonsterStatusWidget");

	// 원하는 UI 위젯을 설정합니다.
	MonsterStatusWidgetComp->SetWidgetClass(MonsterStatusClass);

	// 3D 공간에서 UI 위치를 설정합니다.
	MonsterStatusWidgetComp->SetRelativeLocation(FVector(0, 0, GetActorScale3D().Z + 50.f));
	MonsterStatusWidgetComp->SetRelativeRotation(FRotator(0, 0, -90));
	MonsterStatusWidgetComp->SetRelativeScale3D(FVector(1, 1, 1));

	// 이 컴포넌트를 부착할 액터를 찾거나 설정합니다.
	MonsterStatusWidgetComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
	MonsterStatusWidgetComp->SetDrawSize(FVector2D(500, 150));
	MonsterStatusWidgetComp->SetWidgetSpace(EWidgetSpace::World);
	MonsterStatusWidgetComp->bAutoActivate = true;
}

void ABaseMonster::SetMonsterStatus()
{
	if (MonsterStatusWidget)
	{
		MonsterStatusWidget->SetMonsterName(GetMonName());
		MonsterStatusWidget->SetHP(this);
	}
}

void ABaseMonster::SetTeamMonster()
{
	if (MonsterStatusWidget)
	{
		MonsterStatusWidget->SetTeamMonsterName();
	}
}

void ABaseMonster::BeginPlay()
{
	Super::BeginPlay();
	
	if (stats)
		SetInfos(stats);
	else
		UE_LOG(MonsterLog, Warning, TEXT("Thiere is No MonsterStats!!!"));

	if(MonsterStatusWidgetComp)
		MonsterStatusWidget = Cast<UMonsterStatusWidget>(MonsterStatusWidgetComp->GetUserWidgetObject());

	SetMonsterStatus();
}

void ABaseMonster::SetCharacterMovement()
{
	Super::SetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = false;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = MaxSpeed;
	Comp->MaxAcceleration = 500.f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}

void ABaseMonster::SetInfos(UMonsterStatusDataAsset* InStats)
{
	Name = InStats->Name;
	GetStatusComponent()->SetHP(InStats->MaxHP);
	GetStatusComponent()->SetMaxHP(InStats->MaxHP);
	GetStatusComponent()->SetDamage(InStats->Damage);
	GetStatusComponent()->SetArmor(InStats->Armor);
	GetStatusComponent()->SetLV(InStats->LV);
	GetStatusComponent()->SetEXP(InStats->EXP);
	texture = InStats->texture;
	WalkSpeed = InStats->WalkSpeed;
	MaxSpeed = InStats->MaxSpeed;
	if (InStats->HitMontage)
		HitMontage = InStats->HitMontage;
	if (InStats->DeadMontage)
		DeadMontage = InStats->DeadMontage;
	SetCatchPercent();
}

void ABaseMonster::SetCatchPercent()
{
	switch (rating)
	{
	case EPocketmonRating::E_Normal:
		CatchPercent = 0.7f;
		break;
	case EPocketmonRating::E_Rare:
		CatchPercent = 0.5f;
		break;
	case EPocketmonRating::E_Unique:
		CatchPercent = 0.4f;
		break;
	case EPocketmonRating::E_Legendary:
		CatchPercent = 0.1f;
		break;
	}
}
