#include "headers/mypair.h"
using namespace std;
class leaderBoardClass {
public:
    static void createLeaderBoard() {
        ifstream file("leaderboard.txt");
        set<MyPair<string, int>> st;
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                size_t pos = line.find(":");
                if (pos != string::npos) {
                    string name = line.substr(0, pos);
                    int score = stoi(line.substr(pos + 1));
                    MyPair<string, int> mypair(name, score);
                    st.insert(mypair);
                }
            }
            file.close();
        }
        cout << setw(60);
        cout << "Leaderboard:" << endl;
        int rankk = 1;
        for(auto x : st) {
            cout << setw(50);
            cout << rankk << ": " << x.f << " score = " << x.s << "\n";
        }
    }

    static void SaveScore(string str, int score) {
        ofstream file("leaderboard.txt", ios::app);
        if (file.is_open()) {
            file << str  << ": " << score << endl;
            file.close();
        }
    }

};
