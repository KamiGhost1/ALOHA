#include "aloha.h"

int main(int C, char **V){
    srand(time(0));
    aloha a;
    a.start(C, V);
    return 0;
}