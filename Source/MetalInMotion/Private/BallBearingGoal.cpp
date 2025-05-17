// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingGoal.h"

#include "BallBearing.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"


/**
Get a ratio of a value between a minimum and maximum amount, optionally clamped.
*********************************************************************************/

static float GetRatio(float Value, float Minimum, float Maximum, bool bClamp = true)
{
	if (Value > Maximum && bClamp == true)
	{
		return 1.0f;
	}
	else if (Value > Minimum)
	{
		return (Value - Minimum) / (Maximum - Minimum);
	}
	else
	{
		return 0.0f;
	}
}

/**
Constructor for a goal for ball bearings.
*********************************************************************************/

ABallBearingGoal::ABallBearingGoal()
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorHiddenInGame(false);
}


/**
Hide the collision and sprite components in-game.
*********************************************************************************/

bool ABallBearingGoal::HasBallBearing() const
{
	const FVector CurrentLocation = GetActorLocation();

	for (const ABallBearing* BallBearing : BallBearings)
	{
		FVector Difference = CurrentLocation - BallBearing->GetActorLocation();
		const float Distance = Difference.Size();

		if (Distance < 75.f)
		{
			return true;
		}
	}
	return false;
}

void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);

#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->SetHiddenInGame(true);
#endif
}

void ABallBearingGoal::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector CurrentLocation = GetActorLocation();
	float SphereRadius = Cast<USphereComponent>(GetCollisionComponent())->GetScaledSphereRadius();
	float TickMagnetism = Magnetism;

	// If we're cheating then give our goals extra magnetism.

	static const IConsoleVariable* ExtraForce = IConsoleManager::Get().FindConsoleVariable(TEXT("OurGame.ExtraMagnetism"));

	if (ExtraForce != nullptr &&
		ExtraForce->GetInt() != 0)
	{
		TickMagnetism *= 4.0f;
	}

	for (ABallBearing* BallBearing : BallBearings)
	{
		FVector Difference = CurrentLocation - BallBearing->GetActorLocation();
		float Distance = Difference.Size();
		FVector Direction = Difference;

		Direction.Normalize();

		float Ratio = GetRatio(Distance, 0.f, SphereRadius);
		FVector Force = (1.f - Ratio) * TickMagnetism * Direction;

		BallBearing->BallMesh->AddForce(Force);
	}
}


/**
Add a ball bearing to the list of proximate bearings we're maintaining.
*********************************************************************************/

void ABallBearingGoal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);

	if (BallBearing != nullptr &&
		BallBearing->bMagnetized == true)
	{
		BallBearings.AddUnique(BallBearing);
	}
}


/**
Remove a ball bearing from the list of proximate bearings we're maintaining.
*********************************************************************************/

void ABallBearingGoal::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);

	ABallBearing* BallBearing = Cast<ABallBearing>(OtherActor);

	if (BallBearing != nullptr &&
		BallBearing->bMagnetized == true)
	{
		BallBearings.Remove(BallBearing);
	}
}
