#include "DamagedActor.h"
#include "Components/WidgetComponent.h"
#include "Helper.h"
#include <Components/TextBlock.h>

ADamagedActor::ADamagedActor()
{
	DamageWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageWidget"));
	DamageWidget->SetWidgetClass(Helper::GetClass<UUserWidget>(L"/Game/Widgets/WB_DamageWidget"));
	DamageWidget->SetWidgetSpace(EWidgetSpace::Screen);
}

void ADamagedActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(1.5f);
}

void ADamagedActor::SetDamage(float Damage)
{
	if (!DamageWidget) return;

	UUserWidget* Widget = DamageWidget->GetUserWidgetObject();
	if (!Widget) return;

	// 위젯 내의 텍스트 위젯 가져오기 (예: TextBlock 위젯)
	UTextBlock* TextBlockWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock")));

	if (!TextBlockWidget) return;
	
	// 텍스트 설정
	TextBlockWidget->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(Damage)));
}
