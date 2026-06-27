// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorCommunicate.h"
#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/LightComponent.h"

// Sets default values
AActorCommunicate::AActorCommunicate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorCommunicate::BeginPlay()
{
	Super::BeginPlay();
	
	ApplyRandomNeonColors();
    TurnOnStreetLights();
}

void AActorCommunicate::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);

    ApplyRandomNeonColors();
}


// Called every frame
void AActorCommunicate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActorCommunicate::ApplyRandomNeonColors()
{
    TArray<AActor*> SignActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), SignTag, SignActors);

    UE_LOG(LogTemp, Warning, TEXT("찾은 간판 개수: %d"), SignActors.Num());

    TArray<FLinearColor> NeonColors;
    NeonColors.Add(FLinearColor(1.0f, 0.05f, 0.8f, 1.0f));  // 핫핑크
    NeonColors.Add(FLinearColor(0.0f, 0.3f, 1.0f, 1.0f));   // 블루
    NeonColors.Add(FLinearColor(0.7f, 0.1f, 1.0f, 1.0f));   // 퍼플
    NeonColors.Add(FLinearColor(1.0f, 0.1f, 0.2f, 1.0f));   // 레드
    NeonColors.Add(FLinearColor(0.0f, 0.05f, 0.6f, 1.0f));  // 딥 블루

    for (AActor* Sign : SignActors)
    {
        UStaticMeshComponent* Mesh = Sign->FindComponentByClass<UStaticMeshComponent>();
        if (!Mesh) continue;

        UMaterialInstanceDynamic* DynMat = Mesh->CreateAndSetMaterialInstanceDynamic(0);
        if (!DynMat) continue;

        int32 RandomIndex = FMath::RandRange(0, NeonColors.Num() - 1);
        FLinearColor SelectedColor = NeonColors[RandomIndex];

        DynMat->SetVectorParameterValue(TEXT("NeonColor"), SelectedColor * NeonPower);
    }
}

void AActorCommunicate::TurnOnStreetLights()
{
    TArray<AActor*> LightActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), StreetLightTag, LightActors);

    UE_LOG(LogTemp, Warning, TEXT("찾은 라이트 개수: %d"), LightActors.Num());

    for (AActor* LightActor : LightActors)
    {
        ULightComponent* LightComp = LightActor->FindComponentByClass<ULightComponent>();
        if (!LightComp) continue;

        LightComp->SetVisibility(true);
        LightComp->SetIntensity(StreetLightIntensity);
    }
}

void AActorCommunicate::TurnOffStreetLights()
{
    TArray<AActor*> LightActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), StreetLightTag, LightActors);

    for (AActor* LightActor : LightActors)
    {
        ULightComponent* LightComp = LightActor->FindComponentByClass<ULightComponent>();
        if (!LightComp) continue;

        LightComp->SetVisibility(false);
    }
}

