// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "RhythmManager.generated.h"

UENUM(BlueprintType)
enum class ERhythmColor : uint8
{
	Red UMETA(DisplayName="Red"),
	Yellow UMETA(DisplayName="Yellow"),
	Blue UMETA(DisplayName="Blue")
};

UENUM(BlueprintType)
enum class ERhythmState :uint8
{
	Idle UMETA(DisplayName="Idle"),//아직 시작 전
	Preview UMETA(DisplayName="Preview"),//정답 패턴 보여주는 시간
	Playing UMETA(DisplayName="Playing")//플레이어가 상호작용 하는 시간
};

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHintColor, ERhythmColor, InColor);

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

	//UPROPERTY(BlueprintAssignable, Category = "Rhythm")
	//FOnHintColor OnHintColor;


	UFUNCTION(BlueprintCallable, Category = "Rhythm")
	void StartRhythm();

	UFUNCTION(BlueprintCallable,Category="Rhythm")
	void CheckInteraction(ERhythmColor InteractedColor);

private:
	UPROPERTY(EditAnywhere,Category="Rhythm")
	USoundBase* Music;

	UPROPERTY(VisibleAnywhere,Category="Rhythm")
	UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere,Category="Rhythm")
	ERhythmState CurrentState = ERhythmState::Idle;

	UPROPERTY(EditAnywhere,Category="Rhythm")
	int32 PatternLength = 5;

	UPROPERTY(EditAnywhere,Category="Rhythm")
	float HitWindow = 0.2f;

	float StartTime = 0.0f;
	bool bStarted = false;

	int HintIndex = 0;
	int32 PlayerInputIndex = 0;
	TArray<ERhythmColor> HintPattern;

	float PreviousTime = 0.0f;

	void PlayNextHint();
	bool IsOnBeat() const;

	UPROPERTY()
	AActor* RhythmCircleActor = nullptr;

	FLinearColor GetLinearColorFromRhythmColor(ERhythmColor Color) const;

};
