#ifndef PARSETRANSACTION
#define PARSETRANSACTION

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>

void createLogTransactionError(){
  std::ofstream logError("../BD2Proyect/logError.txt", std::ios::out);
  if (logError.is_open()) {
    logError << "Syntax error\n";
    logError << "transacciones aceptadas\n";
    logError << "update olimpicos set year = ... where id = ...\n";
    logError.close();
  }
}

void deleteLogTransactionError() {
  remove("../BD2Proyect/logError.txt");
}

std::vector<std::string> getStringComponentsTransaction(std::string line, std::string  delimiter = " ") {
  std::vector<std::string> parseo;
  while (line.find(delimiter) != std::string::npos) {
    std::string column = line.substr(0, line.find(delimiter));
    parseo.push_back(column);
    line = line.substr(line.find(delimiter)+1);
  }
  if (!line.empty()) {
    std::string column = line.substr(0, line.find(delimiter));
    parseo.push_back(column);
  }
  return parseo;
}

void refreshTransactionAnswer() {
  std::ifstream origin("../BD2Proyect/athlete_events_clean.csv", std::ios::in);
  if (origin.is_open()) {
    std::string line;
    std::ofstream refreshed("../BD2Proyect/answerQuery.csv", std::ios::out);
    while (std::getline(origin, line)) {
      if (refreshed.is_open()) {
        refreshed << line << '\n';
      }
    }
    refreshed.close();
    origin.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
}

std::vector<int> parseoTrasaccion() {
  std::string line1;
  std::ifstream afile("../BD2Proyect/T1.txt", std::ios::in);
  if (afile.is_open()) {
    std::getline(afile, line1);
    afile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  std::string line2;
  std::ifstream bfile("../BD2Proyect/T2.txt", std::ios::in);
  if (bfile.is_open()) {
    std::getline(bfile, line2);
    bfile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  
  std::vector<std::string> transaccion1 = getStringComponentsTransaction(line1);
  std::vector<std::string> transaccion2 = getStringComponentsTransaction(line2);
  std::vector<int> delimiters = {std::stoi(transaccion1[5]), std::stoi(transaccion1[9]), std::stoi(transaccion2[5])}; //year1 id year 2
  return delimiters;
}

#endif
