#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

int buffer[100];
int count=0;
sem_t full, empty, lock;

void* producer(void* args)
{
  while(true)
  {
    sem_wait(&empty);

    int p=(rand()%100)+1;
    sem_wait(&lock);
    buffer[count]=p;
    std::cout<<"added "<<p<<" at "<<count<<"\n";
    count++;
    sem_post(&lock);

    sem_post(&full);
  }
  return NULL;
}

void* consumer(void* args)
{
  while(true)
  {
    sem_wait(&full);

    sem_wait(&lock);
    std::cout<<"recieved "<<buffer[count-1]<<" from "<<count-1<<"\n";
    count--;
    sem_post(&lock);

    sem_post(&empty);
  }
  return NULL;
}

int main()
{
  srand(time(NULL));
  pthread_t prod, cons;

  sem_init(&full, 0, 0);
  sem_init(&empty, 0, 100);
  sem_init(&lock, 0, 1);

  pthread_create(&prod, NULL, &producer, NULL);
  pthread_create(&cons, NULL, &consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);
}