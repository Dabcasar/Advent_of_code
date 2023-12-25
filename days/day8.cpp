#include <iostream>
#include <vector>
#include <fstream>
#include <tuple>
#include <algorithm>
#include <string>
#include <map>
#include <queue>

std::tuple<std::string,std::string,std::string> parseLine(std::string line){
    size_t equalIndex = line.find('=');
    size_t openBracketIndex = line.find('(');
    size_t closeBracketIndex = line.find(')');
    size_t commaIndex = line.find(',');

    std::string sourceNode = line.substr(0,equalIndex-1);
    std::string leftNode = line.substr(openBracketIndex+1,commaIndex - openBracketIndex-1);
    std::string rightNode = line.substr(commaIndex+2,closeBracketIndex - commaIndex-2);
    

    // std::cout << sourceNode << '\n';
    // std::cout << leftNode << '\n';
    // std::cout << rightNode << '\n';
    
    return std::make_tuple(sourceNode,leftNode,rightNode);
}

void part_1(std::map<std::string,std::tuple<std::string,std::string>>& adjacencyMap, std::string& directions){
    int steps = 0;
    int directionIndex = 0;

    std::string currentNode = "AAA";

    while(currentNode != "ZZZ"){
        steps++;
        if(directionIndex >= directions.length()){
            directionIndex = 0;
        }

        bool left = directions.at(directionIndex) == 'L';
        directionIndex++;
        auto vertex = adjacencyMap[currentNode];

        if(left){
            currentNode = std::get<0>(vertex);
        }else{
            currentNode = std::get<1>(vertex);
        }
    }


    std::cout << "PART 1 ANSWER " << steps << '\n';
}

void part_2(std::map<std::string,std::tuple<std::string,std::string>>& adjacencyMap, std::string& directions){
    std::queue<std::string> queue;

    for(const auto& pair: adjacencyMap){
        auto source = pair.first;
        if(source.at(source.length() - 1) == 'A'){
            queue.push(source);
        }
    }

    int steps = 0;
    int directionIndex = 0;

    while(!queue.empty()){
        std::queue<std::string> tempQueue;

        int size=  queue.size();
        bool isLeft = directions.at(directionIndex++) == 'L';
        bool endState = true;
        for(int i = 0; i < size; i++){
            auto node = queue.front();
            std::cout << "This is node " << node << '\n';
            auto edge = adjacencyMap[node];

            if(node.at(node.length() - 1) != 'Z'){
                endState = false;
            }
            if(isLeft){
                tempQueue.push(std::get<0>(edge));
            }else{
                tempQueue.push(std::get<1>(edge));
            }
            queue.pop();
        }

        while(!tempQueue.empty()){
            queue.push(tempQueue.front());
            tempQueue.pop();
        }
        if(directionIndex >= directions.length()){
            directionIndex = 0;
        }
        if(endState){
            break;
        }
        steps++;
    }

    std::cout << "PART 2 ANSWER " << steps << '\n';
}


int main(){
    std::ifstream myFile ("day8input.txt");
    std::string line;
    
    getline(myFile,line);
    
    std::string directions = line;

    getline(myFile,line);

    
    std::map<std::string,std::tuple<std::string,std::string>> adjacencyMap;

    while(getline(myFile,line)){
        auto nodes = parseLine(line);
        std::string sourceNode = std::get<0>(nodes);
        std::string leftNode = std::get<1>(nodes);
        std::string rightNode = std::get<2>(nodes);

        adjacencyMap[sourceNode] = std::make_tuple(leftNode,rightNode);        
    }

    // part_1(adjacencyMap,directions);
    part_2(adjacencyMap,directions);

}