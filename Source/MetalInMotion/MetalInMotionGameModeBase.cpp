// Fill out your copyright notice in the Description page of Project Settings.


#include "MetalInMotionGameModeBase.h"
#include "BallBearingHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "BallBearingGoal.h"
#include "GameFramework/GameMode.h"

AMetalInMotionGameModeBase::AMetalInMotionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = ABallBearingHUD::StaticClass();
}

void AMetalInMotionGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(AActor::GetWorld(), BackgroundMusic);
}

void AMetalInMotionGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	int32 NumGoals = 0;
	bool Finished = true;
	TArray<AActor*> Actors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABallBearingGoal::StaticClass(), Actors);

	for (const AActor* Goal : Actors)
	{
		NumGoals++;

		if ((Cast<ABallBearingGoal>(Goal))->HasBallBearing() == false)
		{
			Finished = false;
			break;
		}
	}

	if (NumGoals > 0 && Finished == true)
	{
		FinishedTime += DeltaTime;
	}
	else
	{
		FinishedTime = 0.f;
	}

	if (FinishedTime > 1.f)
	{
		if (!bFinishedSoundPlayed)
		{
			bFinishedSoundPlayed = true;

			UGameplayStatics::PlaySound2D(GetWorld(), FinishedSound);
		}

		if (FinishedTime > 10.f)
		{
			Super::RestartGame();
		}
	}
}
