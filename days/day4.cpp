#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <cmath>
#include <map>
#include <stack>

std::map<int,int> getGameToMatches(const std::vector<std::string>& inputLines){
    std::map<int,int> gameToMatchesMap;

    for(int i =0; i < inputLines.size(); i++){
        const std::string& line = inputLines[i];
        int gameIndex = i+1;

        std::set<std::string> winningNumbers;
        int lineSize = line.size();
        int colonIndex = line.find(':');
        colonIndex++;

        while(line.at(colonIndex) == ' '){
            colonIndex++;
        }

        int lineIndex = colonIndex;
        while(lineIndex < lineSize && line.at(lineIndex) != '|'){
            char c = line.at(lineIndex);
            if(c == ' '){
                lineIndex++;
                continue;
            }
            std::string winningDigit;

            while(lineIndex < lineSize && isdigit(line.at(lineIndex))){
                winningDigit += line.at(lineIndex++);
            }
            winningNumbers.insert(winningDigit);
        }

        while(lineIndex < lineSize && (line.at(lineIndex) == '|' || line.at(lineIndex) == ' ')){
            lineIndex++;
        }

        int winningNumbersMatch = 0;
        while(lineIndex < line.size()){
            while(line.at(lineIndex) == ' '){
                lineIndex++;
                continue;
            }
            std::string myNumber;
            while(lineIndex < lineSize && isdigit(line.at(lineIndex))){
                myNumber += line.at(lineIndex++);
            }
            
            if(winningNumbers.find(myNumber) != winningNumbers.end()){
                winningNumbersMatch++;
            }
        }
        gameToMatchesMap[i+1] = winningNumbersMatch;
    }

    return gameToMatchesMap;
}


void part_2(std::vector<std::string>& inputLines){
    std::map<int,int> gamesToMatchingCards = getGameToMatches(inputLines); 

    int numberOfScrachCards = inputLines.size();
    std::stack<int> scratchCards;

    for(const auto& pair: gamesToMatchingCards){
        int game = pair.first;
        int matches = pair.second;

        for(int i = 1; i <= matches; i++){
            scratchCards.push(game + i);
        }
    }

    while(!scratchCards.empty()){
        int card = scratchCards.top();
        scratchCards.pop();
        numberOfScrachCards++;
        
        if(card == inputLines.size() + 1 || gamesToMatchingCards[card] == 0){
            continue;
        }
        int matches = gamesToMatchingCards[card];
        for(int i = 1; i <= matches; i++){
            scratchCards.push(card + i);
        }
    }

    std::cout << "PART 2 ANSWER " << numberOfScrachCards << '\n';
}


void part_1(std::vector<std::string>& inputLines){
    std::map<int,int> gamesToMatchingCards = getGameToMatches(inputLines); 
    
    int sum = 0;
    for(const auto& entry: gamesToMatchingCards){
        if(entry.second == 0){
            continue;
        }
        sum += static_cast<int>(pow(2,entry.second-1));
    }

    std::cout << "PART 1 ANSWER " + std::to_string(sum) << '\n';
}

int main(){
    std::ifstream myfile ("day4input.txt");

    std::vector<std::string> inputLines;
    std::string line;

    if(myfile.is_open()){
        while(getline(myfile,line)){
            inputLines.push_back(line);
        }
    }
    part_1(inputLines);
    part_2(inputLines);
}