#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame()
{
	MaxTries = 50;
	CurrentTry = 1;
	HiddenWord = "planet";
	std::srand(time(NULL));

	std::ifstream InputFile;
	InputFile.open("isograms.txt");

	// outputs an error and exits the game if the InputFile is non-existent.
	if (!InputFile)
	{
		std::cout << "ERROR! InputFile not found!";
		exit(1);
	}
	// adds the words from the input file into an array.
	for (int i = 0; i < 49056; i++)
	{
		getline(InputFile, WordList[i]);
	}

	// sorts the newly constructed array alphabetically.
	std::sort(WordList, WordList+49056);
}


int32 FBullCowGame::GetCurrentTry() const { return CurrentTry; }
FString FBullCowGame::GetHiddenWord() const { return HiddenWord; }
int32 FBullCowGame::GetHiddenWordLength() const { return HiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 6}, {4, 8}, {5, 10}, {6, 14}, {7, 17},
	{8, 20}, {9, 25}, {10, 30} };
	return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

/*Determines whether a string has any uppercase letters.*/
bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

/* check if the WordToCheck is an isogram by checking if 
any letters occur more than once.*/
bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter] == true)
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

void FBullCowGame::SetCurrentTry(int32 SetTry) { CurrentTry = SetTry; }
void FBullCowGame::SetHiddenWord(FString word) { HiddenWord = word; }

/*Pulls a new word from the array WordList in the event of a new game.*/
void FBullCowGame::GenerateNewWord() 
{ 
	FString NewWord = WordList[rand() % (49056-0 + 1) + 0];
	// std::cout << NewWord << std::endl;
	SetHiddenWord(NewWord); 
}

void FBullCowGame::Reset()
{
	SetCurrentTry(1);
	GenerateNewWord();
	bGameIsWon = false;
	std::cout << "Can you guess the " << GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}
/*Checks for valid guesses by calling the appropriate functions.*/
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

/*receives a valid guess, increments turn, and returns count.*/
FBullCowCount FBullCowGame::SubmitValidGuess(FString ValidGuess)
{
	FBullCowCount BullCowCount;

	// loop through all the letters by comparing the guess
	// and hidden words letters.
	for (int32 i = 0; i < HiddenWord.length(); i++)
	{
		for (int32 j = 0; j < HiddenWord.length(); j++)
		{
			if (ValidGuess[i] == HiddenWord[j] && i == j)
			{
				BullCowCount.Bulls++;
			} 
			else if (ValidGuess[i] == HiddenWord[j] && i != j)
			{
				BullCowCount.Cows++;
			}
		}
	}
	// determines whether game is won or not
	// and if is not then increments try.
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{ 
		bGameIsWon = true;
	}
	else
	{ 
		bGameIsWon = false;
		CurrentTry++;
	}

	return BullCowCount;
}