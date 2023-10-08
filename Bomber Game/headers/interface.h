#include "headers/leaderboard.h"
#include "headers/game.h"
class startInterface {
    int menuOption, levelOption, row = 20, col = 80, numberOfEnemy = 10, life = 5, totalTime = 300;
    string name;
public:
    startInterface() {
        showMenu();
    }

    void showMenu() {
        system("cls");
        cout << "\n\n\n\n";
        cout << setw(80);
        cout << "WELCOME TO BOMBER GAME!\n\n";
        cout << setw(70);
        cout << "1. Start\n\n";
        cout << setw(76);
        cout << "2. How To Play\n\n";
        cout << setw(76);
        cout << "3. Leaderboard\n\n";
        cout << setw(69);
        cout << "4. Exit\n\n";

        cin >> menuOption;
        if(menuOption == 1) {
            levelShow();
        }
        else if(menuOption == 2) {
            system("cls");
            HANDLE hConsole;
            cout << "\n\n\n\n";
            cout << setw(80);
            cout << "Game Instructions\n\n";
            cout << setw(76);
            cout << "To go UP press ";
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\'w\'\n\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << setw(76);
            cout << "To go DOWN press ";
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\'s\'\n\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << setw(78);
            cout << "To go LEFT press ";
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\'a\'\n\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << setw(76);
            cout << "To go RIGHT press ";
            hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 4);
            cout << "\'d\'\n\n";
            SetConsoleTextAttribute(hConsole, 7);
            cout << setw(80);
            cout << "Press any key to go back!\n\n";
            getch();
            showMenu();
        }
        else if(menuOption == 3) {
            system("cls");
            leaderBoardClass::createLeaderBoard();
            cout << "\n\n";
            cout << setw(70);
            cout << "Press any key to go back!\n\n";
            getch();
            showMenu();
        }
        else {
            system("cls");
            cout << "\n\n\n\n";
            cout << setw(80);
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 9);
            cout << "!Thanks For Playing BOMBER GAME!\n\n";
            SetConsoleTextAttribute(hConsole, 7);
            exit(0);
        }
    }

    void levelShow() {
        system("cls");
        cout << "\n\n\n\n";
        cout << setw(80);
        cout << "Select Level [Default - Easy]\n\n";
        cout << setw(67);
        cout << "1. Easy\n\n";
        cout << setw(69);
        cout << "2. Medium\n\n";
        cout << setw(67);
        cout << "3. Hard\n\n";
        cout << setw(72);
        cout << "4. Very Hard\n\n";
        cout << setw(80);

        cin >> levelOption;

        system("cls");

        cout << "Enter Your Name :";
        cin >> name;

        if(levelOption == 1) {
            numberOfEnemy = 5;
            life = 5;
            totalTime = -1;
        }
        else if(levelOption == 2) {
            numberOfEnemy = 5;
            life = 3;
            totalTime = -1;
        }
        else if(levelOption == 3) {
            numberOfEnemy = 10;
            life = 3;
            totalTime = 300;
        }
        else if(levelOption == 4) {
            numberOfEnemy = 10;
            life = 1;
            totalTime = 200;
        }

        startGame();
    }

    void startGame() {
        system("cls");
        drawGridClass *baseclass;
        Game game(row, col, numberOfEnemy, life, totalTime, name);
        baseclass = &game;
        baseclass->draw();
        int playerFlag = 0;
        int enemyDirection[numberOfEnemy];
        memset(enemyDirection, 0, sizeof enemyDirection);
        getch();
        while(1) {
            Sleep(50);
            playerFlag = game.playerMove();
            for(int idx = 0; idx < numberOfEnemy; idx++) {
                if(game.ifEnemyAlive(idx)) {
                    enemyDirection[idx] = game.enemyMove(enemyDirection[idx], idx);
                    if(enemyDirection[idx] == -1) {
                        playerFlag = -1;
                        break;
                    }
                }
            }
            if(playerFlag != 0) break;
            game.bombDestroy();
            game.printGrid();
        }

        if(playerFlag == 1) {
            system("cls");
            baseclass->printWinGrid();
            system("pause");
        }

        if(playerFlag == -1) {
            system("cls");
            baseclass->printLooseGrid();
            system("pause");
        }

        showMenu();
    }
};
