// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    isogram = GetValidWords(Names);
    initGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    
    if (bGameOver) {
        ClearScreen();
        initGame();
    }
    else {
        processGuess(Input);
    }
}

void UBullCowCartridge::initGame()
{
    HiddenWord = isogram[FMath::RandRange(0,isogram.Num()-1)];
    lives=HiddenWord.Len() * 2;
    bGameOver = false;
    PrintLine(TEXT("Hello Traveller, Got a moment to spare.\nPlay our little 'BULLS AND COWS' Game."));
    PrintLine(FString::Printf(TEXT("You have %i lives"), lives));
    // PrintLine(TEXT("answer: %s"), *HiddenWord); // Debug line
}

void UBullCowCartridge::endGame()
{
    PrintLine(TEXT("Press Enter to play again."));
    PrintLine(TEXT("The hiddenword was %s."), *HiddenWord);
    bGameOver = true;
}

void UBullCowCartridge::processGuess(FString Guess)
{
    // If game Won 
    if (Guess == HiddenWord) {
        // print the player won
        PrintLine("WON");
        endGame();
        return;
    }
    // if Answer is not a isogram
    if (!isIsogram(Guess))
    {
        PrintLine("No repeating characters.\n try again.");
    }
    // isogram not of specified length
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Please use appropriate word length.\n"));
        return;
    }
    // life counts
    if (lives <= 0) {
        endGame();
        return;
    }
    // show bulls and cows
    int32 bulls=0;
    int32 cows=0;
    FCattleCount count = GetBullCow(Guess);
    PrintLine(TEXT("Bulls-> %i"), count.Bulls);
    PrintLine(TEXT("Cows -> %i"),count.Cows);
    PrintLine(TEXT("try guessing again. You have %i lives left"), --lives);
}

bool UBullCowCartridge::isIsogram(const FString& Guess) const
{
    FString guess = Guess.ToLower();
    int16 alp[26] = { 0 };
    for (int16 i = 0; i < guess.Len(); i++)
    {
        alp[Guess[i] - 'a'] = alp[guess[i] - 'a'] + 1;
    }
    for (int16 i = 0; i < 26; i++)
    {
        if (alp[i] >= 2) return false;
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& Names) const
{
    TArray<FString> valid;
    for(FString word:Names)
    {
        if(word.Len() >= 4 && word.Len() <= 8 && isIsogram(word))
        {
            valid.Emplace(word);
        }
    }
    return valid;
}

FCattleCount UBullCowCartridge::GetBullCow(const FString& guess) const
{
    FCattleCount count;
    // increment bulls when character is at same place as in answer
    // Time Complexity -> O(n^2)
    for(int i=0;i<guess.Len();i++)
    {
        // bulls count
        if(guess[i] == HiddenWord[i])
        {
            count.Bulls++;
            continue;
        }
        // cows count
        for(int32 j=0; j<guess.Len() ;j++)
        {
            if(guess[i] == HiddenWord[j] && i!=j)
            {
                count.Cows++;
                break;
            }
        }
    }
    // increment cows when same character appears elsewhere in answer
    return count;
}