// Fill out your copyright notice in the Description page of Project Settings.


#include "RhythmManager.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ARhythmManager::ARhythmManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	RootComponent = AudioComponent;

}

// Called when the game starts or when spawned
void ARhythmManager::BeginPlay() // 게임시작,음악 재생,리듬 시스템 시작
{
	Super::BeginPlay();

	ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (Player)
	{
		TArray<UChildActorComponent*> ChildComps;
		Player->GetComponents<UChildActorComponent>(ChildComps);

		for (UChildActorComponent* ChildComp : ChildComps)
		{
			if (!ChildComp)
			{
				continue;
			}

			AActor* ChildActor = ChildComp->GetChildActor();

			if (ChildActor && ChildActor->GetClass()->GetName().Contains(TEXT("BP_RhythmCircle")))
			{
				RhythmCircleActor = ChildActor;
				UE_LOG(LogTemp, Warning, TEXT("Found RhythmCircle"));
				break;
			}
		}
	}

	if (Music)
	{
		AudioComponent->SetSound(Music);
		AudioComponent->Play();

		StartRhythm();

		UE_LOG(LogTemp, Warning, TEXT("Music Start!"));
	}
}

// Called every frame
void ARhythmManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bStarted) 
		return;

	CurrentMusicTime = GetWorld()->GetTimeSeconds() - StartTime;
	float BeatInterval = 60.0f / BPM;
	int CurrentBeat = FMath::FloorToInt(CurrentMusicTime / BeatInterval);
	int PreviousBeat = FMath::FloorToInt(PreviousTime / BeatInterval);

	if (CurrentState == ERhythmState::Preview)
	{
		
		if (CurrentBeat != PreviousBeat)
		{
			PlayNextHint();
		}
	}
	PreviousTime = CurrentMusicTime;
}


void ARhythmManager::StartRhythm()//랜덤 색 패턴 생성, 프리뷰(힌트 출력) 상태로 전환
{
	StartTime = GetWorld()->GetTimeSeconds();
	CurrentMusicTime = 0.0f;
	bStarted = true;

	HintIndex = 0;
	PlayerInputIndex = 0;
	HintPattern.Empty();

	for (int i = 0; i < PatternLength; i++)
	{
		int Random = FMath::RandRange(0, 2);
		HintPattern.Add((ERhythmColor)Random);
	}

	CurrentState = ERhythmState::Preview;

	UE_LOG(LogTemp, Warning, TEXT("Rhythm Started-Preview"));
}

// playnexthint 함수 현재는 로그만 출력, 여기서 발밑 파동 색 출력하면 돼,다음 힌트 색 출력, 모든 힌트 출력하면 플레이 상태로 변경

void ARhythmManager::PlayNextHint()
{
	if (HintIndex >= HintPattern.Num())
	{
		CurrentState = ERhythmState::Playing;

		UE_LOG(LogTemp, Warning, TEXT("Player Turn"));

		return;
	}

	ERhythmColor Color = HintPattern[HintIndex];

	if (RhythmCircleActor)
	{
		UFunction* Function = RhythmCircleActor->FindFunction(TEXT("PlayPulse"));

		if (Function)
		{
			struct FPlayPulseParams
			{
				FLinearColor NewColor;
			};

			FPlayPulseParams Params;
			Params.NewColor = GetLinearColorFromRhythmColor(Color);

			RhythmCircleActor->ProcessEvent(Function, &Params);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Hint %d : %d"), HintIndex, (int32)Color);
	HintIndex++;
}


bool ARhythmManager::IsOnBeat() const//현재 음악 박자 허용 범위 안에 있는지 검사
{
	float BeatInterval = 60.0f / BPM;

	float NearestBeat = FMath::RoundToFloat(CurrentMusicTime / BeatInterval) * BeatInterval;

	return FMath::Abs(CurrentMusicTime - NearestBeat) <= HitWindow;
}

//상호작용한 오브젝트의 색을 interactedColor로 전달해 호출함
void ARhythmManager::CheckInteraction(ERhythmColor InteractedColor)//플레이어가 e키로 상호작용 했을 대 호출, 전달 받은 색과 현재 정답 색,타이밍 비교하여 성공/실패 판정
{
	if (CurrentState != ERhythmState::Playing)
		return;
	if (PlayerInputIndex >= HintPattern.Num())
		return;

	bool bColor = HintPattern[PlayerInputIndex] == InteractedColor;

	bool bTiming = IsOnBeat();

	if (bColor && bTiming)
	{
		UE_LOG(LogTemp, Warning, TEXT("Success"));
		PlayerInputIndex++;
		if (PlayerInputIndex >= HintPattern.Num())
		{
			UE_LOG(LogTemp, Warning, TEXT("Stage Clear"));
		}
	}

	else
	{
		UE_LOG(LogTemp, Error, TEXT("Fail"));
	}
}

FLinearColor ARhythmManager::GetLinearColorFromRhythmColor(ERhythmColor Color) const
{
	switch (Color)
	{
	case ERhythmColor::Red:
		return FLinearColor::Red;

	case ERhythmColor::Yellow:
		return FLinearColor::Yellow;

	case ERhythmColor::Blue:
		return FLinearColor::Blue;

	default:
		return FLinearColor::White;
	}
}
