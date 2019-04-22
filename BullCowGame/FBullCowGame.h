#pragma once
#include<string>

//To make syntax unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,

};

class FBullCowGame 
{
	
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetWord() const;

	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	
	void Reset(); 
	FBullCowCount SubmitValidGuess(FString Guess);
private:
	// see contructor for initialisation
	int32 MyCurrentTry;
	bool bGameIsWon;
	FString MyHiddenWord = "";
	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};
