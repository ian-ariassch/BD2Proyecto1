#include <vector>
#include <chrono>
#include "hashIndex.h"
#include "parseSql.h"
#include "randomIndex.cpp"

int bika() {
  std::string line;
  std::ifstream query("../BD2Proyecto1/BD2Proyect/query.txt", std::ios::in);
  if (query.is_open()) {
    std::getline(query, line);
    query.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
  std::vector<int> delimiters = parseoQuery(line);
  std::string str="../BD2Proyecto1/BD2Proyect/nani.csv";
  std::string str1="../BD2Proyecto1/BD2Proyect/athlete_events_clean.csv";
  std::string str2="../BD2Proyecto1/BD2Proyect/athlete_test.csv";
  RandomIndex random(str1,"../BD2Proyecto1/BD2Proyect/randomIndex.txt" );
  // HashIndex index(str1,"../BD2Proyecto1/BD2Proyect/hashIndex.txt");
  auto started = std::chrono::high_resolution_clock::now();
  // index.answerQuery(delimiters);
  random.searchRegisters(delimiters);
  auto done = std::chrono::high_resolution_clock::now();
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(done-started).count() << '\n';
  return 0;
}
