#ifndef BUCKET_H
#define BUCKET_H

#include <vector>
#include "registro.h"

const std::string path="../BD2Proyecto1/BD2Proyect/buckets/";
const int d=7;
struct Bucket{
  int elementosMax;
  int nRegistros;
  int dActual;
  std::string name;
  std::string File;
  bool overflow;

  Bucket(int ele, int d,std::string name){
    this->elementosMax=ele;
    this->dActual=d;
    this->nRegistros=0;
    this->name=name;
    this->overflow=false;
    this->File=path+name+".dat";
  }
  Bucket(){};
  Bucket(std::string str){
    istringstream is(str);
    is>>elementosMax>>nRegistros>>dActual>>name>>File>>overflow;
  }
  bool isFullBucket(){
    return overflow;
  }
  void verifyOverflow(){
    if(nRegistros>=elementosMax)
      this->overflow=true;
    else
      this->overflow=false;
  }
  void addRegister(Registro* registro){
    std::ofstream myfile(File, std::ios::binary | std::ios::app);
    myfile<<*registro;
    myfile.close();
    nRegistros++;
    verifyOverflow();
  }
  bool find(Registro* registro){
    std::vector<Registro*> registers=getRegistros();
    for(auto item:registers){
      if(item->id==registro->id){
        return true;
      }
    }
    return false;
  }
  bool ableSplit(int d){
    if(dActual<d){
      return true;
    }
    return false;
  }
  std::vector<Registro*> getRegistros(){
    Registro* registro;
    std::vector<Registro*> registers;
    std::ifstream file (File, std::ios::in | std::ios::binary);
    while(!file.eof()){
        registro=new Registro();
        file>>*registro;
        registers.push_back(registro);
    }
    registers.pop_back();
    file.close();
    return registers;
  }
  friend std::ostream& operator<<(std::ostream& os, Bucket& obj) {
    os<<obj.elementosMax<<" "<<obj.nRegistros<<" "<<obj.dActual<<" "<<obj.name<<" "<<obj.File<<" "<<obj.overflow<<endl;
    return os;
  }
  void mostrar(){
    cout<<elementosMax<<" "<<nRegistros<<" "<<dActual<<" "<<name<<" "<<File<<" "<<overflow<<endl;
  }
};

#endif
