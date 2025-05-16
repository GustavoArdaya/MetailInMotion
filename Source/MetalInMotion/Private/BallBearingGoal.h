// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerSphere.h"
#include "BallBearingGoal.generated.h"

class ABallBearing;
/**
 * 
 */
UCLASS()
class ABallBearingGoal : public ATriggerSphere
{
	GENERATED_BODY()

public:

	ABallBearingGoal();

	// The power of the magnetism.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Goal)
	float Magnetism = 7500.0f;

protected:

	// Hide the collision and sprite components in-game.
	virtual void PostInitializeComponents() override;

	// Add magnetism to the proximate ball bearings, drawing them towards our center.
	virtual void Tick(float DeltaSeconds) override;

	// Add a ball bearing to the list of proximate bearings we're maintaining.
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	// Remove a ball bearing from the list of proximate bearings we're maintaining.
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

private:

	// A list of proximate ball bearings.
	UPROPERTY(Transient)
	TArray<ABallBearing*> BallBearings;
};
