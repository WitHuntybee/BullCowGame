/* The game logic. BullCowGame is a simple game where a player
has to guess an isogram (a word that only no repeating letters)
and only has a finite amount of tries.
*/
#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <ctime> 
#include <algorithm>
#include <map>
// to make the syntax Unreal friendly.
#define TMap std::map

// to make the syntax Unreal friendly.
using FString = std::string;
using int32 = int;

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
