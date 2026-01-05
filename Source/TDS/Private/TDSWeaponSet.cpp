// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSWeaponSet.h"

UTDSWeaponSet::UTDSWeaponSet()
	: Damage(1.0f), FiringRate(1.0f), LoadedAmmo(0.0f), MaxLoadedAmmo(20.0f), CarriedAmmo(100.0f), MaxCarriedAmmo(100.0f), ShotCount(1.0f), ShotSpread(0.0f)
{
}

void UTDSWeaponSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetLoadedAmmoAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxLoadedAmmo());
	}
	else if (Attribute == GetCarriedAmmoAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxCarriedAmmo());
	}
}
