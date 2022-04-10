// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

#include "DrawDebugHelpers.h"
#include "TheSimpPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "StateMachine/PlayerStateMachineComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	StateMachineComponent = CreateDefaultSubobject<UPlayerStateMachineComponent>(TEXT("State Machine"));
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
	bUseControllerRotationYaw = true;
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerPawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateRight"), this, &APlayerPawn::RotateRight);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerPawn::Interact);
}

ATheSimpPlayerController* APlayerPawn::GetPlayerController() const
{
	return Cast<ATheSimpPlayerController>(GetController());
}

#pragma region Movement

void APlayerPawn::MoveForward(const float Value)
{
	const float Movement = Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Direction = GetActorForwardVector() * Movement;
	AddMovementInput(Direction);
}

void APlayerPawn::MoveRight(const float Value)
{
	const float Movement = Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Direction = GetActorRightVector() * Movement;
	AddMovementInput(Direction);
}

void APlayerPawn::RotateRight(const float Value)
{
	const float Rotate = -1.f * Value * RotateRate * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Rotate);
}

#pragma endregion

#pragma region Interaction

void APlayerPawn::Interact()
{
	if (const ATheSimpPlayerController* PlayerController = GetPlayerController())
	{
		FHitResult Result;
		const bool bHit = PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Result);
		if (bHit)
		{
			DrawDebugSphere(GetWorld(), Result.ImpactPoint, 30.f, 6.f, FColor::Red, false, 10);
		}
	}
}

#pragma endregion 
