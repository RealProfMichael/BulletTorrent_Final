// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSHealthSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"

UTDSHealthSet::UTDSHealthSet()
	: Health(40.0f), MaxHealth(60.0f), Shield(0.0f), MaxShield(0.0f), ShieldRegen(0.0f), ShieldRegenDelay(1.0f), MoveSpeedMulti(1.0f)
{

}

void UTDSHealthSet::ClampAttributeOnChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	else if (Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxShield());
	}
}

void UTDSHealthSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UTDSHealthSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTDSHealthSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTDSHealthSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDSHealthSet, Health, OldHealth);
}

void UTDSHealthSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTDSHealthSet, MaxHealth, OldMaxHealth);
}

void UTDSHealthSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetInDamageAttribute())
	{
		float InDamageDone = GetInDamage();
		SetInDamage(0.0f);
		if (InDamageDone > 0.0f)
		{
			if (GetShield() > 0.0f)
			{
				float NewShield = GetShield();
				const float ShieldDiff = FMath::Min(NewShield, InDamageDone);
				InDamageDone -= ShieldDiff;
				NewShield -= ShieldDiff;
				SetShield(NewShield);
			}

			if (InDamageDone > 0.0f)
			{
				float NewHealth = GetHealth();
				const float HealthDiff = FMath::Min(NewHealth, InDamageDone);
				SetHealth(NewHealth - HealthDiff);
			}

			if (OnDamageTaken.IsBound())
			{
				const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
				AActor* Instigator = EffectContext.GetOriginalInstigator();
				AActor* Causer = EffectContext.GetEffectCauser();

				OnDamageTaken.Broadcast(Instigator, Causer, Data.EffectSpec.CapturedSourceTags.GetSpecTags(), Data.EvaluatedData.Magnitude);
			}
		}
	}
}
