// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSPawnManagerComponent.h"
#include "..\TDS.h"
#include "..\TDSCharacter.h"

const FName UTDSPawnManagerComponent::NAME_ActorFeatureName("PawnManager");

UTDSPawnManagerComponent::UTDSPawnManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UTDSPawnManagerComponent::OnRegister()
{
	Super::OnRegister();

	const APawn* Pawn = GetPawn<APawn>();
	ensureAlwaysMsgf((Pawn != nullptr), TEXT("UTDSPawnManagerComponent on [%s] can only be added to Pawn actors."), *GetNameSafe(GetOwner()));

	TArray<UActorComponent*> PawnExtensionComponents;
	Pawn->GetComponents(UTDSPawnManagerComponent::StaticClass(), PawnExtensionComponents);
	ensureAlwaysMsgf((PawnExtensionComponents.Num() == 1), TEXT("Only one UTDSPawnManagerComponent should exist on [%s]."), *GetNameSafe(GetOwner()));

	// Register with the init state system early, this will only work if this is a game world
	RegisterInitStateFeature();
}

void UTDSPawnManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for changes to all features
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);

	// Notifies state manager that we have spawned, then try rest of default initialization
	ensure(TryToChangeInitState(TDSGameplayTags::InitState_Spawned));
	CheckDefaultInitialization();
}

void UTDSPawnManagerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UTDSPawnManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CheckDefaultInitialization();
}

void UTDSPawnManagerComponent::CheckDefaultInitialization()
{
	static const TArray<FGameplayTag> StateChain = { TDSGameplayTags::InitState_Spawned, TDSGameplayTags::InitState_GameplayReady };

	// This will try to progress from spawned (which is only set in BeginPlay) through the data initialization stages until it gets to gameplay ready
	ContinueInitStateChain(StateChain);
}

bool UTDSPawnManagerComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	APawn* Pawn = GetPawn<APawn>();
	if (!CurrentState.IsValid() && DesiredState == TDSGameplayTags::InitState_Spawned)
	{
		// As long as we are on a valid pawn, we count as spawned
		if (Pawn)
		{
			return true;
		}
	}
	else if (CurrentState == TDSGameplayTags::InitState_Spawned && DesiredState == TDSGameplayTags::InitState_GameplayReady)
	{
		if (ATDSCharacter* TDSChar = Cast<ATDSCharacter>(Pawn))
		{
			return TDSChar->IsReady();
		}
	}

	return false;
}

void UTDSPawnManagerComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	UE_LOG(LogTemp, Log, TEXT("HandleChangeInitState - Current [%s] -> Desired [%s]"), *CurrentState.ToString(), *DesiredState.ToString());

	if (DesiredState == TDSGameplayTags::InitState_GameplayReady)
	{
		SetComponentTickEnabled(false);
	}
}
