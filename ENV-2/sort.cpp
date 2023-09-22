#include <iostream>
#include <vector>
// Function template for performing bubble sort on a vector of generic type U
template <class U>
void bubblesort(std::vector<U>& arr,int N)
{
// Bubble Sort Algorithm
for(int i=0;i<N-1;++i){
  for(int j=0;j<N-i-1;++j){
      if(arr[j].absolutevalue()>arr[j + 1].absolutevalue()){
          // Swap the elements if they are out of order
          std::swap(arr[j],arr[j + 1]);
            }
        }
    }
// Print the sorted elements
for(int i=0;i<N;++i){
  std::cout<<arr[i]<<" ";
   }
}
