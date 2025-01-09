#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <windows.h>

using namespace std;

int mesingacor()
{
    int goinp, gomenu=1;
    int retune=0;
    char key;
    int g1,g2,g3;
    do
    {
        key=getch();
    system("cls");
    cout << "mesin" << endl;
    cout << "Q <- pull" << endl;
    cout << "E <- back" << endl;



    if (key=='q' || key== 'Q')
    {
        int gacha=rand()%1000;
        g1=gacha%10;
        g2=gacha/10%10;
        g3=gacha/100;





    }
    else if (key=='e' || key == 'E')
    {
        gomenu=0;
    }
    else if (key =='x' || key=='X')
    {
      g1=7;
      g2=7;
      g3=7;
    }

    if (key!='e' || key!='E')
    {
        cout << endl << g1 << g2 << g3 << endl;

        if (g1 == g2 && g2 == g3)
        {
            cout << "GACOR!" << endl;
        }
        else
        {
            cout << "tch" << endl;
        }

        Sleep(600);
    }


    }while(gomenu==1);




    return 0;

}




int main()
{
    int inp;
    srand(time(0));


   cout << "menu" << endl;
   cout << "3. mesin gacor" << endl;
   cout << ">> "; cin >> inp;

   if (inp < 1 || inp > 9)
   {
       do{cout << ">> "; cin >> inp;}while(inp <1 || inp >9);
   }


   if (inp==3)
   {
       mesingacor();
   }





    return 0;
}
