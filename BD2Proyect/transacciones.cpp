#include "hashIndex.h"
#include "parseTransaction.h"
#include <vector>
#include <mutex>
#include <thread>
#include <fstream>
#include <iostream>

using namespace std;
mutex mtx;
void consult(int id, int year, int transaccion,HashIndex index )
{
  mtx.lock();
  index.updateYear(id,year,transaccion);
  mtx.unlock();
};

void transaccion()
{
  ofstream answerQuery("../BD2Proyect/answerQuery.csv", ios::out | ofstream::trunc);
  if (answerQuery.is_open()) {
    ifstream origin("../BD2Proyect/athlete_events_clean.csv", ios::in);
    if (origin.is_open()) {
      string line;
      getline(origin, line);
      answerQuery << line << '\n';
      origin.close();
    }
    else {
      cerr << "Unable to open file\n";
    }
  answerQuery.close();
}else{
  cerr << "Unable to open file\n";
}
  string str="../BD2Proyect/nani.csv";
  string str2="../BD2Proyect/athlete_events_clean.csv";
  HashIndex index(str2,"../BD2Proyect/hashIndex.txt");
  vector<int> parseoTrans = parseoTrasaccion(); //year1 id year2
  thread t1(consult,parseoTrans[1],parseoTrans[0],1,index);
  thread t2(consult,parseoTrans[1], parseoTrans[2],2,index);

  t2.join();
  t1.join();

}
