// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheSimpPlayerController.h"
#include "GameFramework/Pawn.h"
#include "StateMachine/IPlayerState.h"
#include "PlayerControl.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPawnMovementComponent;
class UPlayerStateMachineComponent;
class ASimp;

UCLASS()
class THESIMP_API APlayerControl : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerControl();

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UPlayerStateMachineComponent* StateMachineComponent;

	UPROPERTY(VisibleAnywhere)
	ASimp* ControlSimp;

	UPROPERTY(VisibleAnywhere)
	TArray<ASimp*> HouseHold;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASimp> SimpClass;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float RotateRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float ZoomSpeed = 10.f;

	UPROPERTY(EditDefaultsOnly)
	float ZoomMin = 300.f;

	UPROPERTY(EditDefaultsOnly)
	float ZoomMax = 1200.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	ASimp* SpawnSimp();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);
	bool CastCursorToWorld(FHitResult& Result) const;
	void Click();

	void Interact();
	FPlayerContext CreateContext() const;
	void Zoom(float Value);
	ATheSimpPlayerController* GetPlayerController() const;
};
