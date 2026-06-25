// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmManager.generated.h"

UENUM(BlueprintType)
enum class ERhythmColor : uint8
{
	Red UMETA(DisplayName="Red"),
	Yellow UMETA(DisplayName="Yellow"),
	Blue UMETA(DisplayName="Blue")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHintColor, ERhythmColor, Color);

UCLASS()
class PROJECT_REAL_API ARhythmManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rhythm")
	float BPM = 110.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Rhythm")
	float CurrentMusicTime = 0.0f;

	UPROPERTY(BlueprintAssignable, Category = "Rhythm")
	FOnHintColor OnHintColor;

	UFUNCTION(BlueprintCallable, Category = "Rhythm")
	void StartRhythm();

private:
	float StartTime = 0.0f;
	bool bStarted = false;

	int HintIndex = 0;
	TArray<ERhythmColor> HintPattern;

	void PlayNextHint();

};
