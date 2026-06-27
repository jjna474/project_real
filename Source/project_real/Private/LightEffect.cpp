// Fill out your copyright notice in the Description page of Project Settings.


#include "LightEffect.h"

// Sets default values
ALightEffect::ALightEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALightEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALightEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

