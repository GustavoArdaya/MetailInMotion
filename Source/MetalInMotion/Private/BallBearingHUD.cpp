// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBearingHUD.h"

#include "PlayerBallBearing.h"

class APlayerBallBearing;

void ABallBearingHUD::DrawHUD()
{
	Super::DrawHUD();

	if (APlayerBallBearing* BallBearing = Cast<APlayerBallBearing>(GetOwningPawn()))
	{
		AddFloat(L"Speed", BallBearing->GetVelocity().Size() / 100.0f);
		AddFloat(L"Dash timer", BallBearing->GetDashTimer());
		AddFloat(L"Input latitude", BallBearing->GetInputLatitude());
		AddFloat(L"Input longitude", BallBearing->GetInputLongitude());
	}
}
