#include "Characters/Monsters/UndeadBear.h"
#include "Helper.h"
#include "MonsterStatusDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

AUndeadBear::AUndeadBear()
{
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Assets/StylizedEnemyNPC/Meshes/UndeadBear/SK_UndeadBear"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Monsters/UndeadBear/Animations/ABP_UndeadBear"));

	stats = Helper::GetAsset<UMonsterStatusDataAsset>(L"/Game/Monsters/UndeadBear/DA_UndeadBear");
}

void AUndeadBear::BeginPlay()
{
	Super::BeginPlay();
}

void AUndeadBear::SetCharacterMovement()
{
	Super::GetCharacterMovement();

	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = true;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 500.0f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}
