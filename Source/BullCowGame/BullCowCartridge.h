// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"
struct FCattleCount{
	int32 Bulls = 0;
	int32 Cows = 0;
};
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()
	
	public:
	virtual void BeginPlay() override;
	virtual void OnInput(const FString& Input) override;
	void initGame();
	void endGame();
	void processGuess(FString Guess);
	bool isIsogram(const FString& Guess) const;
	TArray<FString> GetValidWords(const TArray<FString>&) const;
	FCattleCount GetBullCow(const FString&) const;
	// Your declarations go below!
	private:
	FString HiddenWord;
	int32 lives;
	bool bGameOver;
	TArray<FString> isogram;
};
