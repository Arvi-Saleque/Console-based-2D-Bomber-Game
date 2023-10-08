#include "drawgrid.h"
#include "enemy.h"
#include "bomb.h"
using namespace std;
#define generateRandomValue(l, r) (uniform_int_distribution<long long int>(l, r)(mt))
mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());

int kx[] = {1, -1, 0, 0};
int ky[] = {0, 0, 1, -1};
int qx[] = {1, -1, 0, 0, -1, -1, 1, 1};
int qy[] = {0, 0, 1, -1, -1, 1, -1, 1};

struct cmp1 {
    bool operator()(COORD A, COORD B) const {
        if(A.X == B.X) return (A.Y < B.Y);
        else return (A.X < B.X);
    }
};


class Game : public drawGridClass{
    int numberOfBlock, numberOfEnemy, maxNoBomb, score, life, timeOfGame;
    COORD playerPosition, destinationPosition;
    string playerName;
    Enemy *enemy;
    deque<Bomb> bombInfo;
    vector<MyPair<COORD, bool>> pointsPositions;
    map<COORD, int, cmp1> idOfBombXY;
public:

    Game(int _row, int _col, int numEnemy, int _life, int _time, string name) {
        enemy = new Enemy[numEnemy];
        for(int idx = 0; idx < numEnemy; idx++) {
            enemy[idx].alive = true;
        }
        row = _row;
        col = _col;
        numberOfEnemy = numEnemy;
        maxNoBomb = 3;
        score = 0;
        life = _life;
        timeOfGame = _time;
        playerName = name;
    }

    void draw() {
        generateBasicGrid();
        generateBlocks();
        generatePoints();
        generatePlayer();
        for(int idx = 0; idx < numberOfEnemy; idx++) {
            generateEnemy(idx);
        }
        generateDestination();
        printGrid();
    }

    void generateBasicGrid() {
        generateTheGrid();
        for(int i = 0; i < row; i++) {
            string tmp = "";
            for(int j = 0; j < col; j++) {
                if(i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                    tmp.push_back('#');
                }
                else {
                    tmp.push_back('.');
                }
            }
            grid[i] = tmp;
        }
    }

    void generateBlocks() {
        numberOfBlock = generateRandomValue(200, 300);
        for(int i = 1; i <= numberOfBlock; i++) {
            COORD point = getRandomPoint();
            grid[point.X][point.Y] = '#';
        }
    }

    void generatePoints() {
        int numberOfPoints = generateRandomValue(20, 25);
        for(int i = 1; i <= numberOfPoints; i++) {
            COORD point = getRandomPoint();
            if(grid[point.X][point.Y] == '.') {
                grid[point.X][point.Y] = '+';
                MyPair<COORD, bool> mypair(point, true);
                pointsPositions.push_back(mypair);
            }
            else {
                i--;
            }
        }
    }

    void removePoints(COORD point) {
        for(auto &x : pointsPositions) {
            if(x.f.X == point.X && x.f.Y == point.Y) {
                x.s = 0;
                break;
            }
        }
    }

    void generatePlayer() {
        COORD point;
        point.X = generateRandomValue(15, 18);
        point.Y = generateRandomValue(1, 5);
        grid[point.X][point.Y] = 'P';
        playerPosition = point;
    }

    void generateEnemy(int idx) {
        COORD point = getRandomPoint();
        grid[point.X][point.Y] = 'E';
        enemy[idx].position = point;
    }

    void generateDestination() {
        COORD point;
        point.X = generateRandomValue(1, 5);
        point.Y = generateRandomValue(72, 77);
        grid[point.X][point.Y] = 'D';
        destinationPosition = point;
        for(int i = 0; i < 8; i++) {
            for(int j = 1; j <= 2; j++) {
                int x = point.X + qx[i]*j;
                int y = point.Y + qy[i]*j;
                grid[x][y] = '#';
            }
        }
    }

    COORD getRandomPoint() {
        COORD point = {-1, -1};
        while(!valid(point)) {
            point.X = generateRandomValue(0, row);
            point.Y = generateRandomValue(0, col);
        }
        return point;
    }

    bool valid(COORD point) {
        int x = point.X, y = point.Y;
        if(x < 1 || x > row - 2 || y < 1 || y > col - 2) return false;
        return true;
    }

