#include "score.h"

int Score::getHighestScore() {
    std::string line;
    int n;
    std::ifstream stream(filename);
    if (stream.is_open())
    {
        while (std::getline(stream, line))
        {
            std::istringstream linestream(line);
            while (linestream >> n)
            {
                _scores.emplace_back(n);
            }
        }
        stream.close();
    }
    
    int higherScore = *std::max_element(_scores.begin(), _scores.end());
    return higherScore;
}

void Score::saveScore(int score) {
    std::fstream stream(filename, std::ios::app);
    if (stream.is_open())
    {
        stream << score << "\n";
    }
    stream.close();
}