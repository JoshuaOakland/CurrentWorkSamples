// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "SpellConflict.h"
#include "SpellResolver.generated.h"

/**
 * Handles final resolution of spells, and accepts results for arbitration from spell controller. I.e. after flying past a tree a fireball hits the back of a wizard
 * lifecycle of a spell is SpellFactory -> SpellController -> SpellResolver -> cleanup
 */
UCLASS()
class THEMAGICGAMERAWCPP_API USpellResolver : public UObject
{
	GENERATED_BODY()
	public:
		void AcceptConflict(USpellConflict* SpellConflict);
		TArray<USpellConflict*> ConflictArray;
		void Initialize();
		void DestroyConflict(USpellConflict* SpellConflict);
		void DeferDestroy(USpellConflict* SpellConflict);
		void Tick(float DeltaTime);
		float DestructionTimer;
		float DestructionTimeLimit;
		uint8 DestructionSanity;
		float DestructionTickRate;
};
