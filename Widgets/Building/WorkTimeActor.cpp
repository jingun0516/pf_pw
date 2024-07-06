#include "Widgets/Building/WorkTimeActor.h"
#include "Components/WidgetComponent.h"
#include "Helper.h"
#include <Components/TextBlock.h>
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/Image.h"
#include "Characters/Monsters/BaseMonster.h"
#include "Characters/Hero.h"
#include "Components/StatusComponent.h"
#include "Components/Pocketmon/PocketmonComponent.h"
#include "Logging/LogMacros.h"
#include <Kismet/GameplayStatics.h>
#include "WorkTimeActor.h"

AWorkTimeActor::AWorkTimeActor()
{
	PrimaryActorTick.bCanEverTick = true;

	WorkTimeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorkTimeWidget"));
	WorkTimeWidget->SetWidgetClass(Helper::GetClass<UUserWidget>(L"/Game/Widgets/BuildingWidget/WB_WorkTime"));
	WorkTimeWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void AWorkTimeActor::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerHero = Cast<AHero>(GetWorld()->GetFirstPlayerController()->GetCharacter());
}

void AWorkTimeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWorkTimeActor::SetLeftTime(float time)
{
	if (!WorkTimeWidget) return;
	
	UUserWidget* Widget = WorkTimeWidget->GetUserWidgetObject();
	if (!Widget) return;
	
	UTextBlock* TextBlockWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("BP_LeftWorkTime")));

	if (!TextBlockWidget) return;
	
	TextBlockWidget->SetText(FText::Format(FText::FromString(TEXT("LeftWorkTime\n{0} seconds")), FText::AsNumber(time)));
}

void AWorkTimeActor::SetImage(UTexture2D* image)
{
	if (!WorkTimeWidget) return;
	
	UUserWidget* Widget = WorkTimeWidget->GetUserWidgetObject();
	if (!Widget) return;
	
	UImage* ImageWidget = Cast<UImage>(Widget->GetWidgetFromName(TEXT("BP_Image")));
	if (!ImageWidget) return;
		
	ImageWidget->SetBrushFromTexture(image);
}

void AWorkTimeActor::SetWorkDone()
{
	if (!WorkTimeWidget) return;
	
	UUserWidget* Widget = WorkTimeWidget->GetUserWidgetObject();
	if (!Widget) return;
	
	UTextBlock* TextBlockWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("BP_LeftWorkTime")));

	if (!TextBlockWidget) return;
	
	FText NewText = FText::FromString(TEXT("Jobs Done"));
	TextBlockWidget->SetText(NewText);
	
	SetLifeSpan(2.f);
}

