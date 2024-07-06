#include "CatchActor.h"
#include "Components/WidgetComponent.h"
#include "Helper.h"
#include <Components/TextBlock.h>
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "CatchFailActor.h"
#include "CatchSuccedActor.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/Hero.h"
#include "Components/StatusComponent.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Logging/LogMacros.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystem.h"
#include "AI/BaseAI.h"

DEFINE_LOG_CATEGORY(CatchLog);

ACatchActor::ACatchActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CatchWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("CatchWidget"));
	CatchWidget->SetWidgetClass(Helper::GetClass<UUserWidget>(L"/Game/Widgets/PocketmonWidget/WB_CatchWidget"));
	CatchWidget->SetWidgetSpace(EWidgetSpace::Screen);
	BaseMaterial = Helper::GetAsset<UMaterialInterface>(L"/Game/Widgets/Utility/M_RoundProgressbar");

	OnDestroyed.AddDynamic(this, &ACatchActor::OnCatchDestroyed);

	effect = Helper::GetAsset<UParticleSystem>(L"/Game/Assets/AdvancedMagicFX13/Particles/P_ky_burst");
}

void ACatchActor::BeginPlay()
{
	Super::BeginPlay();
	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	SetLifeSpan(1.5f);
}

void ACatchActor::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

	if (EndPercent > CurPercent)
	{
		CurPercent += 0.01f;
		if (CurPercent >= EndPercent)
			CurPercent = EndPercent;
	}
	if (CurPercent >= 1.f) CurPercent = 1.f;

	if (CatchWidget)
	{
		UUserWidget* Widget = CatchWidget->GetUserWidgetObject();
		if (Widget)
		{
			UTextBlock* TextBlockWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock")));
			UImage* ProgressBar = Cast<UImage>(Widget->GetWidgetFromName(TEXT("ProgressBar")));

			if (MI_RoundProgressbar)
			{
				MI_RoundProgressbar->SetScalarParameterValue(L"Percent", CurPercent);
			}
			else
			{
				MI_RoundProgressbar = UMaterialInstanceDynamic::Create(BaseMaterial, nullptr);
				if (MI_RoundProgressbar)
				{
					ProgressBar->SetBrushFromMaterial(MI_RoundProgressbar);
					MI_RoundProgressbar->SetScalarParameterValue(L"Percent", CurPercent);
				}
			}

			if (TextBlockWidget)
			{
				TextBlockWidget->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(CurPercent * 100)));
			}
		}
	}
}

void ACatchActor::SetCatchInfo(float Start, float End, int num, ABaseMonster* InMonster)
{
	StartPercent = Start;
	CurPercent = Start;
	EndPercent = End;
	CurNum = num;
	monster = InMonster;
	CheckCatchFunc(EndPercent);
	UE_LOG(CatchLog, Log, TEXT("%f"), EndPercent);
}

void ACatchActor::CheckCatchFunc(float percent)
{
	float FinalPercent = percent;
	UE_LOG(CatchLog, Log, TEXT("%f"), percent);

	if (FinalPercent >= 1.f) FinalPercent = 1.f;
	if (FinalPercent <= 0.f) FinalPercent = 0.f;

	float RandomFloat = FMath::FRandRange(0.f, 1.f);
		
	if (RandomFloat <= FinalPercent)
		CheckCatch = true;
	else
		CheckCatch = false;
}

void ACatchActor::OnCatchDestroyed(AActor* DestroyedActor)
{
	ABaseAI* aimonster = Cast<ABaseAI>(monster);

	if (!CheckCatch)
	{
		GetWorld()->SpawnActor<ACatchFailActor>(GetActorLocation(), FRotator());
		if (!monster) return;
		
		monster->SetActorHiddenInGame(false);
		monster->SetActorEnableCollision(true);
		if (aimonster)
			aimonster->ActivateAIController(true);
		UParticleSystemComponent* SpawnedEmitter = UGameplayStatics::SpawnEmitterAtLocation
		(
			this,
			effect,
			GetActorLocation()
		);
	}
	else
	{
		if (CurNum == 2)	// 최종 Catch 성공
		{
			GetWorld()->SpawnActor<ACatchSuccedActor>(GetActorLocation(), FRotator());
			if (OwnerHero->GetPocketmonComponent()->IsEmptySlot() != EPocketmonSlot::E_None)
			{
				OwnerHero->GetPocketmonComponent()->AddPocketmon(OwnerHero->GetPocketmonComponent()->IsEmptySlot(), monster);
				OwnerHero->GetStatusComponent()->AddEXP(monster->GetStatusComponent()->GetEXP());
				
				monster->SetActorHiddenInGame(true);
				monster->SetActorEnableCollision(false);
				if (!aimonster) return;
				
				aimonster->SetupTeamAIController();
				aimonster->ActivateAIController(false);
			}
		}
		else
		{
			ACatchActor* catchactor = GetWorld()->SpawnActor<ACatchActor>(GetActorLocation(), FRotator());
			catchactor->SetCatchInfo(EndPercent, EndPercent * 1.2f, CurNum + 1, monster);
			if (aimonster)
				aimonster->ActivateAIController(true);
		}
	}
}
