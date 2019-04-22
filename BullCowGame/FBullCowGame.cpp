#pragma once

#include "FBullCowGame.h"
#include <map>

// To make syntax unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // Default constructor

int32 FBullCowGame::GetCurrentTry() const {	return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,7}, {5, 9} };

	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset() {

	const FString HIDDEN_WORD = "davos"; // This must be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms
	if(Word.length() <= 1) { return true; }

	// create hash table
	TMap<char, bool> LetterSeen;
	// iterate over word
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		// if letter has been seen before
		if (LetterSeen[Letter])
		{
			return false; // we DO NOT have an isogram
		}
		else
		// if letter has not been seen before
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; // for example when escape character /0 is entered
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	if (Word.length() < 1) { return true; }

	TMap<char, bool> LetterLowercase;

	for (auto Letter : Word)
	{

		if (islower(Letter))
		{
			// if letter is lowercase set map to true
			LetterLowercase[Letter] = true;
		}
		else
		{
			// if not lowercase return false
			return false;
		}
	}

	// if all letters are lowercase return true
	return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))	//if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments try number and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = GetHiddenWordLength(); //assuming same length as guess

	// loop through all letters in the guess
	for (int32 HWCount = 0; HWCount < WordLength; HWCount++)
	{
		for (int32 GWCount = 0; GWCount < WordLength; GWCount++)
		{
			if (Guess[GWCount] == MyHiddenWord[HWCount])
			{
				if(GWCount == HWCount)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	bGameIsWon = BullCowCount.Bulls == WordLength ? true : false;

	return BullCowCount;
}
