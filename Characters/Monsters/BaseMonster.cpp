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
#include "Characters/Hero.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY(MonsterLog);

ABaseMonster::ABaseMonster()
{
	PrimaryActorTick.bCanEverTick = true;

	if (GetMesh())
	{
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GetMesh() returned nullptr!"));
	}

	MonsterStatusWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Monster Widget"));

	if (MonsterStatusWidgetComp)
	{
		MonsterStatusClass = Helper::GetClass<UUserWidget>(L"/Game/Widgets/BaseStatusWidget/WB_MonsterStatusWidget");

		if (MonsterStatusClass)
		{
			// ���ϴ� UI ������ �����մϴ�.
			MonsterStatusWidgetComp->SetWidgetClass(MonsterStatusClass);
			UE_LOG(LogTemp, Error, TEXT("Succeed to load MonsterStatusClass!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load MonsterStatusClass!"));
		}
		
		MonsterStatusWidgetComp->SetupAttachment(GetMesh());

		MonsterStatusWidgetComp->SetRelativeLocation(FVector(0, 0, GetActorScale3D().Z + 300.f)); // ��ġ ����
		MonsterStatusWidgetComp->SetRelativeRotation(FRotator(0, 90, 0)); // ȸ�� ����
		MonsterStatusWidgetComp->SetRelativeScale3D(FVector(1, 1, 1)); // ������ ����
		MonsterStatusWidgetComp->SetDrawSize(FVector2D(600, 200)); // ũ�� ����
		MonsterStatusWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // ���� ����
		MonsterStatusWidgetComp->bAutoActivate = true; // �ڵ� Ȱ��ȭ
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to create MonsterStatusWidgetComp!"));
	}

}

void ABaseMonster::SetMonsterStatus()
{
	if (MonsterStatusWidget)
	{
		MonsterStatusWidget->SetMonsterName(GetMonName());
		MonsterStatusWidget->SetHP(this);
		MonsterStatusWidget->SetVisibility(ESlateVisibility::HitTestInvisible);
	}
}

void ABaseMonster::SetTeamMonster()
{
	if (MonsterStatusWidget)
	{
		MonsterStatusWidget->SetTeamMonsterName();
	}
}

float ABaseMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!GetIsWild())
	{
		if (Cast<AHero>(DamageCauser->GetOwner()))		// �߻��� ���Ͱ� �ƴ� ��� �÷��̾ ������ ����
			return 0.f;
	}

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
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

void ABaseMonster::UpdateWidgetScale()
{
	if (MonsterStatusWidgetComp)
	{
		// �÷��̾��� ī�޶� ��ġ�� �����ɴϴ�.
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && PlayerController->PlayerCameraManager)
		{
			FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
			FVector WidgetLocation = MonsterStatusWidgetComp->GetComponentLocation();

			// ī�޶�� ���� ������ �Ÿ��� ����մϴ�.
			float Distance = FVector::Dist(CameraLocation, WidgetLocation);

			// �Ÿ� ����� ������ ���͸� �����մϴ� (�ʿ信 ���� ����).
			float ScaleFactor = FMath::Clamp(1000.0f / Distance, 0.5f, 1.0f); // 0.5���� 1.0 ���̷� �����ϸ�

			// ������ �������� �����մϴ�.
			MonsterStatusWidgetComp->SetWorldScale3D(FVector(ScaleFactor));
		}
	}
}

void ABaseMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerC && GetDistanceTo(PlayerC) <= 1000)
		MonsterStatusWidgetComp->SetVisibility(true);

	if (PlayerC && GetDistanceTo(PlayerC) > 1000)
		MonsterStatusWidgetComp->SetVisibility(false);
	//UpdateWidgetScale();
}
