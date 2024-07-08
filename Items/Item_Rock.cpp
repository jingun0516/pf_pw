// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item_Rock.h"
#include "Helper.h"

AItem_Rock::AItem_Rock()
{
	ItemMesh->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Assets/CHERRY_TREE/Meshes/Rock/SM_rock_03"));
	texture = Helper::GetAsset<UTexture2D>(L"/Game/Assets/CraftResourcesIcons/Textures/Tex_stone_06_b");
}
