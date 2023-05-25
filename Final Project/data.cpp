#include "data.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>
#include <iomanip>

void getAirports(std::string inputFile, std::string outputFile){
    std::ifstream ifs{inputFile};
    std::ofstream ofs{outputFile};

    std::string line, word;
    std::vector<std::string> row;
    if(ifs.is_open() && ofs.is_open()){
        while(!ifs.eof()){
            row.clear();
            getline(ifs, line);
            std::stringstream s(line);
            if(line.empty()) continue;
            getline(s,word, '"');
            getline(s,word, '"');
            word.erase(std::remove(word.begin(), word.end(), ','), word.end());
            row.push_back(word);
            getline(s,word,',');
            getline(s,word, '"');
            getline(s,word, '"');
            word.erase(std::remove(word.begin(), word.end(), ','), word.end());
            row.push_back(word);
            getline(s,word,',');
            while(getline(s, word, ',')){
                row.push_back(word);
            }
            //0 Name 2 Country 3 IATA 5 Latitude 6 Longitude
            if(row[3] != "\\N"){
                ofs << row[0] << ',' << row[2] << ',' << row[3] << ',' << row[5] << ',' << row[6] << std::endl;
            }

        }
    }else{
        std::cout << "Error opening files" << std::endl;
    }
    ifs.close();
    ofs.close();
}

void getRoutes(std::string inputFile, std::string outputFile){
    std::ifstream ifs{inputFile};
    std::ofstream ofs{outputFile};


    std::string line, word;
    std::vector<std::string> row;
    if(ifs.is_open() && ofs.is_open()){
        while(!ifs.eof()){
            row.clear();
            getline(ifs, line);
            std::stringstream s(line);
            if(line.empty()) continue;
            while(getline(s, word, ',')){
                row.push_back(word);
            }
            //source destination
            if(row[2] != "\\N" && row[4] != "\\N"){
                ofs << row[2] << ',' << row[4] << std::endl;
            }
        }
    }else{
        std::cout << "Error opening files" << std::endl;
    }
    ifs.close();
    ofs.close();
}