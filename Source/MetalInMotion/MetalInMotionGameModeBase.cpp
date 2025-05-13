// Fill out your copyright notice in the Description page of Project Settings.


#include "MetalInMotionGameModeBase.h"
#include "BallBearingHUD.h"

AMetalInMotionGameModeBase::AMetalInMotionGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;

	HUDClass = ABallBearingHUD::StaticClass();
}
