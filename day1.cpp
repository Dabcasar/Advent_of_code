// Your First C++ Program

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::string line;
    std::ifstream myfile("input.txt");

    vector<std::string> inputList;

    if(myfile.is_open()){
        while(getline(myfile,line)){
            inputList.push_back(line);
        }
    }
    myfile.close();

}
