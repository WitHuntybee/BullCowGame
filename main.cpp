/* This is the console executable, that makes use of the BullCow class.
This acts as the view in an MVC pattern, and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

FBullCowGame BCGame;
bool bStillPlaying;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();



/*What runs during the application.*/
int main()
{
	PrintIntro();
	do
	{
		PlayGame();
		bStillPlaying = AskToPlayAgain();
	} while (bStillPlaying);

	return 0;
}

/*Handles the game mechanics, the function that holds the game together.*/
void PlayGame()
{
	std::cout << "You have " << BCGame.GetMaxTries() << " attempts" << std::endl;

	// looping asking for guesses while the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries())
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

/*prompts the player about playing again*/
bool AskToPlayAgain()
{
	FText Answer = "";
	std::cout << "Do you want to play again?: ";
	getline(std::cin, Answer);

	std::cout << "\n";

	if ((Answer[0] == 'y') || (Answer[0] == 'Y'))
		BCGame.Reset();

	return ((Answer[0] == 'y') || (Answer[0] == 'Y'));
}

/*Introduce the game.*/
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl << std::endl;
}

/*Prints a simple summary at the end of the game.*/
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Well done - You won in " << BCGame.GetCurrentTry() << " tries!\n";
	}
	else
	{
		std::cout << "Sorry, you lost. You'll get it next time!\n";
	}
}

/*Prompts the user to enter a guess and returns that guess.*/
FText GetValidGuess()
{
	FText Guess;
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do // asks player to enter their guess and submit it if it is valid.
	{
		std::cout << "Try #" << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries();;
		std::cout << ". Enter your guess: ";
		getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a valid isogram (a word without repeating letters).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in all lowercase.\n\n";
			break;
		default:
			break;
		}
		
	} while (Status != EGuessStatus::OK);

	return Guess;
}