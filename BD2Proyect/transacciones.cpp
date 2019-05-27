#include <iostream>
#include <mutex>
#include <thread>
#include <fstream>

using namespace std;
string x = "\"C\"";
mutex mtx;
void T1(string line1)
{
  mtx.lock();
  x = line1;
  mtx.unlock();
  mtx.lock();
  cout<<"T1: "<<x<<endl;
  mtx.unlock();
};
void T2(string line2)
{
  mtx.lock();
  cout<<"T2: "<<x<<endl;
  mtx.unlock();
  mtx.lock();
  x = line2;
  mtx.unlock();

};
int main()
{
  ifstream tran1("T1.txt");
  ifstream tran2("T2.txt");
  string line1;
  string line2;
  for(int i=0; i<3;i++)tran1 >> line1;
  for(int i=0; i<3;i++)tran2 >> line2;
  cout<<line1<<endl;
  cout<<line2<<endl;
  thread t2(T2, line2);
  thread t1(T1,line1);


  t2.join();
  t1.join();

}
