#include "Items/Item_Wood.h"
#include "Helper.h"

AItem_Wood::AItem_Wood()
{
	ItemMesh->SetStaticMesh(Helper::GetAsset<UStaticMesh>(L"/Game/Fantastic_Village_Pack/meshes/props/natural/SM_PROP_treetrunk_01"));
	texture = Helper::GetAsset<UTexture2D>(L"/Game/Assets/CraftResourcesIcons/Textures/Tex_wood_02_b");
}
