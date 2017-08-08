// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/NoExportTypes.h"
#include "PhysicsEngine/BodyInstance.h"
#include "PhysicsController.generated.h"

/**
 * 
 */
UCLASS()
class THEMAGICGAMERAWCPP_API UPhysicsController : public UObject
{
	GENERATED_BODY()

	public:
		void AssociateWorld(UWorld* NewWorld);
		void ManipulateAllBodies();
		void ManipulateAllBodies(FVector Location, float DistanceFrom);
		static void MoveBodyTowardsBody(FBodyInstance* TargetBody, FBodyInstance* MovingBody);
		static void MoveBodyAwayFromBody(FBodyInstance* TargetBody, FBodyInstance* MovingBody);
		static void MoveBodyTowardsLocation(FBodyInstance* TargetBody, FVector TargetLocation);
		static void MoveBodyAwayFromLocation(FBodyInstance* TargetBody, FVector TargetLocation);
		static TArray<FBodyInstance*> FindBodiesAtLocationWithinDistance(FVector Location, float Distance);
		UFUNCTION(BlueprintCallable)
		static void TestFunction(FVector Location);
	protected:
		UWorld* World;
	
	
};
