#include "Ball.h"
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
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
    Super::BeginPlay();
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
    if (NewLocation.X <= TopBoundary || NewLocation.X >= BottomBoundary)
    {
        MovementDirection.X *= -1; // Reverse Z direction
    }

    // Set the new location
    SetActorLocation(NewLocation);
}

// Called to bind functionality to input
void ABall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // No input functionality for the ball currently
}
