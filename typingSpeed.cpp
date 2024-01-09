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
int main(){
    ifstream myFile("paragraph.txt");
    string line,content,lines[7];
    srand(time(0));
    int i=0;
    while(getline(myFile,line))
        lines[i++].append(line);
    cout<<endl<<endl;
    int t=0,cursor=0;
    time_t st = time(0);
    char c;
    string text;
    int wrong=0,removed=0,r=0,wWords = 0,wrongs=0,tLen=0;
    while(t<30){
        time_t ct = time(0);
        t = (ct-st);
        i=0;
        wrong=0;
        system("cls");
        if(text.length()>content.length()){
            r++;
            text = text.substr(0, 0);
            cursor=0;
            wrongs+=wrong;
        }
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
        for(int i=0;i<r;i++)
            tLen+=lines[i].length();
        tLen+=text.length();
        float gSpd = tLen/5.0;
        float accuracy = round((1 - (float) (wrongs+removed)/tLen)*100);
        int speed = 2*(gSpd - wrongs/5);
        cout<<endl<<"Wrong: "<<wrongs<<endl<<"Accuracy: "<<accuracy<<"%"<<endl<<"Typing Speed = "<<speed<<"wpm";
}