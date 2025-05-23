// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerBallBearing.h"

#include "MaterialHLSLTree.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

APlayerBallBearing::APlayerBallBearing()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArm->bDoCollisionTest = false;
	SpringArm->SetUsingAbsoluteRotation(true);
	SpringArm->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1000.f;
	SpringArm->bEnableCameraLag = false;
	SpringArm->CameraLagSpeed = 5.f;

	SpringArm->SetupAttachment(BallMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->bUsePawnControlRotation = false;

	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	bMagnetized = false; 
}

void APlayerBallBearing::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PC = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void APlayerBallBearing::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	BallMesh->AddForce(FVector(InputLongitude, InputLatitude, 0.0f) * ControllerForce * BallMesh->GetMass());

	FVector Velocity = BallMesh->GetPhysicsLinearVelocity();
	const float Z = Velocity.Z;

	Velocity.Z = 0.0f;

	if (Velocity.Size() > MaximumSpeed * 100.f)
	{
		Velocity.Normalize();
		Velocity *= MaximumSpeed * 100.f;
		Velocity.Z = Z;

		const float BrakingRadio = FMath::Pow(1.f - FMath::Min(DashTimer, 1.f), 2.f);

		const FVector MergedVelocity = FMath::Lerp(BallMesh->GetPhysicsLinearVelocity(), Velocity, BrakingRadio);

		BallMesh->SetPhysicsLinearVelocity(MergedVelocity);
	}
	else
	{
		BallMesh->AddForce(FVector(InputLongitude, InputLatitude, 0.f) * ControllerForce * BallMesh->GetMass());
	}

	if (DashTimer > 0.f)
	{
		DashTimer = FMath::Max(0.f, DashTimer - DeltaSeconds);
	}
}

void APlayerBallBearing::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
		EnhancedInput->BindAction(DashAction, ETriggerEvent::Triggered, this, &ThisClass::Dash);
	}
}

void APlayerBallBearing::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	InputLongitude = MovementVector.Y;
	InputLatitude = MovementVector.X;
}

void APlayerBallBearing::Look(const FInputActionValue& Value)
{
}

void APlayerBallBearing::Jump(const FInputActionValue& Value)
{
	if (bInContact)
	{
		BallMesh->AddImpulse(FVector(0.f, 0.f, JumpForce * 1000));
	}
}

void APlayerBallBearing::Dash(const FInputActionValue& Value)
{
	if (DashTimer == 0.f)
	{
		FVector Velocity = BallMesh->GetComponentVelocity();

		if (Velocity.Size() > 1.f)
		{
			Velocity.Normalize();
			Velocity *= DashForce * 1000.f;

			BallMesh->AddImpulse(Velocity);

			DashTimer = 1.5;
		}

	}
}


