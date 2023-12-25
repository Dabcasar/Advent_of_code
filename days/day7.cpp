#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <map>

std::vector<std::string> types = {"Five of a kind","Four of a kind","Full house","Three of a kind","Two pair","One pair","High Card"};

std::string getType(std::string& hand){
        std::map<char,int> handMap;
        bool fourOfAKind = false;
        bool threeOfAKind = false;
        for(char c : hand){
            if(handMap.find(c) == handMap.end()){
                handMap[c] = 0;
            }
            handMap[c] = handMap[c] + 1;

            if(handMap[c] == 3){
                threeOfAKind = true;
            }
            if(handMap[c] == 4){
                fourOfAKind = true;
            }
        }

        if(handMap.size() == 1){
            return types[0];
        }
        if(handMap.size() == 2 && fourOfAKind){
            return types[1];
        }else if(handMap.size() == 2){
            return types[2];
        }

        if(handMap.size() == 3 && threeOfAKind){
            return types[3];
        }else if(handMap.size() == 3){
            return types[4];
        }

        if(handMap.size() == hand.length()){
            return types[6];
        }

        return types[5];
}


bool part1Comp(std::tuple<std::string,int,std::string>& a,std::tuple<std::string,int,std::string>& b){
    std::string aType = getType(std::get<0>(a));
    std::string bType = getType(std::get<0>(b));

    if(aType != bType){
        int indexDiff = std::find(types.begin(),types.end(),bType) - std::find(types.begin(),types.end(),aType);
        return indexDiff < 0;
    }

    std::map<char,int> cards = {{'A',0},{'K',1},{'Q',2},{'J',3},{'T',4},{'9',5},{'8',6},{'7',7},{'6',8},
    {'5',9},{'4',10},{'3',11},{'2',12}};

    for(int i = 0; i < 5; i++){
        char aChar = std::get<0>(a).at(i);
        char bChar = std::get<0>(b).at(i);
        if(aChar == bChar){
            continue;
        }
        int diff = cards[bChar] - cards[aChar];
        return diff < 0;
    }

    return 0;
}

bool part2_comp(std::tuple<std::string,int,std::string>& a,std::tuple<std::string,int,std::string>& b){
    std::string aType = !std::get<2>(a).empty() ? getType(std::get<2>(a)) : getType(std::get<0>(a));
    std::string bType = !std::get<2>(b).empty() ? getType(std::get<2>(b)) : getType(std::get<0>(b));

    if(aType != bType){
        int indexDiff = std::find(types.begin(),types.end(),bType) - std::find(types.begin(),types.end(),aType);
        return indexDiff < 0;
    }

    std::map<char,int> cards = {{'A',0},{'K',1},{'Q',2},{'T',4},{'9',5},{'8',6},{'7',7},{'6',8},
    {'5',9},{'4',10},{'3',11},{'2',12},{'J',13}};

    for(int i = 0; i < 5; i++){
        char aChar = std::get<0>(a).at(i);
        char bChar = std::get<0>(b).at(i);
        if(aChar == bChar){
            continue;
        }
        int diff = cards[bChar] - cards[aChar];
        return diff < 0;
    }

    return 0;
}

void part_1(std::vector<std::tuple<std::string,int,std::string>>& inputList){
    std::sort(inputList.begin(),inputList.end(),part1Comp);

    int answer = 0;

    for(int i =0; i < inputList.size(); i++){
        answer += (i + 1) * std::get<1>(inputList[i]);
    }

    std::cout << "PART 1 ANSWER " << answer <<'\n';
}


void part_2(std::vector<std::tuple<std::string,int,std::string>>& inputList){
    
    for(int i =0; i < inputList.size(); i++){
        std::string& hand = std::get<0>(inputList.at(i));
        if (hand.find('J') == std::string::npos) {
            continue;
        }
        
        std::vector<int> jIndex;
        std::map<char,int> cardToFreq;
        char maximum = '.';
        int max = 0;

        for(int j = 0; j < hand.size(); j++){
            char c= hand.at(j);
            if(c=='J'){
                jIndex.push_back(j);
            }else{
                char c= hand.at(j);
                if(cardToFreq[c] == 0){
                    cardToFreq[c] = 0;
                }
                    
                cardToFreq[c] = cardToFreq[c] + 1;
                if(maximum == '.' || cardToFreq[c] > max){
                    max = cardToFreq[c];
                    maximum = c;
                }
            }
        }

        std::string modified = hand;
        for(int index: jIndex){
            modified[index] = maximum;
        }
        std::get<2>(inputList.at(i)) = modified;
    }
    
    
    std::sort(inputList.begin(),inputList.end(),part2_comp);

    int answer = 0;

    for(int i =0; i < inputList.size(); i++){
        answer += (i + 1) * std::get<1>(inputList[i]);
    }

    std::cout << "PART 2 ANSWER " << answer <<'\n';
}


int main(){
    std::ifstream myFile("day7input.txt");
    std::string line;

    std::vector<std::tuple<std::string,int,std::string>> inputList;

    if(myFile.is_open()){
        while(getline(myFile,line)){
            int lineIndex = 0;
            std::string hand;

            while(lineIndex < line.size() && line.at(lineIndex) != ' '){
                hand += line.at(lineIndex++);
            }
            lineIndex++;

            std::string digit;
              while(lineIndex < line.size()){
                digit += line.at(lineIndex++);
            }
            inputList.push_back(std::make_tuple(hand,stoi(digit),""));
        }
    }

    part_1(inputList);
    part_2(inputList);
}


