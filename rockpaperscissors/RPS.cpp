#include "RPS.h"

int main() {

	srand(time(NULL));  // random seed for the game's picks
	int Score = Menu();

	std::vector<std::string>names;
	std::vector<int>scores;
	LoadScore(names, scores);
	CheckScore(Score, names, scores);
	PrintScore(names, scores);
	SaveScore(names, scores);
	system("pause");
	return 0;
}

bool Evaluate(char Input, std::vector<std::string>& Feedback, int& Lives) {
	bool Result = false; // Whether or not you won the play. initialized to 'no'
	int AIGuess = rand() % 3 + 1;  // the computer guesses. added 1 because i don't like counting from 0
	Feedback.clear(); // clear the feedback vector before the match evaluates

	// setting up the player's pick results and putting them in a vector for callback
	if (Input == 'r') { Feedback.push_back("You chose Rock!"); }
	else if (Input == 's') { Feedback.push_back("You chose Scissors!"); }
	else if (Input == 'p') { Feedback.push_back("You chose Paper!"); }

	// if the computer guessed rock
	if (AIGuess == 1) {
		Feedback.push_back("  the Computer chose Rock!");
		switch (Input) {
		case 'p': { Result = true; Feedback.push_back("  You win!\n"); } break;
		case 'r': { Feedback.push_back("  Tie!\n"); } break;
		case 's': { Feedback.push_back("  You Lose!\n"); --Lives; } break;
		}
	}
	// if the computer guessed paper
	else if (AIGuess == 2) {
		Feedback.push_back("  the Computer chose Paper!");
		switch (Input) {
		case 's': { Result = true; Feedback.push_back("  You win!\n"); } break;
		case 'p': { Feedback.push_back("  Tie!\n"); } break;
		case 'r': { Feedback.push_back("  You Lose!\n"); --Lives; } break;
		}
	}
	// if the computer guessed scissors
	else if (AIGuess == 3) {
		Feedback.push_back("  the Computer chose Scissors!");
		switch (Input) {
		case 'r': { Result = true; Feedback.push_back("  You win!\n");} break;
		case 's': { Feedback.push_back("  Tie!\n"); } break;
		case 'p': { Feedback.push_back("  You Lose!\n"); --Lives; } break;
		}
	}
		// returns true only if the player won
		return Result;
	}


char TakeInput(std::vector<std::string>& Feedback, int& PlayCount, int Lives, int Score) {
	char Input = '0';
	// take player input and discard invalid entries
	while (Input != 'r' && Input != 'p' && Input != 's' && Input != 'x') {
		for (int i = 0; i < Feedback.size(); ++i){	std::cout << Feedback[i];}
		std::cout << "Number of games: " << PlayCount << "\nScore: " << Score << "\n" << "Lives Left: " << Lives << "\n";
		std::cout << "[r]ock, [p]aper, [s]cissors, shoot!\n Press x to exit\n";
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin >> Input;
		if (Input != 'r' && Input != 'p' && Input != 's' && Input != 'x') { system("CLS");  }
	}
	return Input;
}

int Play(int& PlayCount) {
	//initialize the game for round 1
	char Output = '0';
	std::vector<std::string>Feedback;
	Feedback.push_back("The Computer awaits your turn\n");
	int Score = 0;
	int Lives = 10;
	std::cout << "Number of games: " << PlayCount << "\nScore: " << Score << "\n";
	//gameplay loop. runs until you're out of lives
	while (Lives > 0) {
		system("CLS");
		Output = TakeInput(Feedback, PlayCount, Lives, Score);
		if (Output == 'x') { break; }
		++PlayCount;
		if (Evaluate(Output, Feedback, Lives)) { ++Score; };
	}
	return Score;
}


