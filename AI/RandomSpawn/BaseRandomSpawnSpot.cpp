#include "AI/RandomSpawn/BaseRandomSpawnSpot.h"
#include "Helper.h"
#include "InfosDataAsset.h"
#include "math.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/BaseCharacter.h"
#include "Resources/BaseResource.h"

ABaseRandomSpawnSpot::ABaseRandomSpawnSpot()
{
	PrimaryActorTick.bCanEverTick = true;

	CurTime = 0;
	Infos = Helper::GetAsset<UInfosDataAsset>(L"/Game/ETC/DA_Info");

	SpotCollision = Helper::CreateSceneComponent<UBoxComponent>(this, L"Box Comp");
	SpotCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

}

void ABaseRandomSpawnSpot::BeginPlay()
{
	Super::BeginPlay();

	SetActorTickEnabled(true);

	PlayerC = Cast<ABaseCharacter>(GetWorld()->GetFirstPlayerController()->GetCharacter());
	
}

FVector ABaseRandomSpawnSpot::makeRandomSpot()
{
	FVector Origin = SpotCollision->Bounds.Origin;
	FVector BoxExtent = SpotCollision->Bounds.BoxExtent;
	FVector RandomSpot = UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
	RandomSpot.Z = Origin.Z;
	return RandomSpot;
}

void ABaseRandomSpawnSpot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurTime++;
}

