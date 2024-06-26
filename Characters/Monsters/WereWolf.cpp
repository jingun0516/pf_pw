#include "Characters/Monsters/WereWolf.h"
#include "Helper.h"
#include "MonsterStatusDataAsset.h"
#include "GameFramework/CharacterMovementComponent.h"

AWereWolf::AWereWolf()
{
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Assets/werewolf/Mesh/SK_Werewolf_cloth"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Monsters/Werewolf/Animations/ABP_Werewolf"));
	
	stats = Helper::GetAsset<UMonsterStatusDataAsset>(L"/Game/Monsters/Werewolf/DA_WereWolf");
}

void AWereWolf::BeginPlay()
{
	Super::BeginPlay();
}

void AWereWolf::SetCharacterMovement()
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
