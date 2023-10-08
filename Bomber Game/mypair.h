template <typename first, typename second>
class MyPair {
    first f;
    second s;
public:
    MyPair(first _f, second _s) : f(_f), s(_s) {}
    friend bool operator < (MyPair<first, second> A, MyPair<first, second> B) {
        return (A.s > B.s);
    }
    friend class Game;
    friend class leaderBoardClass;

};
