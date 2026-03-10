#ifndef SCOREBOARD_FILE_H 
#define SCOREBOARD_FILE_H

#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <iostream>

using namespace std;


void saveFullScoreToFile(const string& filename, const string& name, int score, int streak) {

    map<string, pair<int, int>> data;
    
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            string savedName;
            int savedScore, savedStreak;
            
            if (iss >> savedName >> savedScore >> savedStreak) {
                data[savedName] = {savedScore, savedStreak};
            }
        }
        inFile.close();
    }
    

    if (data.find(name) != data.end()) {

        if (score > data[name].first) {
            data[name] = {score, streak};
        }
    } else {
        data[name] = {score, streak};
    }
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open file for writing!" << endl;
        return;
    }
    
    for (const auto& pair : data) {
        outFile << pair.first << " " 
                << pair.second.first << " " 
                << pair.second.second << endl;
    }
    
    outFile.close();
    //cout << "Score saved: " << name << " " << score << " " << streak << endl;
}

#endif