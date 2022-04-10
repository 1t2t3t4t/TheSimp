// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TheSimpPlayerController.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UPawnMovementComponent;
class UPlayerStateMachineComponent;

UCLASS()
class THESIMP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UPawnMovementComponent* MovementComponent;

	UPROPERTY(VisibleAnywhere)
	UPlayerStateMachineComponent* StateMachineComponent;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly)
	float RotateRate = 10.f;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void RotateRight(float Value);
	
	void Interact();
	ATheSimpPlayerController* GetPlayerController() const;
};
