#include "Paddle.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

// Constructor
APaddle::APaddle()
{
    // Enable ticking
    PrimaryActorTick.bCanEverTick = true;

    // Create a root component
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = Root;

    // Create the mesh component
    PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PaddleMesh"));
    PaddleMesh->SetupAttachment(RootComponent);

    // Set default values
    MovementSpeed = 500.0f; // Units per second
    CurrentMovement = 0.0f;
    LeftBoundary = -500.0f; // Default boundary
    RightBoundary = 500.0f; // Default boundary
}

// Called when the game starts or when spawned
void APaddle::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void APaddle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Apply movement based on current input
    if (CurrentMovement != 0.0f)
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Y += CurrentMovement * MovementSpeed * DeltaTime;

        // Clamp the position to the boundaries
        NewLocation.Y = FMath::Clamp(NewLocation.Y, LeftBoundary, RightBoundary);

        SetActorLocation(NewLocation);
    }
}

// Bind input functions
void APaddle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Bind the input actions
    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &APaddle::MoveLeft);
    PlayerInputComponent->BindAction("MoveLeft", IE_Released, this, &APaddle::StopMovement);
    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &APaddle::MoveRight);
    PlayerInputComponent->BindAction("MoveRight", IE_Released, this, &APaddle::StopMovement);
}

// Handle left movement
void APaddle::MoveLeft()
{
    CurrentMovement = -1.0f; // Move left
}

// Handle right movement
void APaddle::MoveRight()
{
    CurrentMovement = 1.0f; // Move right
}

// Stop movement
void APaddle::StopMovement()
{
    CurrentMovement = 0.0f; // Stop movement
}
