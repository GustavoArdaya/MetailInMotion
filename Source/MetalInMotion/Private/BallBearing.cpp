// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearing.h"

ABallBearing::ABallBearing()
{
	PrimaryActorTick.bCanEverTick = true;

	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
	BallMesh->SetSimulatePhysics(true);
	SetRootComponent(BallMesh);
}

void ABallBearing::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABallBearing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABallBearing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

