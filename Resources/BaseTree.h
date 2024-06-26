// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Resources/BaseResource.h"
#include "BaseTree.generated.h"

class UParticleSystem;

UCLASS()
class PF_PW_API ABaseTree : public ABaseResource
{
	GENERATED_BODY()

public:
	ABaseTree();


	virtual void Die() override;
private:
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
