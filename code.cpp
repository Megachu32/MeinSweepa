#include <iostream>
#include <vector> //for logo only
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <chrono>
#include <windows.h>
#include <fstream>
#include <thread>
#include <atomic>
#include <algorithm>

using namespace std;

std::atomic<bool> running(true);

void PrintLogo() //this is logo print
{
    vector <vector<string>> words ={
        {
            " #       # ",
            " # #   # # ",
            " #   #   # ",
            " #       # ",
            " #       # "
        }, //  m
        {
            " # # # # # ",
            "     #     ",
            "     #     ",
            "     #     ",
            " # # # # # "
        }, //  i
        {
            " #       # ",
            " # #     # ",
            " #   #   # ",
            " #     # # ",
            " #       # "
        }, //  n
        {
            " # # # # #   ",
            " #           ",
            " # # # # #   ",
            " #           ",
            " # # # # #   "
        }, //  e
        {
            " # # # # # ",
            " #         ",
            " # # # # # ",
            "         # ",
            " # # # # # "
        }, //  s
        {
            " #       # ",
            " #       # ",
            " #   #   # ",
            " # #   # # ",
            " #       # "
        }, //  w
        {
            " # # # # # ",
            " #         ",
            " # # # # # ",
            " #         ",
            " # # # # # "
        }, //  e
        {
            " # # # # # ",
            " #         ",
            " # # # # # ",
            " #         ",
            " # # # # # "
        }, //  e
        {
            " # # # # # ",
            " #       # ",
            " # # # # # ",
            " #         ",
            " #         "
        }, //  p
        {
            " # # # # # ",
            " #         ",
            " # # # # # ",
            " #         ",
            " # # # # # "
        }, //  e
        {
            " # # # # # ",
            " #       # ",
            " # # # # # ",
            " #     #   ",
            " #       # "
        }, // r
    };

    // Calculate the total width of the word "MAZE"

    int wordwidth = 0;
    const int consolewidth = 40;
    const int consoleHeight = 30;

        wordwidth = words[0].size() + 1; // Add 1 space between letters

        // Calculate offsets
        int horizontaloffset = (consolewidth - wordwidth) / 2;
        int verticaloffset = (consoleHeight -5) / 2; // 5 rows for the word

        // Print blank lines for vertical centering

        for (int i = 0; i < verticaloffset; ++i) {
        cout << endl;
        }
        for(int i = 0; i < 5; i++){
            for (int i = 0; i < horizontaloffset; ++i) {
                cout << " ";
            }
            for (const auto& word : words) {
                cout << "\033[35m" << word[i] << "\033[0m";
            }
            cout << endl;
        }

    // // Print each line of the logo
    // for (int i = 0; i < 5; ++i) {
    //     for (const auto& word : words) {
    //         cout << "\033[35m" << word[i] << "\033[0m";
    //     }
    //     cout << endl;
    // }
}

void PrintGame(int n, int m, string tile[20][20], string difn[3], int minec[3], int p[2], int timeGo, int cheat, string tilen[20][20])
{ 
        cout << "Difficulty: " << difn[n] << endl;
        cout << "Mines : " << minec[n] << endl;
        cout << "Time: " << timeGo << endl;
        for(int i=0;i<m;i++){
            for(int j=0;j<m;j++){
                if(cheat != 1){
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
                else{
                    if(tilen[i][j] == "[F]" && !(i==p[0] && j==p[1])){
                        cout << "\033[33m" << tilen[i][j] << "\033[0m" << " ";
                    }
                    else if(tilen[i][j] == "[M]"){
                        cout << "\033[31m" << tilen[i][j] << "\033[0m" << " ";
                    }
                    else if(i==p[0] && j==p[1]){
                        cout << "\033[32m";
                        cout << tilen[i][j] << " ";
                        cout << "\033[0m";
                    }
                    else{
                        cout << tilen[i][j] << " ";
                    }
                }
            }
            cout << endl;
        }
        cout << "Green tile is the player position" << endl;
        cout << "Uncover all the tile to win" << endl;
        cout << "Press W/A/S/D to move" << endl;
        cout << "Press E to dig" << endl;
        
}

void scoreWrite(int n, string p)
{
    ofstream score("P_Scores.txt", ios::app); // Open file in append mode
    if (!score) {
        std::cerr << "Error: File could not be created!" << std::endl;
        return;
    }
    // getline(cin, p);
    score << p << ": " << n << endl;
    score.close();
}

void viewScore() // untuk print score
{
    ifstream score("P_Scores.txt");
    if (!score) {
        cerr << "Error: File could not be opened!" << endl;
        return;
    }
    vector<pair<int, string>> scores;
    string line;
    while (getline(score, line)) {
        size_t pos = line.find(": ");
        if (pos != string::npos) {
            string name = line.substr(0, pos);
            int score = stoi(line.substr(pos + 2));
            scores.push_back({score, name});
        }
    }
    sort(scores.begin(), scores.end(), greater<>());

    cout << "Top 5 Players with the Lowest Scores:" << endl;
        int count = 4;
    for (size_t i = min(scores.size(), size_t(5)); i > 0; --i) {
        cout << 5-count << ". " << scores[i].second << ": " << scores[i].first << endl;
        count--;
    }
    cout << "Press any key to return to the main menu" << endl;
}

void gameTimer(int &score, int &timeGo) {
    int timel = 0;
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        timel++;
        score = timel;
        timeGo = timel;
    }
}

