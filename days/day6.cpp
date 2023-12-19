#include <iostream>
#include <fstream>
#include <vector>
#include <utility> 

std::pair<long long, long long> makePair(std::vector<int>& timeVector, std::vector<int>& distanceVector){
    std::string timeString;
    std::string distanceString;

    for(int i =0 ; i < timeVector.size(); i++){
        timeString += std::to_string(timeVector[i]);
        distanceString += std::to_string(distanceVector[i]);
    }

    long long time = stoll(timeString);
    long long distance = stoll(distanceString);

    return std::make_pair(time,distance);
}

void part_1(std::vector<int>& timeVector, std::vector<int>& distanceVector){
    int ans = 1;

    for(int i =0 ; i < timeVector.size(); i++){
        int time = timeVector[i];
        int distance = distanceVector[i];
        int numberOfWays = 0;

        for(int j = 1; j < time; j++){
            int remainingTime = time - j;
            int distanceTravelled = remainingTime * j;
            if(distanceTravelled > distance){
                numberOfWays++;
            }
        }
        ans *= numberOfWays;
    }
    std::cout << "PART 1 ANSWER " << ans << '\n';
}

void part_2(std::pair<long long, long long> pair){
    long long time = pair.first;
    long long distance = pair.second;
    long long ans = 0;

    for(long long j = 0; j <= time; j++){
        long long remainingTime = time - j;
        long long distanceTravelled = remainingTime * j;
        if(distanceTravelled > distance){
            ans++;
        }
    }
    
    std::cout << "PART 2 ANSWER " << ans << '\n';
}



void addLineToVector(std::vector<int>& vec, std::string& line){
    int lineIndex = 0;
    int size = line.size();
    while(lineIndex < size && !isdigit(line.at(lineIndex))){
        lineIndex++;
    }

    while(lineIndex < size){
        while(lineIndex < size && !isdigit(line.at(lineIndex))){
            lineIndex++;
            continue;
        }
        std::string digit;
        while(lineIndex < size && isdigit(line.at(lineIndex))){
            digit += line.at(lineIndex++);
        }
        vec.push_back(stoi(digit));
    }
}

int main(){
    std::ifstream myFile("day6input.txt");
    std::string line;

    std::vector<int> timeVector;
    std::vector<int> distanceVector;
    if(myFile.is_open()){
        getline(myFile,line);
        addLineToVector(timeVector,line);
        getline(myFile,line);
        addLineToVector(distanceVector,line);
    }

    part_1(timeVector,distanceVector);
    part_2(makePair(timeVector,distanceVector));
}

