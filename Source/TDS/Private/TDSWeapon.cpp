// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSWeapon.h"

// Sets default values
ATDSWeapon::ATDSWeapon()
	: IsAutoFire(false), Damage(5.0f), FiringRate(2.0f), MaxLoadedAmmo(24.0f), ShotCount(1.0f), ShotSpread(0.0f)
{
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	RootComponent = SkeletalMeshComp;
}

// Called when the game starts or when spawned
void ATDSWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void ATDSWeapon::Equip()
{
	OnEquip();
}

void ATDSWeapon::UnEquip()
{
	OnUnEquip();
}