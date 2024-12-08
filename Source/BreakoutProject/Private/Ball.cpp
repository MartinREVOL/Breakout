#include "Ball.h"
#include "Brick.h" // Include the brick header
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"

// Constructor
ABall::ABall()
{
    // Enable ticking
    PrimaryActorTick.bCanEverTick = true;

    // Create a root component
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    // Create the mesh component
    BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BallMesh"));
    BallMesh->SetupAttachment(RootComponent);

    // Set default values
    MovementSpeed = 300.0f; // Units per second
    MovementDirection = FVector(1.0f, 1.0f, 0.0f).GetSafeNormal(); // Normalize the direction
    LeftBoundary = -500.0f;
    RightBoundary = 500.0f;
    TopBoundary = 500.0f;
    BottomBoundary = -500.0f;
    PaddleActor = nullptr; // No paddle assigned by default

    // Collision handling
    bCanCollideWithPaddle = true;
    CollisionCooldown = 0.2f; // 200ms cooldown
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
    Super::BeginPlay();

    // Find the paddle dynamically
    FindPaddle();
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Update the position based on movement direction and speed
    FVector NewLocation = GetActorLocation();
    NewLocation += MovementDirection * MovementSpeed * DeltaTime;

    // Check for collisions with boundaries
    if (NewLocation.Y <= LeftBoundary || NewLocation.Y >= RightBoundary)
    {
        MovementDirection.Y *= -1; // Reverse Y direction
    }
    if (NewLocation.X >= BottomBoundary)
    {
        MovementDirection.X *= -1; // Reverse X direction
    }

    // Check for collision with the paddle
    CheckPaddleCollision();

    // Check for collision with bricks
    CheckBrickCollisions();

    // Set the new location
    SetActorLocation(NewLocation);
}

void ABall::CheckPaddleCollision()
{
    if (!PaddleActor || !bCanCollideWithPaddle)
    {
        return; // No paddle assigned or collision is on cooldown
    }

    // Get paddle position and scale
    FVector PaddleLocation = PaddleActor->GetActorLocation();
    FVector PaddleScale = PaddleActor->GetActorScale3D();

    // Get ball position
    FVector BallLocation = GetActorLocation();

    // Calculate paddle boundaries
    float PaddleLeft = PaddleLocation.Y - (200.0f * PaddleScale.Y); // Adjust the size factor as needed
    float PaddleRight = PaddleLocation.Y + (200.0f * PaddleScale.Y);
    float PaddleBottom = PaddleLocation.X - (50.0f * PaddleScale.X);
    float PaddleTop = PaddleLocation.X + (50.0f * PaddleScale.X);

    // Check if the ball is within paddle bounds
    bool bIsWithinPaddleY = BallLocation.Y >= PaddleLeft && BallLocation.Y <= PaddleRight;
    bool bIsWithinPaddleX = BallLocation.X >= PaddleBottom && BallLocation.X <= PaddleTop;

    if (bIsWithinPaddleY && bIsWithinPaddleX)
    {
        // Reverse the X direction to simulate a bounce
        MovementDirection.X *= -1;

        // Slightly adjust the ball position to prevent sticking
        BallLocation.X = PaddleTop + 1.0f; // Move slightly above the paddle
        SetActorLocation(BallLocation);

        // Put collision on cooldown
        bCanCollideWithPaddle = false;
        GetWorld()->GetTimerManager().SetTimer(CollisionResetTimer, this, &ABall::ResetPaddleCollision, CollisionCooldown, false);
    }
}

void ABall::FindPaddle()
{
    // Get all actors of the Paddle class in the level
    TArray<AActor*> FoundPaddles;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APawn::StaticClass(), FoundPaddles);

    for (AActor* Actor : FoundPaddles)
    {
        // If this is the paddle class, set it as PaddleActor
        if (Actor->GetName().Contains(TEXT("Paddle")))
        {
            PaddleActor = Actor;
            break;
        }
    }
}

void ABall::ResetPaddleCollision()
{
    bCanCollideWithPaddle = true;
}

void ABall::CheckBrickCollisions()
{
    // Get all actors of the Brick class in the level
    TArray<AActor*> FoundBricks;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrick::StaticClass(), FoundBricks);

    FVector BallLocation = GetActorLocation();

    for (AActor* Actor : FoundBricks)
    {
        ABrick* Brick = Cast<ABrick>(Actor);
        if (Brick)
        {
            FVector BrickLocation = Brick->GetActorLocation();
            FVector BrickScale = Brick->GetActorScale3D();

            // Calculate brick boundaries
            float BrickLeft = BrickLocation.Y - (100.0f * BrickScale.Y); // Adjust the size factor as needed
            float BrickRight = BrickLocation.Y + (100.0f * BrickScale.Y);
            float BrickBottom = BrickLocation.X - (50.0f * BrickScale.X);
            float BrickTop = BrickLocation.X + (50.0f * BrickScale.X);

            // Check if the ball is within brick bounds
            bool bIsWithinBrickY = BallLocation.Y >= BrickLeft && BallLocation.Y <= BrickRight;
            bool bIsWithinBrickX = BallLocation.X >= BrickBottom && BallLocation.X <= BrickTop;

            if (bIsWithinBrickY && bIsWithinBrickX)
            {
                // Reverse the X direction to simulate a bounce
                MovementDirection.X *= -1;

                // Destroy the brick
                Brick->Destroy();

                break; // Only handle one collision per frame
            }
        }
    }
}

