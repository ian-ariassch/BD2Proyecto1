#include <map>
#include <string>
#include "registro.h"

using namespace std;

class RandomIndex{
  string fileName;
  string indexName;
  std::map<int, int> index;
public:
  RandomIndex(string _filename, string _fileindex){
    this->fileName=_filename;
    this->indexName=_fileindex;
    if(!isIndexCreated(indexName)){
      std::cout<<"no existe el indice, creandolo"<<std::endl;
      createIndex();
    }
    else{
      loadIndex();
    }
    showIndex();
  }
  void loadIndex(){
    ifstream file (indexName, ios::in | ios::binary);
    while(!file.eof()){
        int recordkey,pos;
        file.read((char*)&recordkey,sizeof(int));
        file.read((char*)&pos,sizeof(int));
        if(recordkey==0 && pos==0)
          continue;
        index.insert(pair<int,int>(recordkey,pos));
    }
    file.close();
  }
  void createIndex(){
    ifstream file (fileName, ios::in );
    string str;
    int pos;
    std::vector<int> v;
    std::vector<string> registro;
    getline(file,str);
    pos=file.tellg();

    while(getline(file,str)){
      v.push_back(pos);
      registro=parseoCSV(str);
      index.insert(pair<int,int>(stoi(registro[0]),pos));
      pos=file.tellg();
    }
    file.close();
    file.open(fileName);
    for(auto item:index){
      file.seekg(item.second);
      getline(file,str);
      cout<<str<<endl;
    }
    file.close();
  }

  void add(Registro *registro){
    if(index.find(registro->id)!=index.end())
      return;
    ofstream myfile(fileName,  ios::app);

    int pos=myfile.tellp();
    myfile<<*registro;
    myfile.close();
    index.insert(pair<int,int>(registro->id,pos));
  };

  void showIndex(){
    for(auto item:index){
        cout<<item.first<<" "<<item.second<<endl;
    }
  };

  bool searchRegisters(vector<int> enteros){
    if (enteros[0] == -1) {
      return false;
    }
    Registro* registro;
    ofstream output("../BD2Proyecto1/BD2Proyect/answerQuery.csv", ios::out);
    std::ifstream origin("../BD2Proyecto1/BD2Proyect/athlete_events_clean.csv", std::ios::in);
    if (origin.is_open()) {
      std::string line;
      std::getline(origin, line);
      output << line << '\n';
      origin.close();
    }
    else {
      std::cerr << "Unable to open file\n";
    }
    if(enteros[0]==enteros[1]){
      registro = buscar(enteros[0]);
      output << *registro;
      delete registro;
    }
    else{
      for(int i= enteros[0]; i <= enteros[1]; ++i){
        if (index.find(i) == index.end()) {
          break;
        }
        registro=buscar(i);
        output << *registro;
        delete registro;
      }
    }
    output.close();
    return true;
  }

  Registro* buscar(int codigo){
    Registro * registro=new Registro();
    ifstream file (fileName, ios::in);
    file.seekg(index[codigo]);
    file>>*registro;
    file.close();
    //registro->mostrar();
    return registro;
  }
  bool isIndexCreated(std::string fileName){
    std::ifstream infile(fileName);
    bool abierto=infile.good();
    infile.close();
    return  abierto;
  }
  ~RandomIndex(){
    ofstream myindex(indexName, ios::binary);
    for(auto item:index){
      myindex.write((const char*)&item.first,sizeof(int));
      myindex.write((const char*)&item.second,sizeof(int));
    }
    myindex.close();
  }
};
