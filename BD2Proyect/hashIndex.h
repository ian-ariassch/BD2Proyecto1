#ifndef HASH_H
#define HASH_H

#include <map>
#include <bitset>
#include <math.h>
#include <stdio.h>
#include <string>
#include "bucket.h"

const int maxElements=100;

class HashIndex{
  std::string fileName;
  std::string indexName;
  Bucket* bucket;
  int depth;
  int nIndex;
  int maxElementos;
  std::map<int,Bucket*> hash;
public:

  HashIndex(std::string _filename, std::string fileindex){
    this->maxElementos=maxElements;
    this->depth=d;
    this->nIndex=pow(2,depth);
    this->fileName=_filename;
    this->indexName=fileindex;
    if(!isIndexCreated(fileindex)){
      std::cout<<"no existe el indice, creandolo"<<std::endl;
      createIndex();
    }
    else{
      loadIndex();
    }
    showIndex();
  }
  HashIndex(){};

  void createIndex(){
    std::string str;
    createMap();
    Registro* registro;
    std::ifstream file (fileName, std::ios::in | std::ios::binary);
    getline(file,str);
    std::vector<string> v;
    while(!file.eof()){
        getline(file,str);
        if(str==""){
          break;
        }
        v=parseoCSV(str);
        registro=new Registro(v);
        registro->mostrar();
        this->addRegistro(registro);
    }
    file.close();
  }
  void loadIndex(){
    string str;
    createMap();
    ifstream file (indexName, ios::in);
    int i,turn=1;
    while(getline(file, str)){
      if(turn>0){
        i=stoi(str);
      }
      else{
        bucket=new Bucket(str);
        hash[i]=bucket;
      }
      turn=turn*-1;
    }
    file.close();
  }
  void showIndex(){
    for(auto item:hash){
      cout<<item.first<<": ";
      item.second->mostrar();
    }
  }
  int hashFunction(int id){
    return id%nIndex;
  };
  void createMap(){
    for(int i=0;i<nIndex;++i){
      hash.insert(std::pair<int,Bucket*>(i,nullptr));
    }
  }

  void addRegistro(Registro* registro){
    int i=hashFunction(registro->id);
    bucket=hash[i];
    if(bucket==nullptr){
      std::string binary = std::bitset<1>(i).to_string();
      cout<<binary<<endl;
      std::cout<<endl;
      bucket=new Bucket(maxElements,1,binary);
      bucket->addRegister(registro);
      reorganizeIndex(bucket);
      return;
    }/*
    else if(bucket->find(registro)){
      std::cout<<"here2"<<endl;
      return;
    }*/
    else if(bucket->isFullBucket() && bucket->ableSplit(depth)){
      splitBuckets(i,registro);
      return;
    }
    else{
      bucket->addRegister(registro);
    }
  }

  bool isIndexCreated(std::string fileName){
    std::ifstream infile(fileName);
    bool abierto=infile.good();
    infile.close();
    return  abierto;
  }

  void splitBuckets(int index, Registro* registro){
    bucket=hash[index];
    std::string str,newName1,newName2,file;
    std::vector<Registro*> registers=bucket->getRegistros();
    registers.push_back(registro);
    int newD=bucket->dActual+1;
    newName1="0"+bucket->name;
    newName2="1"+bucket->name;
    file=bucket->File;
    if( remove(file.c_str( )) != 0 )
      perror( "Error deleting file" );
    Bucket* newbucket1=new Bucket(maxElements,newD,newName1);
    Bucket* newbucket2=new Bucket(maxElements,newD,newName2);
    delete bucket;
    reorganizeIndex(newbucket1);
    reorganizeIndex(newbucket2);
    for(auto item:registers){
      int i=hashFunction(item->id);
      bucket=hash[i];
      bucket->addRegister(item);
    }
    for(auto item:registers){
      delete item;
    }
    registers.clear();
  }
  void reorganizeIndex(Bucket* newbucket){
    std::string str;
    for(int i=0;i<nIndex;i++){
      str=std::bitset<d>(i).to_string();
      if(str.substr( str.length() - newbucket->dActual ) == newbucket->name){
        cout<<newbucket->name<<endl;
        hash[i]=newbucket;
      }
    }
  }

  bool answerQuery(std::vector<int> delimiters){
    if (delimiters[0] == -1) {
      return false;
    }
    std::ofstream answerQuery("answerQuery.csv", std::ios::out);
    if (answerQuery.is_open()) {
      std::ifstream origin("athlete_events_clean.csv", std::ios::in);
      if (origin.is_open()) {
        std::string line;
        std::getline(origin, line);
        answerQuery << line << '\n';
        origin.close();
      }
      else {
        std::cerr << "Unable to open file\n";
      }
      for (size_t registroBucket = delimiters[0]; registroBucket <= delimiters[1]; registroBucket++) {
        std::vector<Registro*> bucketRegistros = (this->hash[hashFunction(registroBucket)])->getRegistros();
        bool maxSizeReached = false;
        for (size_t registro = 0; registro < bucketRegistros.size(); registro++) {
          if (bucketRegistros[registro]->id == registroBucket) {
            answerQuery << *bucketRegistros[registro];
            maxSizeReached = false;
            break;
          }else{
            maxSizeReached = true;
          }
        }
        for(auto item:bucketRegistros){
          delete item;
        }
        bucketRegistros.clear();
        if (maxSizeReached) {
          break;
        }
      }
      answerQuery.close();
      return true;
    }
  }

  ~HashIndex(){
    ofstream myindex(indexName);
    for(auto item:hash){
      myindex<<item.first<<endl;
      myindex<<*item.second;
    }
    myindex.close();
  }
};


#endif
