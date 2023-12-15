// Your First C++ Program

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void part_1(std::vector<std::string> inputList){
     int sum = 0;
    for(unsigned int i = 0; i < inputList.size(); i++){
        std::string word = inputList[i];
        std::string digits = "";
        for (char c: word){
            if(isdigit(c)){
               digits += c;
            }
        }
        std::string val = std::string(1,digits.at(0)) + std::string(1,digits.at(digits.size() - 1));
        sum += stoi(val);

    }

    std::cout << "PART 1 ANSWER " << sum +'\n';
}

void part_2(std::vector<std::string> inputList){
   
   std::map<std::string, std::string> numberMap = {
        {"one", "1"},
        {"two", "2"},
        {"three", "3"},
        {"four", "4"},
        {"five", "5"},
        {"six", "6"},
        {"seven", "7"},
        {"eight", "8"},
        {"nine", "9"}
    };
    
    int sum = 0;
    for(unsigned i = 0; i < inputList.size(); i++){
        std::string word = inputList[i];
        std::string digits = "";
        for(int j = 0; j < word.length(); j++){
            char c = word.at(j);
            if(isdigit(c)){
                digits += c;
                continue;
            }
           
            for (const auto& pair : numberMap) {
                std::string num_string = pair.first;
                if(word.size() - j < num_string.size()){
                    continue;
                }
                
                if(word.substr(j,num_string.size() ).compare(num_string) == 0){
                    digits += pair.second;
                    j += (pair.first.size() - 1);
                    break;
                }
            }
        }
        

        std::string val = std::string(1,digits.at(0)) + std::string(1,digits.at(digits.size() - 1));
        std::cout << val << '\n';
        sum += stoi(val);
    }

    std::cout << sum << '\n';
}

int main() {
    std::string line;
    std::ifstream myfile("day1input.txt");

    std::vector<std::string> inputList;

    if(myfile.is_open()){
        while(getline(myfile,line)){
            inputList.push_back(line);
        }
    }
    myfile.close();
    

    part_1(inputList);
    part_2(inputList);

    
}

