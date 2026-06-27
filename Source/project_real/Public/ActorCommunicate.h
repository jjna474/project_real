#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorCommunicate.generated.h"

UCLASS()
class PROJECT_REAL_API AActorCommunicate : public AActor
{
    GENERATED_BODY()

public:
    AActorCommunicate();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName SignTag = "Sign";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float NeonPower = 10.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName StreetLightTag = "StreetLight";

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StreetLightIntensity = 3000.0f;

    UFUNCTION(BlueprintCallable)
    void ApplyRandomNeonColors();

    UFUNCTION(BlueprintCallable)
    void TurnOnStreetLights();

    UFUNCTION(BlueprintCallable)
    void TurnOffStreetLights();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
    virtual void OnConstruction(const FTransform& Transform) override;
};