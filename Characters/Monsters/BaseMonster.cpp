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
			// 원하는 UI 위젯을 설정합니다.
			MonsterStatusWidgetComp->SetWidgetClass(MonsterStatusClass);
			UE_LOG(LogTemp, Error, TEXT("Succeed to load MonsterStatusClass!"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to load MonsterStatusClass!"));
		}
		
		MonsterStatusWidgetComp->SetupAttachment(GetMesh());

		MonsterStatusWidgetComp->SetRelativeLocation(FVector(0, 0, GetActorScale3D().Z + 300.f)); // 위치 설정
		MonsterStatusWidgetComp->SetRelativeRotation(FRotator(0, 90, 0)); // 회전 설정
		MonsterStatusWidgetComp->SetRelativeScale3D(FVector(1, 1, 1)); // 스케일 설정
		MonsterStatusWidgetComp->SetDrawSize(FVector2D(600, 200)); // 크기 설정
		MonsterStatusWidgetComp->SetWidgetSpace(EWidgetSpace::Screen); // 공간 설정
		MonsterStatusWidgetComp->bAutoActivate = true; // 자동 활성화
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
		if (Cast<AHero>(DamageCauser->GetOwner()))		// 야생의 몬스터가 아닐 경우 플레이어가 때리지 못함
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
		// 플레이어의 카메라 위치를 가져옵니다.
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && PlayerController->PlayerCameraManager)
		{
			FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
			FVector WidgetLocation = MonsterStatusWidgetComp->GetComponentLocation();

			// 카메라와 위젯 사이의 거리를 계산합니다.
			float Distance = FVector::Dist(CameraLocation, WidgetLocation);

			// 거리 기반의 스케일 팩터를 정의합니다 (필요에 따라 조정).
			float ScaleFactor = FMath::Clamp(1000.0f / Distance, 0.5f, 1.0f); // 0.5에서 1.0 사이로 스케일링

			// 위젯에 스케일을 적용합니다.
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
