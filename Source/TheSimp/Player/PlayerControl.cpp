// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControl.h"

#include "DrawDebugHelpers.h"
#include "TheSimpPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "StateMachine/PlayerStateMachineComponent.h"
#include "TheSimp/Character/Simp.h"

// Sets default values
APlayerControl::APlayerControl()
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
void APlayerControl::BeginPlay()
{
	Super::BeginPlay();
	
	bUseControllerRotationYaw = true;
	ControlSimp = SpawnSimp();
}

// Called every frame
void APlayerControl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

ASimp* APlayerControl::SpawnSimp()
{
	ASimp* Simp = GetWorld()->SpawnActor<ASimp>(SimpClass);
	HouseHold.Add(Simp);
	Simp->SetOwner(this);
	return Simp;
}

// Called to bind functionality to input
void APlayerControl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerControl::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerControl::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("RotateRight"), this, &APlayerControl::RotateRight);

	PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &APlayerControl::Interact);
	PlayerInputComponent->BindAction(TEXT("Click"), IE_Pressed, this, &APlayerControl::Click);
}

ATheSimpPlayerController* APlayerControl::GetPlayerController() const
{
	return Cast<ATheSimpPlayerController>(GetController());
}

#pragma region Movement

void APlayerControl::MoveForward(const float Value)
{
	const float Movement = Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Direction = GetActorForwardVector() * Movement;
	AddMovementInput(Direction);
}

void APlayerControl::MoveRight(const float Value)
{
	const float Movement = Value * MovementSpeed * GetWorld()->GetDeltaSeconds();
	const FVector Direction = GetActorRightVector() * Movement;
	AddMovementInput(Direction);
}

void APlayerControl::RotateRight(const float Value)
{
	const float Rotate = -1.f * Value * RotateRate * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(Rotate);
}

#pragma endregion

#pragma region Interaction

bool APlayerControl::CastCursorToWorld(FHitResult& Result) const
{
	if (const ATheSimpPlayerController* PlayerController = GetPlayerController())
	{
		return PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, Result);
	}

	return false;
}

void APlayerControl::Click()
{
	FHitResult Result;
	const bool bHit = CastCursorToWorld(Result);
	if (bHit && StateMachineComponent)
	{
		StateMachineComponent->Click(Result, CreateContext());
	}
}

void APlayerControl::Interact()
{
	FHitResult Result;
	const bool bHit = CastCursorToWorld(Result);
	if (bHit && StateMachineComponent)
	{
		StateMachineComponent->InteractWorld(Result, CreateContext());
	}
}

FPlayerContext APlayerControl::CreateContext() const
{
	return FPlayerContext(ControlSimp);
}

#pragma endregion 
