#include <iomanip>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>


using namespace std;

int main(int argc, char** argv)
{


    char* input, *output;
    input = argv[1];
    output = argv[2];
    std::fstream f(input , std::ios::in);
    std::fstream  out(output , std::ios::out);

    int sample;
    bool check = true;
    
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();


    while(f >> sample)
    {
        //out << "check "<< sample << "\n";
        if(sample < 2)
        {
            out << "invalid input , please input >= 2" << "\n";
        }
        for (int i = 2; i <= sqrt(sample); i++)
        {
            if (sample % i == 0)
              check = false;
        }
        if (check)
            out << 1 << "\n";
        if (check == false)
            out << 0 << "\n";

        check = true;

    }
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::cout << "Run time "
  	<< std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count()
  	<< "  us.\n";
    //cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;
} 
