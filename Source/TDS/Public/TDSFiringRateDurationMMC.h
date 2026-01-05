// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TDSFiringRateDurationMMC.generated.h"

/**
 * 
 */
UCLASS()
class TDS_API UTDSFiringRateDurationMMC : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

	FGameplayEffectAttributeCaptureDefinition FiringRateDef;

public:
	UTDSFiringRateDurationMMC();

	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const;

};
