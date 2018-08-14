#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime> 
#include <algorithm>

using FString = std::string;
using int32 = int;

/*All values initialized to 0*/
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public: 
	//constructor
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	FString GetHiddenWord() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	
	EGuessStatus CheckGuessValidity(FString);

	void SetCurrentTry(int32);
	void SetHiddenWord(FString);

	void GenerateNewWord();
	void Reset();
	
	FBullCowCount SubmitValidGuess(FString);
	

private: 
	int32 CurrentTry;
	int32 MaxTries;
	int32 HiddenWordLength;
	FString HiddenWord;
	FString WordList[49056];
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
