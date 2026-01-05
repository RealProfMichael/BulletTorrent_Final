// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSPlayerState.h"
#include "AbilitySystemComponent.h"
#include "TDSHealthSet.h"
#include "TDSWeaponSet.h"
#include "../TDS.h"
#include "TDSGameplayAbility.h"

ATDSPlayerState::ATDSPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);

	HealthSet = CreateDefaultSubobject<UTDSHealthSet>("HealthSet");
	WeaponSet = CreateDefaultSubobject<UTDSWeaponSet>("WeaponSet");
}

void ATDSPlayerState::BeginPlay()
{
	Super::BeginPlay();

	InitializeEffects();
	InitializeAbilities();
}

UAbilitySystemComponent* ATDSPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATDSPlayerState::InitializeAbilities()
{
	// Give Abilities, Server only
	if (!HasAuthority() || !AbilitySystemComponent)
		return;

	for (TSubclassOf<UTDSGameplayAbility>& Ability : DefaultAbilities)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}
}

void ATDSPlayerState::InitializeEffects()
{
	if (!AbilitySystemComponent)
		return;

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect>& Effect : DefaultEffects)
	{
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);
		if (SpecHandle.IsValid())
		{
			FActiveGameplayEffectHandle GEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}