void wordTab()
{
    int wordwidth = 0;
    const int consolewidth = 30;
    const int consoleHeight = 10;
    int horizontaloffset = (consolewidth - wordwidth) / 2;
    for(int i = 0; i < 5; i++){
            for (int i = 0; i < horizontaloffset; ++i) {
                cout << " ";
            }
            }
}


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
    srand(time(0));
    char key; // Gerakan player (w,a,s,d,x,f)
    int n,m,i,j,minecount,ni,nj,state1 = 0,counter = 0; // n untuk index, m untuk tile
    int game = 0; // counter dipakai
    int dif[] = {9,16,20}; // Easy, Medium, Hard
    string difn[] = {"\033[32mEasy\033[0m","\033[33mMedium\033[0m","\033[31mHard\033[0m"}; // nama difficulty
    int minec[] = {10,40,80}; // jumlah bom
    string flag = "[F]", mine = "[M]";
    int score = 0, timeGo = 0; // untuk score dan time
    bool win = true; //untuk loop
    int cheat = 0; //cheat

    std::thread timerThread(gameTimer, std::ref(score), std::ref(timeGo));

    bool continueGame = true;

    do { // for loop do menu pertama
        do {
            PrintLogo();
            wordTab();
            cout << "1. Play" << endl;
            wordTab();
            cout << "2. Score" << endl;
            wordTab();
            cout << "3. Exit" << endl;
            wordTab();
            cout << ">> "; cin >> n;
            if(n == 777){break;}
        } while ((n < 1 || n > 3));

        switch (n) {
            case 1: {
                state1 = 0;
                cheat = 0;
                score = 0;
                timeGo = 0;
                counter = 0;
                game = 0;
                i = 0;
                j = 0;
                do {
                    system("cls");
                    cout << "Choose difficulty:" << endl;
                    cout << "1. Easy(9x9 10 mines)" << endl;
                    cout << "2. Medium(16x16 40 mines)" << endl;
                    cout << "3. Hard(20x20 80 mines)" << endl;
                    cout << ">> "; cin >> n;
                    if(n == 69){cheat = 1; cout << "CHEAT ON" << endl; while(!kbhit());}
                } while (n < 1 || n > 3);
                n = n - 1;
                m = dif[n];
                string tile[20][20], tilen[20][20];
                int p[] = {0, 0};
                for (i = 0; i < m; i++) {
                    for (j = 0; j < m; j++) {
                        tile[i][j] = "[ ]";
                        tilen[i][j] = "[ ]";
                    }
                }
                continueGame = true;
                do {
                    do {
                        system("cls");
                        PrintGame(n, m, tile, difn, minec, p, timeGo, cheat, tilen);

                        cout << "Press F to place flag" << endl;
                        if (state1 < 0) {
                            system("cls");
                            cout << "You Lose" << endl << "Game Over!" << endl;
                            while (!kbhit());
                            running = false;
                            timerThread.join();
                            continueGame = false;
                            break;
                        } else if (state1 > 0) {
                            system("cls");
                            cout << "You uncover all the tile" << endl;
                            cout << "You Win!" << endl;
                            while (!kbhit());
                            system("cls");
                            string name;
                            cout << "What is your name? "; cin >> name;
                            scoreWrite(score, name);
                            running = false;
                            timerThread.join();
                            continueGame = false;
                            break;
                        }
                    } while (!kbhit());
                    if (!continueGame) break;
                    key = getch();
                    if (key == 'w' || key == 'W' || key == '8') {
                        if (p[0] > 0) {
                            p[0]--;
                        }
                    } else if (key == 'a' || key == 'A' || key == '4') {
                        if (p[1] > 0) {
                            p[1]--;
                        }
                    } else if (key == 's' || key == 'S' || key == '5') {
                        if (p[0] < m - 1) {
                            p[0]++;
                        }
                    } else if (key == 'd' || key == 'D' || key == '6') {
                        if (p[1] < m - 1) {
                            p[1]++;
                        }
                    } else if (key == 'e' || key == 'E') {
                        if (game == 0) {
                            int check[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
                            int test[2];
                            for (int b = 0; b < minec[n]; b++) {
                                do {
                                    i = rand() % m;
                                    j = rand() % m;
                                } while ((i == p[0] && j == p[1]) || tilen[i][j] == "[M]");
                                tilen[i][j] = "[M]";
                            }
                            for (i = 0; i < m; i++) {
                                for (j = 0; j < m; j++) {
                                    if (tilen[i][j] != "[M]") {
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
                                        tilen[i][j] = "[" + to_string(minecount) + "]";
                                    }
                                }
                            }
                            game++;
                        }
                        if (tilen[p[0]][p[1]] == mine) {
                            tile[p[0]][p[1]] = tilen[p[0]][p[1]];
                            for (i = 0; i < m; i++) {
                                for (j = 0; j < m; j++) {
                                    if (tilen[i][j] == mine) {
                                        tile[i][j] = tilen[i][j];
                                    }
                                }
                            }
                            state1--;
                        } else {
                            tile[p[0]][p[1]] = tilen[p[0]][p[1]];
                            counter++;
                        }
                    } else if (key == 'f' || key == 'F') {
                        if (tile[p[0]][p[1]] == "[ ]") {
                            tile[p[0]][p[1]] = flag;
                        } else if (tile[p[0]][p[1]] == flag) {
                            tile[p[0]][p[1]] = "[ ]";
                        }
                    }
                    else if(key == 'c' || key == 'C'){
                        if(cheat == 4 || cheat == 2){
                            cheat = 1;
                        }
                        if (cheat == 1){
                            cheat++;
                        }
                    }
                    if (counter == (m * m) - minec[n]) {
                        state1++;
                    }
                } while (continueGame);
                n = 0;
                break;
            }
            case 2: {
                system("cls");
                viewScore();
                while (!kbhit());
                system("cls");
                break;
            }
            case 3: {
                break;
            }
            case 777:{
                srand(time(0));
                mesingacor();
                break;
            }
        }
    } while (n != 3);
    running = false;
    timerThread.join();
 return 0;
}