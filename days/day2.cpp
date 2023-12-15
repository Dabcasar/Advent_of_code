#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

int getSubGameIndex(const auto& game){
    for(int i = 0; i < game.length(); i++){
        if(game[i] == ':'){
            return i;
        }
    }
    return -1;
}

std::vector<std::string> splitString(const auto& game_string, char delimter){
    std::vector<std::string> result;

    int start = 0;
    int end = game_string.find(delimter);

    while(end != std::string::npos){
        result.push_back(game_string.substr(start,end - start));
        start = end + 1;
        while(game_string[start] == ' '){
            start++;
        }
        end = game_string.find(delimter, start);
    }
    result.push_back(game_string.substr(start,end - start));

    for(std::string s : result){
        std::cout << s << '\n';
    }
    
    return result;
}


void part_1(std::vector<std::string> inputList){
    int answer = 0;
    std::string red = "red";
    std::string green = "green";
    std::string blue = "blue";

    std::map<std::string,int> colourmap = {
        {red, 12},
        {green, 13},
        {blue, 14}
    };

    for(const auto& game: inputList){
        std::istringstream iss(game);
        std::string game_string;

        getline(iss,game_string,':');

        int size = game_string.size();
        
        std::string game_id = game_string.substr(5);
        int colonIndex = getSubGameIndex(game);
        iss.clear();

        std::vector<std::string> game_set = splitString(game.substr(colonIndex + 2), ';');
        bool goodID = true;

        for(std::string set: game_set){
            int green_count = 0;
            int red_count = 0;
            int blue_count = 0;

            std::vector<std::string> splitOnCommas = splitString(set,',');
            for(std::string numberAndColour: splitOnCommas){
                std::vector<std::string> numberAndColourSplit = splitString(numberAndColour,' ');
                int val = stoi(numberAndColourSplit[0]);
                std::string colour = numberAndColourSplit[1];
                if(colour == green){
                    green_count += val;
                }else if(colour == red){
                    red_count += val;
                }else{
                    blue_count += val;
                }
            }
            if(green_count > colourmap[green] || red_count > colourmap[red] || blue_count > colourmap[blue]){
                goodID = false;
            }
        }

        if(goodID){
            answer += stoi(game_id);
        }
    }
        
    std::cout << "PART 1 ANSWER " << answer;
}

void part_2(std::vector<std::string> inputList){
    int answer = 0;
    std::string red = "red";
    std::string green = "green";
    std::string blue = "blue";

    std::map<std::string,int> colourmap = {
        {red, 12},
        {green, 13},
        {blue, 14}
    };

    for(const auto& game: inputList){
        std::istringstream iss(game);
        std::string game_string;

        getline(iss,game_string,':');

        int size = game_string.size();
        
        std::string game_id = game_string.substr(5);
        int colonIndex = getSubGameIndex(game);
        iss.clear();

        std::vector<std::string> game_set = splitString(game.substr(colonIndex + 2), ';');
        bool goodID = true;
        
        int min_green = 0;
        int min_red = 0;
        int min_blue = 0;

        for(std::string set: game_set){
            int green_count = 0;
            int red_count = 0;
            int blue_count = 0;

            std::vector<std::string> splitOnCommas = splitString(set,',');
            for(std::string numberAndColour: splitOnCommas){
                std::vector<std::string> numberAndColourSplit = splitString(numberAndColour,' ');
                int val = stoi(numberAndColourSplit[0]);
                std::string colour = numberAndColourSplit[1];
                if(colour == green){
                    green_count += val;
                }else if(colour == red){
                    red_count += val;
                }else{
                    blue_count += val;
                }
                min_blue = std::max(min_blue,blue_count);
                min_green = std::max(min_green,green_count);
                min_red = std::max(min_red,red_count);
            }
            
        }

       answer += (min_blue * min_green * min_red);
    }
        
    std::cout << "PART 2 ANSWER " << answer;
}



int main(){
    std::string line;
    std::ifstream myfile("day2input.txt");

    std::vector<std::string> inputList;

    if(myfile.is_open()){
        while(getline(myfile,line)){
            inputList.push_back(line);
        }
    }
    
    part_1(inputList);
    part_2(inputList);

}

