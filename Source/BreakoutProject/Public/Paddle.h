#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Paddle.generated.h"

UCLASS()
class BREAKOUTPROJECT_API APaddle : public APawn
{
    GENERATED_BODY()

public:
    // Constructor
    APaddle();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    // Root component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* Root;

    // Mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Paddle Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* PaddleMesh;

    // Movement speed
    UPROPERTY(EditAnywhere, Category = "Paddle Movement")
    float MovementSpeed;

    // Boundaries for movement
    UPROPERTY(EditAnywhere, Category = "Paddle Movement")
    float LeftBoundary;

    UPROPERTY(EditAnywhere, Category = "Paddle Movement")
    float RightBoundary;

    // Input functions
    void MoveLeft();
    void MoveRight();
    void StopMovement();


    // Current movement direction (-1 for left, 1 for right, 0 for no movement)
    float CurrentMovement;
};
