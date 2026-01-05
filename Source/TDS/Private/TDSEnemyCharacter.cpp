// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "TDSGameplayAbility.h"
#include "TDSHealthSet.h"
#include "TDSWeaponSet.h"

// Sets default values
ATDSEnemyCharacter::ATDSEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);

	HealthSet = CreateDefaultSubobject<UTDSHealthSet>("HealthSet");
	WeaponSet = CreateDefaultSubobject<UTDSWeaponSet>("WeaponSet");
}

void ATDSEnemyCharacter::OnMoveSpeedMultiAttributeChanged(const FOnAttributeChangeData& Data)
{
	GetCharacterMovement()->MaxWalkSpeed = DefaultMaxWalkSpeed * Data.NewValue;
}

// Called when the game starts or when spawned
void ATDSEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthAttribute()).AddUObject(this, &ATDSEnemyCharacter::OnHealthAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetShieldAttribute()).AddUObject(this, &ATDSEnemyCharacter::OnShieldAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetMoveSpeedMultiAttribute()).AddUObject(this, &ATDSEnemyCharacter::OnMoveSpeedMultiAttributeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHeatAttribute()).AddUObject(this, &ATDSEnemyCharacter::OnHeatAttributeChanged);
	HealthSet->OnDamageTaken.AddUObject(this, &ATDSEnemyCharacter::OnDamageTakenChanged);
}

UAbilitySystemComponent* ATDSEnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATDSEnemyCharacter::InitializeAbilities()
{
	// Give Abilities, Server only
	if (!HasAuthority() || !AbilitySystemComponent)
		return;

	for (TSubclassOf<UTDSGameplayAbility>& Ability : DefaultAbilities)
	{
		FGameplayAbilitySpecHandle SpecHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 1, static_cast<int32>(Ability.GetDefaultObject()->AbilityInputID), this));
	}
}

void ATDSEnemyCharacter::InitializeEffects()
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

void ATDSEnemyCharacter::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

void ATDSEnemyCharacter::OnHeatAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHeatChanged(Data.OldValue, Data.NewValue);
}

void ATDSEnemyCharacter::OnShieldAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnShieldChanged(Data.OldValue, Data.NewValue);
}

void ATDSEnemyCharacter::OnDamageTakenChanged(AActor* DamageInstigator, AActor* DamageCauser, const FGameplayTagContainer& GameplayTagContainer, float Damage)
{
	OnDamageTaken(DamageInstigator, DamageCauser, GameplayTagContainer, Damage);
}

void ATDSEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitializeEffects();
	InitializeAbilities();
}

// Called every frame
void ATDSEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}