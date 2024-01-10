#include <iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<conio.h>
#include<math.h>
using namespace std;

//Colors definition
#define cg "\033[1;32m"
#define cy "\033[1;33m"
#define cr "\033[1;31m"
#define cb "\033[1;34m"
#define cm "\033[1;35m"
#define cw "\033[1;37m"
#define cc "\033[1;36m"
#define cn "\033[1;0m"

class result{
    int wrongs, speed;
    float accuracy;
    public:
        result(int w,int s, float a){
                wrongs = w;
                speed = s;
                accuracy = a;
            }
};

void randomColor(){
    int ind = rand()%7;
    switch (ind)
    {
    case 0:
        cout<<cg;
        break;
    case 1:
        cout<<cy;
        break;
    case 2:
        cout<<cr;
        break;
    case 3:
        cout<<cb;
        break;
    case 4:
        cout<<cm;
        break;
    case 5:
        cout<<cc;
        break;
    case 6:
        cout<<cn;
        break;
    
    default:
        break;
    }
}
int countLines(ifstream &f){
    string l;
    int lCnt=0;
    while(getline(f,l))
        lCnt++;
    return lCnt;
}
int chooseLvl(){
    int lvl=0;
    cout<<endl<<"1. Easy"<<endl<<"2. Medium"<<endl<<"3. Hard"<<endl<<cy<<"Choose the difficulty Level: ";
    cin>>lvl;
    cout<<cn;
    return lvl-1;
}
bool continueGame(){
    int i;
    cout<<endl<<"1. Yes"<<endl<<"2. No"<<endl<<cy<<"Try one time more? ";
    cin>>i;
    cout<<cn;
    if(i==1)
        return true;
    return false;
}
int main(){
    string levels[3] = {"easy.txt", "medium.txt", "hard.txt"};
    bool play;
    do{
    int lvl = chooseLvl();
    ifstream myFile(levels[lvl]);
    int n = countLines(myFile);
    string line,content,lines[n];
    srand(time(0));
    int i=0;
    myFile.clear();
    myFile.seekg(0);
    while(getline(myFile,line))
        lines[i++].append(line);
    cout<<endl<<endl;
    int t=0,cursor=0;
    time_t st = time(0);
    char c;
    string text;
    int wrong=0,removed=0,r,wWords = 0,wrongs=0,tLen=0;
    r = rand()%(n-3);
    while(t<30){
        time_t ct = time(0);
        t = (ct-st);
        i=0;
        system("cls");
        if(text.length()>content.length()){
            tLen+=text.length();
            r++;
            text = text.substr(0, 0);
            cursor=0;
            wrongs+=wrong;
        }
        wrong=0;
        content = content.substr(0, 0);
        content.append(lines[r]);
        while(i<content.length()){
            if(i<cursor)
                if(text.at(i)==content.at(i))
                    cout<<cg;
                else{
                    cout<<cr;
                    wrong++;
                }
            else
                cout<<cn;
            if(i==cursor)
                cout<<cy<<"|"<<cn;
            cout<<content.at(i++);
        }
        c = _getch();
        if(c==8){
            if(cursor>0){
                cursor--;
                removed++;
                text = text.substr(0, text.size()-1);
            }
            cursor--;
        }
        else
            text+=c;
        cursor++;
    }
        wrongs+=wrong;
        tLen+=text.length();
        float gSpd = tLen/5.0;
        float accuracy = round((1 - (float) (wrongs+removed)/tLen)*100);
        int speed = 2*(gSpd - wrongs/5.0);
        cout<<endl<<"Wrong: "<<wrongs<<endl<<"Accuracy: "<<accuracy<<"%"<<endl<<"Typing Speed = "<<speed<<"wpm";
        play = continueGame();
        result res(wrongs,speed,accuracy);
        ofstream file("results.txt");
        file << res;
        
    }while(play);
    cout<<endl<<endl<<cg<<"THANK YOU!"<<cn;
}