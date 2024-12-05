#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Ball.generated.h"

UCLASS()
class BREAKOUTPROJECT_API ABall : public APawn
{
    GENERATED_BODY()

public:
    // Constructor
    ABall();

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
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball Components", meta = (AllowPrivateAccess = "true"))
    USceneComponent* Root;

    // Mesh component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ball Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BallMesh;

    // Movement speed
    UPROPERTY(EditAnywhere, Category = "Ball Movement")
    float MovementSpeed;

    // Movement direction
    FVector MovementDirection;

    // Boundaries for the ball
    UPROPERTY(EditAnywhere, Category = "Ball Movement")
    float LeftBoundary;

    UPROPERTY(EditAnywhere, Category = "Ball Movement")
    float RightBoundary;

    UPROPERTY(EditAnywhere, Category = "Ball Movement")
    float TopBoundary;

    UPROPERTY(EditAnywhere, Category = "Ball Movement")
    float BottomBoundary;

    // Function to handle boundary collisions
    void HandleBoundaryCollision();
};
