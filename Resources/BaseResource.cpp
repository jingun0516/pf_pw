#include "Resources/BaseResource.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Tools/BaseTool.h"
#include "DamagedActor.h"
#include "Helper.h"
#include "Logging/Logmacros.h"
#include "Particles/ParticleSystemComponent.h"
#include <Sound/SoundCue.h>
#include "Items/BaseItem.h"
#include "Math/UnrealMathUtility.h"
#include "Components/CapsuleComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include <Perception/AISense_Sight.h>

DEFINE_LOG_CATEGORY(ResourceLog);

ABaseResource::ABaseResource()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "ResourceMesh");
	col = Helper::CreateSceneComponent<UCapsuleComponent>(this, "collision", mesh);

	RootComponent = mesh;

	col->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	col->SetCollisionResponseToAllChannels(ECR_Ignore);
	col->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // AI 감지와 관련된 채널 설정

	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseResource::OnBeginOverlap);
	//StimuliSourceComponent = Helper::CreateSceneComponent<UAIPerceptionStimuliSourceComponent>(this, "StimulComp");
	StimuliSourceComponent = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("StimuliSourceComponent"));

	// 감지 유형 설정 (시각 감지)
	StimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliSourceComponent->bAutoRegister = true;
}

void ABaseResource::BeginPlay()
{
	Super::BeginPlay();

	StimuliSourceComponent->RegisterForSense(TSubclassOf<UAISense_Sight>());
	StimuliSourceComponent->bAutoRegister = true;

	if (StimuliSourceComponent)
	{
		UE_LOG(LogTemp, Log, TEXT("StimuliSourceComponent successfully initialized"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StimuliSourceComponent failed to initialize"));
	}
}

void ABaseResource::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ABaseResource::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseResource::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (HP > 0.f)
	{
		float NextHP = HP - DamageAmount;
		if (ADamagedActor* DActor = GetWorld()->SpawnActor<ADamagedActor>(GetActorLocation(), FRotator()))
		{
			DActor->SetDamage(DamageAmount);
		}
		SetHP(NextHP);
		if (NextHP <= 0)
		{
			Die();
		}
	}
	return DamageAmount;
}

void ABaseResource::Respawn()
{
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetHP(GetMaxHP());

}

void ABaseResource::Die()
{
	Destroy();
}
