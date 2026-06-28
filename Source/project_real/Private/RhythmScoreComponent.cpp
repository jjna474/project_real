// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmScoreComponent.h"

// Sets default values
ARhythmScoreComponent::ARhythmScoreComponent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARhythmScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARhythmScoreComponent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARhythmScoreComponent::AddScore(int32 AddValue)
{
	Score += AddValue;
}

int32 ARhythmScoreComponent::GetScore() const
{
	return Score;
}
void ARhythmScoreComponent::AddCombo()
{
    Combo++;
}

void ARhythmScoreComponent::ResetCombo()
{
    Combo = 0;
}

int32 ARhythmScoreComponent::GetCombo() const
{
    return Combo;
}

void ARhythmScoreComponent::ApplyJudgement(ERhythmJudgement Judgement)
{
	switch(Judgement)
    {
    case ERhythmJudgement::Perfect:
        AddScore(100);
        AddCombo();
        break;

    case ERhythmJudgement::Good:
        AddScore(50);
        AddCombo();
        break;

    case ERhythmJudgement::Miss:
        ResetCombo();
        break;
    }
}

