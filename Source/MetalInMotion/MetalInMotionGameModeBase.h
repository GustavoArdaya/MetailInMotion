// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MetalInMotionGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class METALINMOTION_API AMetalInMotionGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	
	AMetalInMotionGameModeBase();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
	USoundCue* BackgroundMusic;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Audio)
	USoundCue* FinishedSound;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:

	float FinishedTime = 0.f;

	bool bFinishedSoundPlayed = false;
};
