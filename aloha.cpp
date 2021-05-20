#include "aloha.h"

void aloha::start(int C, char **V){
    int mode = check_params(C, V);
    if(mode == 1){
        this->mainCycle();
    }
}

void aloha::opening(){
    cout<<endl;
    cout<<"\t__    __      ______ "<<endl;
    cout<<"\t| |  / /   / /______\\ \\   | | \\  / | |   | |"<<endl;
    cout<<"\t| | / /    | |      | |   | |\\ \\/ /| |   | |"<<endl;
    cout<<"\t| |/ /     | |      | |   | |  --  | |   | |"<<endl;
    cout<<"\t| |\\ \\     | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| | \\ \\    | |      | |   | |      | |   | |"<<endl;
    cout<<"\t| |  \\ \\   | |______| \\   | |      | |   | |"<<endl;
    cout<<"\t| |   \\ \\  \\ \\______| \\\\  | |      | |   | |"<<endl;
    cout<<"\n\nK@mi soft\ngithub.com:kamighost1\n"<<endl;
};

int aloha::check_params(int C, char **V){
    if(C == 1){
        this->opening();
        cout<<"its ALOHA modeling program"<<endl;
        exit(0);
    }

    if(C == 2){
        string v1 = V[1];
        if(v1 == "-s"){
            return 1;
        }
    }
    cout<<"unknown params!"<<endl;
    return 0;
}

void aloha::mainCycle(){
    cout<<"Enter M: ";
    cin>>this->M;
    this->initParams();
    abonent a;
    a.queue = 0;
    for(int i = 0; i < this->M; i++){
        this->abonents.push_back(a);
    }
    int result;
    int streamStat;
    for(int i = 0; i < CYCLES; i++){
        streamStat = this->genMsg();
        result = this->lifestep();
        this->stat.push_back(result);
        this->stat_stream.push_back(streamStat);
        cout<<i<<"; "<<result<<"; "<<streamStat<<endl;
    }
}

void aloha::initParams(){
    this->Psend = double(1)/this->M;
    this->Pmsg = CREATE_MSG;
    cout<<"Psend: "<<this->Psend<<endl;
    cout<<"Pmsg: "<<this->Pmsg<<endl;
}

double aloha::random(double min, double max){
    return (double)(rand())/RAND_MAX*(max - min) + min;
}

int aloha::genMsg(){
    int counter=0;
    double P; 
    for(int i = 0; i < this->abonents.size(); i++){
        P = random(0,1);
        if(P<=CREATE_MSG){
            this->abonents[i].queue++;
            counter++;
        }
    }
    return counter;
}

int aloha::lifestep(){
    int counter = 0;
    int id;
    double P;
    for(int i =0; i < this->abonents.size();i++){
        if(this->abonents[i].queue > 0 ){
            P = random(0,1);
            if(P <= this->Psend){
                counter++;
                id = i;
            }
        }
    }
    if(counter>1){
        return 2;
    }
    if(counter==1){
        this->sending(id);
        return 1;
    }
    if(counter==0){
        return 0;
    }
    return -1;
}

void aloha::sending(int id){
    this->abonents[id].queue--;
}