// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmManager.h"
#include "Components/AudioComponent.h"

// Sets default values
ARhythmManager::ARhythmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;

}

// Called when the game starts or when spawned
void ARhythmManager::BeginPlay()
{
	Super::BeginPlay();

	if (Music)
	{
		AudioComponent->SetSound(Music);
		AudioComponent->Play();
		StartTime = GetWorld()->GetTimeSeconds();
		bStarted = true;
		UE_LOG(LogTemp, Warning, TEXT("Music Start!"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Music is nullptr"));
	}
	
}

// Called every frame
void ARhythmManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bStarted && AudioComponent && AudioComponent->IsPlaying())
	{
		CurrentMusicTime = GetWorld()->GetTimeSeconds() - StartTime;

		if (FMath::FloorToInt(CurrentMusicTime) != FMath::FloorToInt(PreviousTime))
		{
			UE_LOG(LogTemp, Warning, TEXT("Current Music Time:%f"), CurrentMusicTime);
		}

		PreviousTime = CurrentMusicTime;
	}
}

void ARhythmManager::StartRhythm()
{
	StartTime = GetWorld()->GetTimeSeconds();
	CurrentMusicTime = 0.0f;
	bStarted = true;

	UE_LOG(LogTemp, Warning, TEXT("Rhythm Started"));
}


void ARhythmManager::PlayNextHint()
{
	UE_LOG(LogTemp, Warning, TEXT("PlayNextHint Called"));
}
