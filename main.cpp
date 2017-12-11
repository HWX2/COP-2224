/* 
Bull/Cow Game 
AUTHORS: Brendon Hales, Hayden White
Chipola College
Class: COP 2224
Fall Semester, 2017
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintInstructions();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // represents a new game

// the entry point for the application 
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PrintInstructions();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	
	return 0; // exit the application
}


// introduce the game
void PrintIntro()
{
	std::cout << "\n     Welcome to Bulls and Cows! This is a fun guessing game!" << std::endl;
	std::cout << std::endl;
	std::cout << "                   }_____{       ___ " << std::endl;
	std::cout << "                   /(o o)       (o o)\\ " << std::endl;
	std::cout << "        /---------/  \\_/         \\_/  \\----------\\ " << std::endl;
	std::cout << "       / |  BULL  |O                 O|   COW   | \\ " << std::endl;
	std::cout << "      *  |-,------|                   |---------|  * " << std::endl;
	std::cout << "         ^        ^                   ^         ^ " << std::endl;
	std::cout << std::endl;
	std::cout << "     Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram that I am thinking of?" << std::endl;
	std::cout << std::endl;
	
	return;
}

// instructions for the game
void PrintInstructions()
{
	std::cout << "     How to play: " << std::endl;
	std::cout << "     What is an isogram?   An isogram is a word that has 0 repeating letters.\n";
	std::cout << "     What is a BULL?       A BULL means that a letter is correct, ";
	std::cout << " and in the correct position. " << std::endl;
	std::cout << "     What is a COW?        A COW means that a letter is correct,";
	std::cout << " but is not in the correct position.\n\n";
	std::cout << "     The number of BULLS or COWS corresponds to";
	std::cout << " the number of letters that fall into those categories.\n";
	std::cout << "     If a letter does not fall into the BULL or COW category,";
	std::cout << " then that letter is incorrect.\n\n\n";
	std::cout << "     You will have " << BCGame.GetMaxTries() << " turns to guess the correct word.\n\n";
	
	return;

}

// gameplay
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	
	// loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); // check for valid guess

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "                 BULLS = " << BullCowCount.Bulls;
		std::cout << " COWS = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

// loop continually until user gives a valid guess
FText GetValidGuess() 
{	
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "     Turn " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "     Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "     Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "     Please remove all uppercase letters and re-try with all lowercase.\n\n";
			break;
		default: // assume the guess is valid
			break;
		}
	} 
	while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "     Do you want to play again with the same word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "     WELL DONE     -     YOU WON!\n";
	}
	else
	{
		std::cout << "     YOU LOST!     -     BETTER LUCK NEXT TIME!\n";
	}
}
