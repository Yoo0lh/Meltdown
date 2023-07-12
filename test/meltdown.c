#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

unsigned long long meltdown(unsigned long long address) {

  unsigned long long start_time, end_time;
  
  start_time = clock();
  usleep(0.1);
  end_time = clock();
  return (end_time - start_time);

}

int main() {
  
  unsigned long long address = 0xfb61b000; // the addres to be access
  unsigned long long time_taken;
  char *address_string = "0xfb61b000";
 
  time_taken = meltdown(address); //cach time
  printf("Time taken to access address %s: %llu \n",address_string, time_taken); 
  
  return 0;

}
