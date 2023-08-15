#ifndef SCORE_H
#define SCORE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Score {
public:
    int getHighestScore();
    void saveScore(int score);
private:
    std::vector<int> _scores;
    const std::string filename = "../scores";
};

#endif