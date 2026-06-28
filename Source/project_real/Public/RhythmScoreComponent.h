// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RhythmScoreComponent.generated.h"

UENUM(BlueprintType)
enum class ERhythmJudgement :uint8
{
	Perfect UMETA(DisplayName="Perfect"),
	Good UMETA(DisplayName="Good"),
	Miss UMETA(DisplayName="Miss")
};
UCLASS()
class PROJECT_REAL_API ARhythmScoreComponent : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARhythmScoreComponent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	int32 Score = 0;
	int32 Combo = 0;

public:
	void AddScore(int32 AddValue);
	UFUNCTION(BlueprintCallable)
	int32 GetScore() const;

	UFUNCTION(BlueprintCallable)
	void ApplyJudgement(ERhythmJudgement Judgement);

	void AddCombo();
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	int32 GetCombo() const;


};
