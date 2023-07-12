#include <iostream>
#include <vector>
#include <ctime>

int main (){
  int i = 0; 
  std::vector <int> data;
   data = {1,2,3,4,5,6,7,8,9} ;
  for (i = 0 ; i < 20  ; i++){
    if (i < data.size ()){
      clock_t start = clock();
      std::cout << data[i] << " :time:" ;
      clock_t end = clock ();
      std::cout << std::scientific << std::fixed << static_cast<double>(end - start) / CLOCKS_PER_SEC << std::endl;
    }
  }
  return 0;
}
