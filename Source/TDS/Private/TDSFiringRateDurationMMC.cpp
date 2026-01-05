// Fill out your copyright notice in the Description page of Project Settings.


#include "TDSFiringRateDurationMMC.h"
#include "TDSWeaponSet.h"

UTDSFiringRateDurationMMC::UTDSFiringRateDurationMMC()
{
	FiringRateDef.AttributeToCapture = UTDSWeaponSet::GetFiringRateAttribute();
	FiringRateDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	FiringRateDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(FiringRateDef);
}

float UTDSFiringRateDurationMMC::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float FiringRate = 0.0f;
	GetCapturedAttributeMagnitude(FiringRateDef, Spec, EvaluationParameters, FiringRate);
	FiringRate = FMath::Max<float>(FiringRate, 0.01f);

	return 1.0f / FiringRate;
}
