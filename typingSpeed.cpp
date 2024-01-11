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
    public:
        int wrongs, speed;
        float accuracy;
        char timeStmp[60];
        void setResult(int w,int s, float a){
                wrongs = w;
                speed = s;
                accuracy = a;
                time_t t = time(NULL);
                struct tm *aT = localtime(&t);
                strftime(timeStmp,60,"%d %b - %I:%M%p",aT);
            }
        void updateFile(ofstream &f){
            
            f<<this->timeStmp<<",   "<<this->wrongs<<",          "<<this->speed<<",             "<<this->accuracy<<endl;
        }
};
int countLines(ifstream &f){
    string l;
    int lCnt=0;
    while(getline(f,l))
        lCnt++;
    f.clear();
    f.seekg(0);
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
void displayLeaderboard(result res){
    ifstream rfile("results.txt");
    int n = countLines(rfile)-1;
    rfile.close();
    result results[n];
    FILE *p = fopen("results.txt", "r");
    char st[100];
    fgets(st,100,p);
    for(int i=0;i<n;i++)
        fscanf(p,"%60[^,],   %d,          %d,             %f\n",results[i].timeStmp,&results[i].wrongs,&results[i].speed,&results[i].accuracy);
    fclose(p);
    int sorted=1;
    while(sorted){
        sorted=0;
        for(int i=0;i<n-1;i++)
            if(results[i].speed<results[i+1].speed){
                result temp = results[i];
                results[i] = results[i+1];
                results[i+1] = temp;
                sorted=1;
            }
        }
    cout<<endl<<"\t\t"<<cy<<"LEADERBOARD"<<endl;
    cout<<"SN   Timestamp         Wrongs      Speed(wpm)      Accuracy"<<endl<<cn;
    for(int i=0;(i<n && i<10);i++){
        string ts(results[i].timeStmp),ts2(res.timeStmp);
        if(ts==ts2)
            cout<<cg;
        cout<<i+1<<"    "<<results[i].timeStmp<<"    "<<results[i].wrongs<<"            "<<results[i].speed<<"              "<<results[i].accuracy<<endl<<cn;
    }
}
int main(){
    string levels[3] = {"easy.txt", "medium.txt", "hard.txt"};
    bool play;
    do{
    int lvl = chooseLvl();
    ifstream myFile(levels[lvl]);
    if(!myFile.is_open()){
        cerr<<"Error: cannot open file";
        return 1;
    }
    int n = countLines(myFile);
    string line,content,lines[n];
    srand(time(0));
    int i=0;
    while(getline(myFile,line))
        lines[i++].append(line);
    cout<<endl<<endl;
    int t=0,cursor=0;
    time_t st = time(0);
    char c;
    string text;
    int wrong=0,removed=0,r,wrongs=0,tLen=0;
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
            cout<<content.at(i++)<<cn;
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
        result res;
        res.setResult(wrongs,speed,accuracy);
        ifstream file;
        file.open("results.txt");
        ofstream rfile;
        if(!file){
            rfile.open("results.txt",ios::app);
            rfile<<"Timestamp         Wrongs      Speed(wpm)      Accuracy"<<endl;
        }
        else
            rfile.open("results.txt",ios::app);
        file.close();
        res.updateFile(rfile);
        rfile.close();
        displayLeaderboard(res);
        play = continueGame();
    }while(play);
    cout<<endl<<endl<<cg<<"THANK YOU!"<<cn;
}