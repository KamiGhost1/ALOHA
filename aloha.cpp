#include "aloha.h"

void aloha::start(int C, char **V){
    int mode = check_params(C, V);
    if(mode == 1){
        this->Pmode = 0;
        this->mainCycle();
    }
    if(mode == 2){
        this->Pmode = 1;
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
        if(v1 == "-m"){
            return 2;
        }
    }
    cout<<"unknown params!"<<endl;
    return 0;
}

void aloha::mainCycle(){
    cout<<"Enter M: ";
    cin>>this->M;
    this->initParams();
    int result;
    int streamStat;
    // for(this->PCmsg; this->PCmsg<1.01;this->PCmsg+=STEP){
       
    //     this->stat.clear();
    //     this->stat_stream.clear();
    //     this->errors = 0;
    // }
    this->genAbonents();
    for(int i = 0; i < CYCLES; i++){
        streamStat = this->genMsg(i);
        result = this->lifestep(i);
        this->stat.push_back(result);
        this->stat_stream.push_back(streamStat);
        cout<<i<<"; "<<result<<"; "<<streamStat<<endl;
    }
    double ping = this->ping();
    double intensive = this->intensive();
    cout<<"PCmsg: "<<this->PCmsg<<"\nping: "<<ping<<" intensive: "<<intensive<<" errors: "<<double(errors)/CYCLES<<endl; 

}

void aloha::initParams(){
    this->Psend = double(1)/this->M;
    this->Pmsg = CREATE_MSG;
    this->PCmsg = P_MSGS_MORE;
    this->errors = 0;
    cout<<"Psend: "<<this->Psend<<endl;
    cout<<"Pmsg: "<<this->Pmsg<<endl;
}

double aloha::random(double min, double max){
    return (double)(rand())/RAND_MAX*(max - min) + min;
}

int aloha::genMsg(int step){
    int counter=0;
    double P, P1;
    int size; 
    for(int i = 0; i < this->abonents.size(); i++){
        P = random(0,1);
        if(P<=this->Pmsg){
            P1 = random(0,1);
            if(P1<this->PCmsg){
                size = random(1, MAX_COUNT_MSG);
                this->abonents[i].queue+=size;
                counter+=size;
                for (int j = 0; j<size;j++){
                    this->abonents[i].gen.push_back(step);
                }
            }else{
                this->abonents[i].queue++;
                counter++;
                this->abonents[i].gen.push_back(step);
            }
        }
    }
    return counter;
}

int aloha::lifestep(int step){
    int counter = 0;
    vector <int> id;
    double P;
    for(int i =0; i < this->abonents.size();i++){
        if(this->abonents[i].queue > 0 ){
            if(this->abonents[i].Fsend){
                this->abonents[i].Fsend=false;
                P = 0;
            }else{
                P = random(0,1);
            }
            if(P <= this->Psend){
                counter++;
                id.push_back(i);
            }
        }
    }
    if(counter>1){
        id.clear();
        this->errors++;
        return 2;
    }
    if(counter==1){
        this->sending(id[0], step);
        id.clear();
        return 1;
    }
    if(counter==0){
        return 0;
    }
    return -1;
}

void aloha::sending(int id, int step){
    this->abonents[id].queue--;
    this->abonents[id].served.push_back(step);
    if(this->Pmode == 1){
         this->abonents[id].Fsend = true;
    }
}

double aloha::ping(){
    double d0 = 0.5;
    vector <double> d1;
    vector <int> dP;
    int elem;
    // cout<<"wtf"<<endl;
    for(int i =0; i< this->abonents.size(); i++){
        for(int j = 0; j<this->abonents[i].served.size();j++){
            // cout<<this->abonents[i].gen[j]<<" "<<this->abonents[i].served[j]<<endl;
            dP.push_back(this->abonents[i].served[j]-abonents[i].gen[j] +1);
            #ifdef USE_100
            elem = this->abonents[i].gen.size() - this->abonents[i].served.size();
            if(elem > 0){
                for(int u = 0;u<elem;u++){
                    dP.push_back(CYCLES);
                }
            }
            #endif
        }
        elem = 0;
        for(int j = 0; j<dP.size();j++){
            elem+=dP[j];
        }
        if(dP.size()>0)
            d1.push_back(double(elem)/dP.size());
        else
            d1.push_back(CYCLES);
        dP.clear();
    }
    elem = 0;
    for(int j = 0; j<d1.size();j++){
        elem+=d1[j];
        // cout<<d1[j]<<endl;
    }
    return d0 + double(elem)/d1.size();
}

double aloha::intensive(){
    int lamda=0;
    for(int i =0; i<this->stat_stream.size();i++){
        lamda+=this->stat_stream[i];
    }
    return double(lamda)/this->stat_stream.size();
}

void aloha::genAbonents(){
    if(this->abonents.size() > 0)
        this->abonents.clear();
    abonent a;
    a.queue = 0;
    if(this->Pmode == 0){
        a.Fsend = false;
    }else{
        a.Fsend = true;
    }
    for(int i = 0; i < this->M; i++){
        this->abonents.push_back(a);
    }
}