// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BallBearing.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PlayerBallBearing.generated.h"

class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class APlayerBallBearing : public ABallBearing
{
	GENERATED_BODY()

public:
	APlayerBallBearing();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BallBearing")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BallBearing")
	UCameraComponent* Camera;

	// Force to use to push the ball bearing around
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BallBearing")
	float ControllerForce = 250.f;

	// Force to push the ball bearing into the air
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BallBearing")
	float JumpForce = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BallBearing")
	float DashForce = 150.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BallBearing")
	float MaximumSpeed = 4.f;

protected:
	
	virtual void Tick(float deltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	// Input Mapping Context
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Input Actions
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* DashAction;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Jump(const FInputActionValue& Value);

	UFUNCTION()
	void Dash(const FInputActionValue& Value);


private:

	float InputLongitude = 0.f;

	float InputLatitude = 0.f;

	float DashTimer = 0.f;
};
