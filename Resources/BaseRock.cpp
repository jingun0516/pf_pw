#include "Resources/BaseRock.h"
#include "Helper.h"
#include "Tools/BaseTool.h"
#include "Particles/ParticleSystem.h"
#include "Items/Item_Rock.h"
#include "Sound/SoundCue.h"

ABaseRock::ABaseRock()
{
	//mesh->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Meshes/Foliages/SM_rock_04_b"));
	gather = Helper::GetAsset<UParticleSystem>(L"/Game/Assets/InfinityBladeEffects/Effects/FX_Cines/P_Gate_Sparks_01");
	sound = Helper::GetAsset<USoundCue>(L"/Game/Sounds/Rock_Gather_Cue");
	SpawnItemClass = Helper::GetClass<AItem_Rock>(L"/Game/Items/BP_Item_Rock");
}

void ABaseRock::Die()
{
	Super::Die();

	if (!SpawnItemClass) return;
	
	UE_LOG(LogTemp, Log, TEXT("SpawnItemClass YES"));
	AItem_Rock* SpawnItem = GetWorld()->SpawnActor<AItem_Rock>(SpawnItemClass, GetActorLocation(), FRotator());
	if (!SpawnItem) return;
		
	UE_LOG(LogTemp, Log, TEXT("ItemSpawned"));
	int32 RandomInt = FMath::RandRange(10, 20);
	SpawnItem->SetCounts(RandomInt);
	SpawnItem->SetActorEnableCollision(true);
	SpawnItem->SetActorHiddenInGame(false);
		
	}


void ABaseRock::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
