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


DEFINE_LOG_CATEGORY(ResourceLog);

ABaseResource::ABaseResource()
{
	PrimaryActorTick.bCanEverTick = true;

	mesh = Helper::CreateSceneComponent<UStaticMeshComponent>(this, "ResourceMesh");
	
	mesh->OnComponentBeginOverlap.AddDynamic(this, &ABaseResource::OnBeginOverlap);
}

void ABaseResource::BeginPlay()
{
	Super::BeginPlay();
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
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);

	FTimerHandle SpawnTimerHandle;
	float RespawnDelay = 5.0f;
	GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &ABaseResource::Respawn, RespawnDelay, false);
}
