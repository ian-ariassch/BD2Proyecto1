#ifndef REGISTRO_H
#define REGISTRO_H

#include <iostream>
#include <ctype.h>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

std::vector<std::string> parseoCSV(std::string line) {
  std::vector<std::string> parseo;
  while (line.find(";") != std::string::npos) {
    std::string column = line.substr(0, line.find(";"));
    parseo.push_back(column);
    line = line.substr(line.find(";")+1);
  }
  parseo.push_back(line);
  return parseo;
}

struct Registro{
  int id;
  std::string name;
  std::string sex;
  std::string age;
  std::string height;
  std::string weight;
  std::string team;
  std::string NOC;
  std::string game;
  std::string year;
  std::string season;
  std::string city;
  std::string sport;
  std::string event;
  std::string medal;
  Registro(){};
  Registro(std::vector<std::string> v){
    this->id=stoi(v[0]);
    this->name=v[1];
    this->sex=v[2];
    this->age=v[3];
    this->height=v[4];
    this->weight=v[5];
    this->team=v[6];
    this->NOC=v[7];
    this->game=v[8];
    this->year=v[9];
    this->season=v[10];
    this->city=v[11];
    this->sport=v[12];
    this->event=v[13];
    this->medal=v[14];
  }
  void crearRegistro(std::vector<std::string> v){
    this->id=stoi(v[0]);
    this->name=v[1];
    this->sex=v[2];
    this->age=v[3];
    this->height=v[4];
    this->weight=v[5];
    this->team=v[6];
    this->NOC=v[7];
    this->game=v[8];
    this->year=v[9];
    this->season=v[10];
    this->city=v[11];
    this->sport=v[12];
    this->event=v[13];
    this->medal=v[14];
  }
  friend std::istream& operator>>(std::istream& is, Registro& obj){
    string str;
    getline(is,str);
    if(str==""){
      return is;
    }
    vector<string> v=parseoCSV(str);
    obj.crearRegistro(v);
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, Registro& obj) {
    os<<obj.id<<";"<<obj.name<<";"<<obj.sex
    <<";"<<obj.age<<";"<<obj.height<<";"<<obj.weight
    <<";"<<obj.team<<";"<<obj.NOC<<";"<<obj.game<<";"
    <<obj.year<<";"<<obj.season<<";"<<obj.city<<";"
    <<obj.sport<<";"<<obj.event<<";"<<obj.medal<<endl;
    return os;
  }
  void mostrar(){
    cout<<"Id: "<<id<<endl;
    cout<<"Nombre: "<<name<<endl;
    cout<<"Sex: "<<sex<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Height: "<<height<<endl;
    cout<<"Weight: "<<weight<<endl;
    cout<<"Team: "<<team<<endl;
    cout<<"NOC: "<<NOC<<endl;
    cout<<"Game: "<<game<<endl;
    cout<<"Year: "<<year<<endl;
    cout<<"Season: "<<season<<endl;
    cout<<"City: "<<city<<endl;
    cout<<"Sport: "<<sport<<endl;
    cout<<"Event: "<<event<<endl;
    cout<<"Medal: "<<medal<<endl;
  }
};

#endif