int Menu() {
	system("CLS");
	//initialization of score and playcount to 0
	int Score = 0;
	int PlayCount = 0;

	//menu to discard invalid data and start the game or view the leaderboard
	char MenuOption = '3';

	while (MenuOption != '1' && MenuOption != '2') {
		system("CLS");
		std::cout << "What would you like to do?\n[1]Play\n[2]View High Scores\n";
		std::cin >> MenuOption;
	}
	if (MenuOption == '1') {Score = Play(PlayCount); }
	if (MenuOption == '2') { return 0; }

	//post game feedback
	std::cout << "\n\nYour final score was " << Score << "\nYour Game Count was " << PlayCount << "\nGood Game!\n\n";
	return Score;
}

void LoadScore(std::vector<std::string>& names, std::vector<int>& scores) {
	//standard file reading program to extract the leaderboard names and scores

	//helper variables to put the file contents into local vectors
	std::string Name;
	std::string scorestring; // this one for the string to int function
	int BoardScores;


	std::ifstream board("Leaderboardnames.txt");
	if (board.is_open()) {
		while (std::getline(board, Name)) {
			names.push_back(Name);		}
		board.close();
	}
	else { std::cout << "Leaderboard unreadable or initializing\n"; }

	std::ifstream board2("Leaderboardscore.txt");
	if (board2.is_open()) {
		while (std::getline(board2, scorestring)) 
		{
			BoardScores = std::stoi(scorestring); // string to int necessary for comparators
			scores.push_back(BoardScores);
		}
		board2.close();
	}
	else { std::cout << "Scoresheet unreadable or initializing\n"; }

	//if the score sheet is invalid, clear it
	if (scores.size() != names.size()) { scores.clear(); names.clear(); }

	//populate the board with blank entries if necessary
	while (scores.size() < 10 ) {
		BoardScores = 0;
		Name = "none";
		scores.push_back(BoardScores);
		names.push_back(Name);
	}
}

void CheckScore(int Score, std::vector<std::string>& names, std::vector<int>& scores) {

	//function initialization. 2 iterators and a blank string for player name input
	std::vector<int>::iterator it = scores.begin();
	std::vector<std::string>::iterator it2 = names.begin();
	std::string Name = " ";

	// check each score starting from the top. if a player has a higher score
	// insert their name and score in the same position for each list,
	// then break the loop so it doesn't replace everything else
	for (int i = 0; i < scores.size(); ++i, ++it, ++it2)
	{
		if (Score > scores[i]) {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "What is your name?\n";
			std::getline(std::cin, Name);
			scores.emplace(it, Score);
			names.emplace(it2, Name);
			break;
		}
	}
	// make sure no more than 10 entries are on either list
	while (scores.size() > 10) { scores.pop_back(); }
	while (names.size() > 10) { names.pop_back(); }
}

void PrintScore(std::vector<std::string> names, std::vector<int> scores) {

	//initialize a format helper to place spaces between names and scores
	//results in two neat collumns
	int formathelper = 0;
	std::cout << "\n\n\n     HIGH SCORES\n";
	for (int i = 0; i < names.size(); ++i)
	{
		formathelper = 20; // may need to change for longer names. 20 was arbitrary
		formathelper -= names[i].length();
		if (scores[i] / 10 >= 1) { formathelper -= 1; } // will have formatting issues if the player scores over 100. seems unlikely
		std::cout << names[i];
		while (formathelper > 1) { std::cout << " "; --formathelper; }
		std::cout << scores[i] << "\n";
	}
	std::cout << "\n\n";
}

void SaveScore(std::vector<std::string> names, std::vector<int> scores) {
	//standard ofstream functions to create/overwrite 2 separate score sheets
	//named Leaderboardnames and Leaderboardscores in the base directory
	std::ofstream board3("Leaderboardnames.txt");
	if (board3.is_open())
	{
		for (int i = 0; i <= names.size() - 1; ++i) { board3 << names[i] << "\n"; }
		board3.close();
	}
	else { "leaderboard cannot be written to"; }

	std::ofstream board4("Leaderboardscore.txt");
	if (board4.is_open())
	{
		for (int i = 0; i <= scores.size() - 1; ++i) { board4 << scores[i] << "\n"; }
		board4.close();
	}
	else { "scoreboard cannot be written to"; }
}