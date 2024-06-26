// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDrop.generated.h"

/**
 * 
 */
UCLASS()
class PF_PW_API UDragDrop : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UUserWidget* WidgetReference;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FVector2D DropOffset;
};
