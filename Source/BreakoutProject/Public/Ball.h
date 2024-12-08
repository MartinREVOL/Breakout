#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Brick.h"
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

    // Reference to the paddle actor
    AActor* PaddleActor;

    // Cooldown for paddle collision to avoid multiple rapid direction changes
    bool bCanCollideWithPaddle;

    // Time delay before enabling collision again
    float CollisionCooldown;

    // Timer to reset collision
    FTimerHandle CollisionResetTimer;

    // Handle collision with paddle
    void CheckPaddleCollision();

    // Find the paddle dynamically
    void FindPaddle();

    // Reset collision flag
    void ResetPaddleCollision();

    // Check for collisions with bricks
    void CheckBrickCollisions();
};
