// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item_Wood.h"
#include "Helper.h"

AItem_Wood::AItem_Wood()
{
	texture = Helper::GetAsset<UTexture2D>(L"/Game/Assets/CraftResourcesIcons/Textures/Tex_wood_02_b");
}
