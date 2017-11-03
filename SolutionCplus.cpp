#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define MAXITER 500

using namespace std;

 
 class Bender{
     int Location[2];
     int NLocation[2];
     int TxLocation[2];
     int TyLocation[2];
     char Symb, NextSymb;
     string Paths[MAXITER];
     
     bool Beer, Inverted, Blocked;
     public:
        string Direction;
        Bender(string *, int);
        void update_bender( string *);
        void update_nextstep( string *);
        void takeastep(string *);
        void print_bender_unit(void);
        bool at_suicide(void);
        void add2print(int);
            
 };
 
 void Bender::print_bender_unit(void){
  
     cout<<"Bender is at: " << this->Location[0] <<" "<< this->Location[1] << endl;
     cout<<"Bender is going " << this->Direction << " towards " << this->NLocation[0] <<" "<< this->NLocation[1] << endl;
     cout<<"Has he been drinking: " << this->Beer << endl;
     cout<<"Is he inverted: " << this->Inverted << endl;
     cout<<"He is currently on a " << this->Symb << endl;
     cout<<"Teleporter one at (" <<this->TxLocation[0] << "," <<this->TyLocation[0] <<")"<< endl;
     cout<<"Teleporter two at (" <<this->TxLocation[1] << "," <<this->TyLocation[1] <<")"<< endl;

     if(this->Blocked == true){cout << "He is being blocked by a" << this->NextSymb << endl;}
 }
 
 Bender::Bender(string* _map, int _L){
     Direction = "SOUTH";
     Beer = Inverted = Blocked = false;
     Symb = '@';
     size_t whereat = '@';
     //Paths = new string[MAXITER];
     for(int i = 0; i < _L; i++){
         whereat = _map[i].find('@');
         if(whereat != string::npos){
             Location[0] = i;
             Location[1] = whereat;
         }
     }
     TxLocation[0] = 0; TxLocation[1] = 0;
     TyLocation[0] = 0; TyLocation[1] = 0;
     int temp = 0;
     for(int i = 0; i < _L; i++){
         whereat = _map[i].find('T');
         if(whereat != string::npos){
             TxLocation[temp] = i;
             TyLocation[temp] = whereat;
             temp++;
         }
     }
     NLocation[0] = Location[0] + 1;
     NLocation[1] = Location[1];
     //copy(begin(Location),end(Location), NLocation);
     NextSymb = _map[NLocation[0]][NLocation[1]];

 }
 
 void Bender::update_bender(string *_map){
     this->Location[0] = this->NLocation[0]; this->Location[1] = this->NLocation[1];
     this->Symb = _map[this->Location[0]][this->Location[1]];
     this->Blocked = false;
     switch(this->Symb){
         case 'B':
            this->Beer = not this->Beer;
            break;
        case 'I':
            this->Inverted = not this->Inverted;
            break;
        case 'S':
            this->Direction = "SOUTH";
            this->NLocation[0]++;
            break;
        case 'E':
            this->Direction = "EAST";
            this->NLocation[1]++;
            break;
        case 'N':
            this->Direction = "NORTH";
            this->NLocation[0]--;
            break;
        case 'W':
            this->Direction = "WEST";
            this->NLocation[1]--;
            break;
        case 'X':
            if(this->Beer == true){_map[Location[0]][Location[1]] = ' ';}
            break;
        case 'T':
            (this->Location[0] == TxLocation[0]) ? (this->Location[0] =  TxLocation[1]) : (this->Location[0] =  TxLocation[0]);
            (this->Location[1] == TyLocation[0]) ? (this->Location[1] =  TyLocation[1]) : (this->Location[1] =  TyLocation[0]);
            break;
     }
     this->NextSymb = _map[this->NLocation[0]][this->NLocation[1]];


     
 }
 
 void Bender::update_nextstep(string *_map){
     this->NLocation[0] = this->Location[0]; this->NLocation[1] = this->Location[1];
     switch(this->Direction[0]){
            case 'S':
                this->NLocation[0]++;
                break;
            case 'E':
                this->NLocation[1]++;
                break;
            case 'N':
                this->NLocation[0]--;
                break;
            case 'W':
                this->NLocation[1]--;
                break;
            case 'B':
                this->Beer = not this->Beer;
            case 'I':
                this->Inverted = not this->Inverted;
     }
     this->NextSymb = _map[this->NLocation[0]][this->NLocation[1]];
     if(this->NextSymb == '#' || (this->NextSymb == 'X' && this->Beer == false)){ this->Blocked = true;}
     //else if(this->NextSymb == 'X' && this->Beer == true){ _map
     else{this->Blocked = false;}
 }
 
 void Bender::takeastep(string *_map){
  
  string directions[4] = {"SOUTH", "EAST", "NORTH", "WEST"};
  int temp = 0;
  this->update_nextstep(_map);
  while(this->Blocked == true){
      (this->Inverted == false) ? (this->Direction = directions[temp]) : (this->Direction = directions[3-temp]);
      //this->print_bender_unit();
      this->update_nextstep(_map);
      temp++;
  }
     
 }
 void Bender::add2print(int itern){
    
    //cout << this->Direction << endl;
    this->Paths[itern] = this->Direction;
    //cout << this->Paths[itern] << endl;
 }
            
bool Bender::at_suicide(void){

    if(this->Symb == '$'){return true;}
    else{return false;}
            
 }

void print_map(string* _map, int _L){
    for(int i = 0; i < _L; i++){
        cout << _map[i] << endl;
    }
    return;
}



int main()
{
    int L, C, numofsteps = 0;
    cin >> L >> C; cin.ignore();
    string *map;
    string *path2suic;
    path2suic = new string[MAXITER];
    map = new string[L];
    for (int i = 0; i < L; i++) {
        getline(cin, map[i]);
    }
    //print_map(map, L);
    Bender *rodr = new Bender(map, L);
    //rodr->print_bender_unit();
    while(rodr->at_suicide() == false){
        rodr->takeastep(map);
        //rodr->print_bender_unit();
        path2suic[numofsteps] = rodr->Direction;
        rodr->add2print(numofsteps);

        rodr->update_bender(map);

        numofsteps++;
        if(numofsteps >MAXITER-1){break;}
    }
    if( numofsteps > MAXITER-1){cout<< "LOOP"<<endl;}
    else{
        for(int i = 0; i < numofsteps; i++){
            cout << path2suic[i] << endl;   
        }
    }
    
    return 0;
}
