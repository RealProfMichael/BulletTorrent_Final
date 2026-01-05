// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSDestructible.h"
#include "AbilitySystemComponent.h"
#include "TDSHealthSet.h"

// Sets default values
ATDSDestructible::ATDSDestructible()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMeshComp;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComp");
	AbilitySystemComponent->SetIsReplicated(true);

	HealthSet = CreateDefaultSubobject<UTDSHealthSet>("HealthSet");
}

// Called when the game starts or when spawned
void ATDSDestructible::BeginPlay()
{
	Super::BeginPlay();

	if (!AbilitySystemComponent)
		return;

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(HealthSet->GetHealthAttribute()).AddUObject(this, &ATDSDestructible::OnHealthAttributeChanged);
}

UAbilitySystemComponent* ATDSDestructible::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATDSDestructible::OnHealthAttributeChanged(const FOnAttributeChangeData& Data)
{
	OnHealthChanged(Data.OldValue, Data.NewValue);
}

// Called every frame
void ATDSDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}