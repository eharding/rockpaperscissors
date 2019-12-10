#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#pragma once


bool Evaluate(char Input, std::vector<std::string>& Feedback, int& Lives);
char TakeInput(std::vector<std::string>& Feedback, int& PlayCount, int Lives, int Score);
int Play(int& PlayCount);
int Menu();
void LoadScore(std::vector<std::string>& names, std::vector<int>& scores);
void CheckScore(int Score, std::vector<std::string>& names, std::vector<int>& scores);
void PrintScore(std::vector<std::string> names, std::vector<int> scores);
void SaveScore(std::vector<std::string> names, std::vector<int> scores);

