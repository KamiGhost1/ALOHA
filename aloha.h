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
    bool Fsend;
    vector <int> gen;
    vector <int> served;
};

class aloha{
public:
    void start(int C, char **V);
    int check_params(int C, char **V);
    void initParams();
    double random(double min, double max);
    int genMsg(int step);
    void sending(int id, int step);
    int lifestep(int step);
    void opening();
    void mainCycle();
    double ping();
    int Pmode;
    int M;
    double Pmsg;
    double Psend;
    vector <abonent> abonents;
    vector <int> stat;
    vector <int> stat_stream;
};