    void printGrid() {
        cout << "\n";
        cout << setw(35);
        cout << "Score : " << score;
        cout << setw(25);
        cout << "Life : " << life;
        if(timeOfGame < 0) {
            cout << setw(25);
            cout << "Time : NO LIMIT" << "\n\n\n";
        }
        else {
            cout << setw(25);
            cout << "Time : " << timeOfGame  << "\n\n\n";
        }
        for(int i = 0; i < bombInfo.size(); i++) {
            grid[bombInfo[i].position.X][bombInfo[i].position.Y] = '*';
        }
        for(auto x : pointsPositions) {
            if(x.s == 1) {
                grid[x.f.X][x.f.Y] = '+';
            }
        }
        HANDLE hConsole;
        for(int i = 0; i < row; i++) {
            cout << setw(20);
            for(int j = 0; j < col; j++) {
                if(i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] == 'P') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 11);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] == 'D') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] == 'E') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 4);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] == '*') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 12);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] == '+') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 14);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    cout << grid[i][j];
                }
            }
            cout << "\n";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }

    void printWinGrid() {
        cout << setw(30) << "\n";
        cout << "Your Total Score is : " << score << "\n";
        cout << "\n\n\n\n";
        generateBasicGrid();
        grid[10][30] = 'W';
        grid[10][31] = 'I';
        grid[10][32] = 'N';
        HANDLE hConsole;
        for(int i = 0; i < row; i++) {
            cout << setw(20);
            for(int j = 0; j < col; j++) {
                if(grid[i][j] == '#') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] != '.') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    cout << grid[i][j];
                }
            }
            cout << "\n";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

        leaderBoardClass::SaveScore(playerName, score);
    }

    void printLooseGrid() {
        cout << "\n\n\n\n";
        generateBasicGrid();
        grid[10][30] = 'G';
        grid[10][31] = 'A';
        grid[10][32] = 'M';
        grid[10][33] = 'E';
        grid[10][34] = ' ';
        grid[10][35] = 'O';
        grid[10][36] = 'V';
        grid[10][37] = 'E';
        grid[10][38] = 'R';
        HANDLE hConsole;
        for(int i = 0; i < row; i++) {
            cout << setw(20);
            for(int j = 0; j < col; j++) {
                if(grid[i][j] == '#') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 9);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else if(grid[i][j] != '.') {
                    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
                    SetConsoleTextAttribute(hConsole, 2);
                    cout << grid[i][j];
                    SetConsoleTextAttribute(hConsole, 7);
                }
                else {
                    cout << grid[i][j];
                }
            }
            cout << "\n";
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});

        leaderBoardClass::SaveScore(playerName, score);
    }

    int playerMove() {
        if(timeOfGame > 0) {
            timeOfGame--;
            if(timeOfGame == 0) return -1;
        }
        if(life == 0) return -1;
        int curX = playerPosition.X, curY = playerPosition.Y;
        if(_kbhit()) {
            char cur = _getch();
            if(cur == 'j') {
                curY--;
            }
            else if(cur == 'l') {
                curY++;
            }
            else if(cur == 'i') {
                curX--;
            }
            else if(cur == 'k') {
                curX++;
            }
            else if(cur == 'x') {
                if(bombInfo.size() == maxNoBomb) {
                    return 0;
                }
                bombInfo.push_back(Bomb(bombInfo.size(), 20, {curX, curY}, true));
                idOfBombXY[{curX, curY}] = bombInfo.size() - 1;
                return 0;
            }
            int flag = 0;
            if(grid[curX][curY] == 'D') {
                flag = 1;
            }
            else if(grid[curX][curY] == 'E') {
                life--;
                if(life == 0) {
                    flag = -1;
                }
            }
            else if(grid[curX][curY] == '.') {
                updatePositionPlayer(curX, curY);
            }
            else if(grid[curX][curY] == '*') {
                life--;
                system("pause");
                system("cls");
                if(life == 0) {
                    flag = -1;
                }
            }
            else if(grid[curX][curY] == '+') {
                score += 10;
                removePoints({curX, curY});
                updatePositionPlayer(curX, curY);
            }
            return flag;
        }
    }

    bool ifEnemyAlive(int idx) {
        return enemy[idx].alive;
    }

    int enemyMove(int dir, int idx) {
        int curX = enemy[idx].position.X + kx[dir], curY = enemy[idx].position.Y + ky[dir];
        if(grid[curX][curY] == '*') {
            if(bombInfo[idOfBombXY[{curX, curY}]].time <= 10) {
                removeEnemy(curX, curY, idx);
                enemy[idx].alive = false;
                score += 100;
                return 0;
            }
            else {
               return generateRandomValue(0, 4);
            }
        }
        if(grid[curX][curY] == 'P') {
            life--;
            system("pause");
            system("cls");
            if(life == 0) {
                return -1;
            }
        }
        if(grid[curX][curY] == '.' || grid[curX][curY] == '+') {
            updatePositionEnemy(curX, curY, idx);
            return dir;
        }
        else {
            return generateRandomValue(0, 4);
        }
    }

    void updatePositionPlayer(int x, int y) {
        grid[x][y] = 'P';
        grid[playerPosition.X][playerPosition.Y] = '.';
        playerPosition.X = x;
        playerPosition.Y = y;
    }

    void updatePositionEnemy(int x, int y, int idx) {
        grid[x][y] = 'E';
        grid[enemy[idx].position.X][enemy[idx].position.Y] = '.';
        enemy[idx].position.X = x;
        enemy[idx].position.Y = y;
    }

    void removeEnemy(int x, int y, int idx) {
        grid[enemy[idx].position.X][enemy[idx].position.Y] = '.';
    }

    void bombDestroy() {
        for(int id = 0; id < bombInfo.size(); id++) {
            if(!bombInfo[id].flag) break;
            bombInfo[id].time--;
            if(bombInfo[id].time <= 10) {
                for(int i = 0; i < 4; i++) {
                    int x = bombInfo[id].position.X + kx[i];
                    int y = bombInfo[id].position.Y + ky[i];
                    if(x == 0 || x == row - 1 || y == 0 || y == col - 1) continue;
                    if(grid[x][y] == 'E') {
                        for(int j = 0; j < numberOfEnemy; j++) {
                            pair<int, int> checkPoint = {x, y};
                            if(enemy[j] == checkPoint) {
                                removeEnemy(x, y, j);
                                enemy[j].alive = false;
                                score += 100;
                            }
                        }
                    }
                    if(grid[x][y] == 'P') {
                        life--;
                        system("pause");
                        system("cls");
                    }
                    grid[x][y] = '*';
                }
            }
            if(bombInfo[id].time == 0) {
                for(int i = 0; i < 4; i++) {
                    int x = bombInfo[id].position.X + kx[i];
                    int y = bombInfo[id].position.Y + ky[i];
                    if(grid[x][y] == '*') {
                        if(playerPosition.X == x && playerPosition.Y == y) {
                            grid[x][y] = 'P';
                        }
                        else {
                            grid[x][y] = '.';
                        }
                    }
                }
                grid[bombInfo[id].position.X][bombInfo[id].position.Y] = '.';
                bombInfo.pop_front();
            }
        }
    }

};
