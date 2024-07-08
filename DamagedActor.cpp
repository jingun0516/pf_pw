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

	// ���� ���� �ؽ�Ʈ ���� �������� (��: TextBlock ����)
	UTextBlock* TextBlockWidget = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("TextBlock")));

	if (!TextBlockWidget) return;
	
	// �ؽ�Ʈ ����
	TextBlockWidget->SetText(FText::Format(FText::FromString(TEXT("{0}")), FText::AsNumber(Damage)));
}
