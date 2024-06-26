// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIMonster/UndeadBear_AI.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/ToolComponent.h"
#include "Tools/BaseTool.h"
#include "Characters/Monsters/MonsterStatusDataAsset.h"
#include "Helper.h"

AUndeadBear_AI::AUndeadBear_AI()
{
	GetMesh()->SetSkeletalMesh(Helper::GetAsset<USkeletalMesh>
		(L"/Game/Assets/StylizedEnemyNPC/Meshes/UndeadBear/SK_UndeadBear"));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	GetMesh()->SetAnimInstanceClass(Helper::GetClass<UAnimInstance>
		(L"/Game/Monsters/UndeadBear/Animations/ABP_UndeadBear"));

	stats = Helper::GetAsset<UMonsterStatusDataAsset>(L"/Game/Monsters/UndeadBear/DA_UndeadBear");

	MonsterToolClass = Helper::GetClass<ABaseTool>(L"/Game/Tools/InvisibleTool/BP_Melee");
}

void AUndeadBear_AI::BeginPlay()
{
	Super::BeginPlay();
}

void AUndeadBear_AI::SetCharacterMovement()
{
	UCharacterMovementComponent* Comp = GetCharacterMovement();

	Comp->bOrientRotationToMovement = false;
	Comp->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	Comp->JumpZVelocity = 700.0f;
	Comp->AirControl = 0.35f;
	Comp->MaxWalkSpeed = 900.0;
	Comp->MaxAcceleration = 500.f;

	Comp->BrakingDecelerationWalking = 2000.0f;
	Comp->BrakingDecelerationFalling = 1500.0f;
}
