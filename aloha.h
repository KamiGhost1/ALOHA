#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <vector>
#include <stdlib.h>
using namespace std;
#define CYCLES 100
#define CREATE_MSG 0.1

class abonent{
public:
    int queue;
};

class aloha{
public:
    void start(int C, char **V);
    int check_params(int C, char **V);
    void initParams();
    double random(double min, double max);
    int genMsg();
    void sending(int id);
    int lifestep();
    void opening();
    void mainCycle();
    int M;
    double Pmsg;
    double Psend;
    vector <abonent> abonents;
    vector <int> stat;
    vector <int> stat_stream;
};

