#ifndef PARSESQL
#define PARSESQL

#include <vector>
#include <string>
#include <iostream>
#include <limits.h>
#include <stdio.h>
#include <fstream>

void createLogError(){
  std::ofstream logError("logError.txt", std::ios::out);
  if (logError.is_open()) {
    logError << "Syntax error\n";
    logError << "Consultas aceptadas:\n";
    logError << "select * from olimpicos where id > ...\n";
    logError << "select * from olimpicos where id >= ...\n";
    logError << "select * from olimpicos where id <= ...\n";
    logError << "select * from olimpicos where id < ...\n";
    logError << "select * from olimpicos where id = ...\n";
    logError.close();
  }
}

void deleteLogError() {
  remove("logError.txt");
}

std::vector<std::string> getStringComponents(std::string line, std::string  delimiter = " ") {
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

void refreshAnswer() {
  std::ifstream origin("athlete_events_clean.csv", std::ios::in);
  if (origin.is_open()) {
    std::string line;
    std::ofstream refreshed("answerQuery.csv", std::ios::out);
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

std::vector<int> parseoQuery(std::string line) {
  std::vector<std::string> aceptedQueries = {
  "select", "*", "from", "olimpicos", "where", "id"
  };
  std::vector<int> delimiters = {-1, -1};
  int posString = 0;
  std::vector<std::string> parseo = getStringComponents(line);
  if (parseo.size() == 0) {
    refreshAnswer();
    return delimiters;
  }
  for (; posString < aceptedQueries.size(); posString++) {
    if (aceptedQueries[posString] != parseo[posString]) {
      createLogError();
      return delimiters;
    }
    deleteLogError();
  }
  if (parseo[posString] == "<=") {
    posString++;
    delimiters[0] = 1;
    delimiters[1] = std::stoi(parseo[posString]);
  } else if (parseo[posString] == "<") {
    posString++;
    delimiters[0] = 1;
    delimiters[1] = std::stoi(parseo[posString]) - 1;
  } else if (parseo[posString] == ">=") {
    posString++;
    delimiters[0] = std::stoi(parseo[posString]);
    delimiters[1] = INT_MAX;
  } else if (parseo[posString] == ">") {
    posString++;
    delimiters[0] = std::stoi(parseo[posString]) + 1;
    delimiters[1] = INT_MAX;
  } else if (parseo[posString] == "=") {
    posString++;
    delimiters[0] = std::stoi(parseo[posString]);
    delimiters[1] = std::stoi(parseo[posString]);
  }
  return delimiters;
}

#endif
