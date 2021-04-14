#include<iostream>
#include<thread>
#include <unistd.h>
#include<semaphore.h>
using namespace std;

class task
{
  sem_t table;
  sem_t a;
  sem_t b;
  sem_t c;
  char mats[3] = {'a','b','c'};
  int i=0;

  void smoker_a()
  {
    while(true)
    {
    sem_wait(&a);
    cout<<"A is smoking\n";
    sleep(2);
    sem_post(&table);
    }
  }

  void smoker_b()
  {
    
    while(true)
    {
    
    sem_wait(&b);
    cout<<"B is smoking\n";
    sleep(2);
    sem_post(&table);
    }
  }

  void smoker_c()
  {
    while(true)
    {
    sem_wait(&c);
    cout<<"C is smoking\n";
    sleep(2);
    sem_post(&table);
    }
  }

  void dealer_d()
  {
    while(true)
    {
    sem_wait(&table);
    if(mats[i%3]=='a') {sem_post(&a);}
    else if(mats[i%3]=='b') {sem_post(&b);}
    else {sem_post(&c);}
    i++;
    }
  }

  public:
  task()
  {
    sem_init(&table,0,1);
    sem_init(&a,0,0);
    sem_init(&b,0,0);
    sem_init(&c,0,0);

    thread d(&task::dealer_d, this);
    thread a(&task::smoker_a, this);
    thread b(&task::smoker_b, this);
    thread c(&task::smoker_c, this);
    d.join();
  }
};

int main()
{
  task a;
}