#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Brick.generated.h"

UCLASS()
class BREAKOUTPROJECT_API ABrick : public AActor
{
    GENERATED_BODY()

public:
    // Constructor
    ABrick();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Function to handle destruction
    void DestroyBrick();

private:
    // Mesh component for the brick
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Brick Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* BrickMesh;
};
