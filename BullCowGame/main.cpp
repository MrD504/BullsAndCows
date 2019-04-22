#pragma once

/*	This is the console executable, that makes use of the BullCow Class
	This acts ad the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// alias to make more like Unreal Engine syntax
using FText = std::string;
using int32 = int;


// Function prototypes as outside class
FText GetValidGuess();
void IntroduceGame();
void PlayGame();
void SummariseGame();
bool AskToPlayAgain();
FBullCowGame BCGame;

int main()
{
	bool PlayAgain = true;
	do {
		IntroduceGame();
		PlayGame();
		PlayAgain = AskToPlayAgain();

		if (PlayAgain) {
			BCGame.Reset();
		}
	} while (PlayAgain);
	
	return 0;
}

void IntroduceGame()
{
	std::cout << std::endl << std::endl << "Welcome to Bulls and Cows, a fun word game." << std::endl;
	
	// Insert ASCII art
	std::cout << "   (__)          __       " << std::endl;
	std::cout << "  ~ O O ~      ~ O O ~    " << std::endl;
	std::cout << "  ( ^ ^ )      ( ^ ^ )    " << std::endl;
	std::cout << std::endl;
	std::cout << "      BULLS AND COWS      " << std::endl;
	std::cout << std::endl;
	// end of ASCII ART
	
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?" << std::endl;
	std::cout << "You have " << BCGame.GetMaxTries() << " guesses" << std::endl;
	std::cout << std::endl;

	return;
}

FText GetValidGuess() // loop continually until the user gives a valid guess
{
	EGuessStatus Status = EGuessStatus::Invalid_Status; // initialise outside of loop due to scope
	FText Guess = "";

	do {

		std::cout << "Try: "<< BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess" << std::endl ;
		std::getline (std::cin,Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Word is not an isogram, repeating letters detected" << std::endl << std::endl;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase" << std::endl << std::endl;
			break;
		default:
			break;
		}
		
	} while (Status != EGuessStatus::OK); // keep looping until no errors
	
	return Guess;

}

// Plays a single game to completion
void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	FText word = BCGame.GetWord();

	// Loop for the number of turns asking for guess
	
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) 
	{
		FText Guess = GetValidGuess(); 
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls << ", Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}

	SummariseGame();
	
	return;
}

void SummariseGame()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Congratulations your guess: " << BCGame.GetWord() << " matches what I was thinking of" << std::endl;
	}
	else
	{
		std::cout << "Sorry you have failed to guess the word. Thanks for playing. GAME OVER" << std::endl;
	}

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again using the same word?" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}
