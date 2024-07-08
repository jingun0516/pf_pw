#include "Resources/BaseTree.h"
#include "Tools/BaseTool.h"
#include "Particles/ParticleSystem.h"
#include "Helper.h"
#include "Items/Item_Wood.h"
#include "Sound/SoundCue.h"

ABaseTree::ABaseTree()
{
	//mesh->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Meshes/Foliages/SM_Cherry_tree_01.SM_Cherry_tree_01"));
	gather = Helper::GetAsset<UParticleSystem>(L"/Game/Assets/InfinityBladeEffects/Effects/FX_Cines/P_Gate_Sparks_01");
	sound = Helper::GetAsset<USoundCue>(L"/Game/Sounds/Wood_Gather_Cue");
	SpawnItemClass = Helper::GetClass<AItem_Wood>(L"/Game/Items/BP_Item_Wood");
}

void ABaseTree::Die()
{
	Super::Die();

	if (!SpawnItemClass) return;
	
	AItem_Wood* SpawnItem = GetWorld()->SpawnActor<AItem_Wood>(SpawnItemClass, GetActorLocation(), FRotator());
	if (!SpawnItem) return;
	
	UE_LOG(LogTemp, Log, TEXT("ItemSpawned"));
	int32 RandomInt = FMath::RandRange(10, 20);
	UE_LOG(LogTemp, Log, TEXT("RandomInt: %d"), RandomInt);
	SpawnItem->SetCounts(RandomInt);
	SpawnItem->SetActorEnableCollision(true);
	SpawnItem->SetActorHiddenInGame(false);
}

void ABaseTree::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
