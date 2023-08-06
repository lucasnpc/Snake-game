#ifndef SCORE_H
#define SCORE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#define printVariableNameAndValue(x) std::cout<<"The name of variable **"<<(#x)<<"** and the value of variable is => "<<x<<"\n"

class Score {
public:
    int getHighestScore();
    void saveScore(int score);
private:
    std::vector<int> _scores;
    const std::string filename = "../scores";
};

#endif