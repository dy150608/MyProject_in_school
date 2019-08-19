
#include "greedysnake.h"

int main()
{
    using namespace std;
    int _option;
    Snake _osnake;
    cout<<"w:turn up"<<endl;
    cout<<"s:turn down"<<endl;
    cout<<"a:turn left"<<endl;
    cout<<"d:turn right"<<endl;
    cout<<"tips: your snake can not turn back"<<endl;
    system("pause");
    system("cls");
    cout<<"please choose option:"<<"\n";
    cout<<"1:new game"<<"\n"<<"2:quit game"<<"\n";
    while(cin>>_option && _option != 2)
    {
        if(_option != 1)
        {
            cout<<"please input legal option"<<"\n";
            continue;
        }
        _osnake.intialize();
        _osnake.gamecontinue();
        _osnake.printscore();
        cout<<"please input option!"<<endl;
    }
    return 0;
}
