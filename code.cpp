#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    char key; // Gerakan player (w,a,s,d,x,f)
    int n,m,i,j,minecount,ni,nj,state = 0,counter = 0; // n untuk index, m untuk tile
    int game = 0; // counter dipakaic
    int dif[] = {9,16,20}; // Easy, Medium, Hard
    string difn[] = {"\033[32mEasy\033[0m","\033[33mMedium\033[0m","\033[31mHard\033[0m"}; // nama difficulty
    int minec[] = {10,40,80}; // jumlah bom
    string flag = "[F]", mine = "[M]";
    // Lol me 64
    do{
        system("cls");
        cout << "=== MINESWEEPER ===" << endl;// MENU
        cout << "Choose difficulty:" << endl;
        cout << "1. Easy(9x9 10 mines)" << endl;
        cout << "2. Medium(16x16 40 mines)" << endl;
        cout << "3. Hard(20x20 80 mines)" << endl;
        cout << ">> "; cin >> n;
    }while(n<1 || n>3);
    n = n-1;
    m = dif[n];
    string tile[m][m],tilen[m][m];
    //////////////////////
        //PLAYSCREEN//
    //////////////////////
    int p[] = {0,0};
    for(i=0;i<m;i++){
        for(j=0;j<m;j++){
            tile[i][j] = "[ ]";
            tilen[i][j] = "[ ]";
        }
    }
    do{
        system("cls");
        cout << "=== MINESWEEPER ===" << endl;
        cout << "Difficulty: " << difn[n] << endl;
        cout << "Mines : " << minec[n] << endl;
        for(i=0;i<m;i++){
            for(j=0;j<m;j++){
                if(tile[i][j] == "[F]" && !(i==p[0] && j==p[1])){
                    cout << "\033[33m" << tile[i][j] << "\033[0m" << " ";
                }
                else if(tile[i][j] == "[M]"){
                    cout << "\033[31m" << tile[i][j] << "\033[0m" << " ";
                }
                else if(i==p[0] && j==p[1]){
                    cout << "\033[32m";
                    cout << tile[i][j] << " ";
                    cout << "\033[0m";
                }
                else{
                    cout << tile[i][j] << " ";
                }
            }
            cout << endl;
        }
        cout << "Green tile is the player position" << endl;
        cout << "Uncover all the tile to win" << endl;
        cout << "Press W/A/S/D to move" << endl;
        cout << "Press X to dig" << endl;
        cout << "Press F to place flag" << endl;
        //-------------------------------------------
        // Win Lose Checker
        if(state<0){
            cout << "You Lose" << endl << "Game Over!" << endl;
            return 0;
        }
        else if(state>0){
            cout << "You uncover all the tile" << endl;
            cout << "You Win!" << endl;
            return 0;
        }
        //-------------------------------------------

        key = getch();
        if(key=='w' || key=='W' || key=='8'){//move up
            if(p[0]>0){
                p[0]--;
            }
        }
        else if(key=='a' || key=='A' || key=='4'){//move left
            if(p[1]>0){
                p[1]--;
            }
        }
        else if(key=='s' || key=='S' || key=='5'){//move down
            if(p[0]<m-1){
                p[0]++;
            }
        }
        else if(key=='d' || key=='D' || key=='6'){//move right
            if(p[1]<m-1){
                p[1]++;
            }
        }
        else if(key=='x' || key=='X'){ // Digging
            if(game==0){ // Bomb Placement
                // Bomb placement logic
                int check[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
                int test[2];
                for (int b = 0; b < minec[n]; b++) {
                do {
                    i = rand() % m;
                    j = rand() % m;
                } while ((i == p[0] && j == p[1]) || tilen[i][j] == "[M]");  // Don't place bombs on player position
                tilen[i][j] = "[M]";  // Place bomb
                }

                // Calculate adjacent mines
                for (i = 0; i < m; i++) {
                    for (j = 0; j < m; j++) {
                        if (tilen[i][j] != "[M]") { // Only count for non-bomb tiles
                            minecount = 0;
                            for (int k = 0; k < 8; k++) {
                                test[0] = check[k][0];
                                test[1] = check[k][1];
                                ni = i + test[0];
                                nj = j + test[1];
                                if (ni >= 0 && nj >= 0 && ni < m && nj < m && tilen[ni][nj] == "[M]") {
                                    minecount++;
                                }
                            }
                        tilen[i][j] = "[" + to_string(minecount) + "]"; // Update with number of adjacent mines
                        }
                    }
                }
                game++;
            }
            if(tilen[p[0]][p[1]]==mine){ // Digging bomb
                tile[p[0]][p[1]]=tilen[p[0]][p[1]]; // revealing bomb
                for(i=0;i<m;i++){
                    for(j=0;j<m;j++){
                        if(tilen[i][j]==mine){
                            tile[i][j] = tilen[i][j];
                        }
                    }
                }
                state--;
            }
            else{ // Normal digging
                tile[p[0]][p[1]] = tilen[p[0]][p[1]];
                counter++;
            }
        }
        else if(key=='f' || key=='F'){ // Flag
            if(tile[p[0]][p[1]]=="[ ]"){
                tile[p[0]][p[1]]= flag;
            }
            else if(tile[p[0]][p[1]]==flag){
                tile[p[0]][p[1]]="[ ]";
            }
        }
        if(counter==(m*m)-minec[n]){// win when all tile uncovered
            state++;
        }
    }while(true);
    return 0;
}
