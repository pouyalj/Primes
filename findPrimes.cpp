#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <omp.h>
using namespace std;

int main() {

    int num=-1, numPrime=0;
    vector<int> P;
    cout << "Type upper bound integer: ";
    cin >> num;

    omp_set_num_threads(omp_get_max_threads());

    #pragma omp parallel for schedule(dynamic)
    for (int n = 0; n <= num; n++) {
        int flag=1, j=2; 
        if(n <=1) {
            // cout << std::to_string(n) + " is not a prime \n"; //print if necessary
        }
        else {
            while (j<((n/2)+1)) {
                if(n % j==0) {
                    flag = 0;
                }
                j++;
            }
            if(flag==0) {
                // cout << std::to_string(n) + " is not prime \n"; // print if neccessary
            }
            else {
                // cout << std::to_string(n) + " is prime \n";
                numPrime++;
                #pragma omp critical
                P.push_back(n);
            }
        }
    }
    cout << "Total number of prime numbers within range: " + std::to_string(numPrime) + "\n";
    ofstream file;
	file.open("Primes.txt");
    for(int i=0;i<P.size();++i){
		file<<P[i]<<endl;
    }
    file.close();
}