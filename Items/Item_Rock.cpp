// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item_Rock.h"
#include "Helper.h"

AItem_Rock::AItem_Rock()
{
	ItemMesh->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Assets/CHERRY_TREE/Meshes/Rock/SM_rock_03"));
	ItemMesh->SetRelativeScale3D(FVector(0.1f, 0.1f, 0.1f));
	ItemCol->SetRelativeLocation(FVector(-0.207948f, 0.918179f, 10.0f));
	ItemCol->SetRelativeScale3D(FVector(0.4f, 0.4f, 0.4f));
	texture = Helper::GetAsset<UTexture2D>(L"/Game/Assets/CraftResourcesIcons/Textures/Tex_stone_06_b");
}
