#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

bool isSymbol(char c){
    return !isdigit(c) && c != '.';
}

bool isAdjacentToSymbol(std::vector<std::string> line, int row, int col){
    
    int  directions [8][2] = {
        {0,1},{0,-1},{1,0},{-1,0},
        {1,1},{-1,-1},{1,-1},{-1,1}
    };

    for(const int (&dir)[2] : directions){
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if(newRow < 0 || newRow >= line.size() || newCol < 0 || newCol >= line[newRow].size()){
            continue;
        }
        if(isSymbol(line[newRow].at(newCol))){
            return true;
        }
    }

    return false;
}


std::string getGearIndex(std::vector<std::string> line, int row, int col){
    
    int  directions [8][2] = {
        {0,1},{0,-1},{1,0},{-1,0},
        {1,1},{-1,-1},{1,-1},{-1,1}
    };

    for(const int (&dir)[2] : directions){
        int newRow = row + dir[0];
        int newCol = col + dir[1];
        if(newRow < 0 || newRow >= line.size() || newCol < 0 || newCol >= line[newRow].size()){
            continue;
        }
        if(isSymbol(line[newRow].at(newCol))){
            return std::to_string(newRow) + "->" + std::to_string(newCol);
        }
    }

    return "";
}

void part_1(std::vector<std::string> inputLines){
    int sum = 0;
    
    for(int i = 0; i < inputLines.size(); i++){
        std::string line = inputLines[i];

        int line_index = 0;
        while(line_index < line.size()){
            char c = line[line_index];
            if(!isdigit(c)){
                line_index++;
                continue;
            }
            bool symbolAdjacentToNumber = false;
            std::string num;
            while(line_index < line.size() && isdigit(line[line_index])){
                num += line[line_index];
                if(isAdjacentToSymbol(inputLines,i,line_index)){
                    symbolAdjacentToNumber = true;
                }
                line_index++;
            }
            if(symbolAdjacentToNumber){
                sum += stoi(num);
            }
        }
    }
    std::cout << "PART 1 Answer " << std::to_string(sum) << '\n';
}

void part_2(std::vector<std::string> inputLines){
    std::map<std::string,std::vector<int>> gearToAdjacentNumbersMap;
    
    for(int i = 0; i < inputLines.size(); i++){
        std::string line = inputLines[i];

        int line_index = 0;
        while(line_index < line.size()){
            char c = line[line_index];
            if(!isdigit(c)){
                line_index++;
                continue;
            }
            bool symbolAdjacentToNumber = false;
            std::string gearIndex;
            std::string num;
            while(line_index < line.size() && isdigit(line[line_index])){
                num += line[line_index];
                if(isAdjacentToSymbol(inputLines,i,line_index)){
                    gearIndex = getGearIndex(inputLines,i,line_index);
                }
                line_index++;
            }

            if(gearIndex == ""){
                continue;
            }

            if(gearToAdjacentNumbersMap.find(gearIndex) == gearToAdjacentNumbersMap.end()){
                gearToAdjacentNumbersMap[gearIndex] = std::vector<int>();
            }

            gearToAdjacentNumbersMap[gearIndex].push_back(stoi(num));
        }
    }

    int sum = 0;

    for(const auto& pair: gearToAdjacentNumbersMap){
        if(pair.second.size() <= 1){
            continue;
        }
        int gear_ratio = 1;
        for(int digit: pair.second){
            gear_ratio *= digit;
        }
        sum += gear_ratio;
    }

    std::cout << "PART 2 Answer " << std::to_string(sum) << '\n';
}



int main(){
    std::fstream myfile("day3input.txt");
    std::string line;
    std::vector<std::string> inputLines;


    if(myfile.is_open()){
        while(getline(myfile,line)){
            inputLines.push_back(line);
        }
    }

    part_1(inputLines);
    part_2(inputLines);

    return 0;
}