#include <iostream>
#include<vector>
using namespace std;

int main(){
    vector<vector<int> > array={{1,2,8,9},{2,4,9,12},{4,7,10,13},{6,8,11,15}};
    
    int target=7;
    int row=array.size();
    int col=array[0].size();
       for (int i=row-1;i>=0;i--){
           int j=0;
            while(j<col){
                if ( target == array[i][j])
                    return true;
                
                if (target<array[i][j]){
                    break;
                }
                j++;
            }
       }
       return false;
}