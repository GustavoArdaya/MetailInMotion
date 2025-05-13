// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingGoal.h"

#include "BallBearing.h"
#include "Components/SphereComponent.h"
#include "Components/BillboardComponent.h"


/**
Constructor for a goal for ball bearings.
*********************************************************************************/

ABallBearingGoal::ABallBearingGoal()
{
	SetActorHiddenInGame(false);
}


/**
Hide the collision and sprite components in-game.
*********************************************************************************/

void ABallBearingGoal::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GetCollisionComponent()->SetHiddenInGame(true);

#if WITH_EDITORONLY_DATA
	GetSpriteComponent()->SetHiddenInGame(true);
#endif
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
