#include"calculate.h"
#include <string>
#include <algorithm>
int main()
{
    string input;
    cout<<"enter what you want to calculate:"<<endl;
    getline(cin,input) ;
     input.erase(remove_if(input.begin(), input.end(), ::isspace), input.end());
    try {
        cout << "the result is:" << calculate(input) << endl;
    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
    }
    return 0;}

