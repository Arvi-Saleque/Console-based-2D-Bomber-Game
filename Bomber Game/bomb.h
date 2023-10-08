class Bomb {
    int time, id;
    COORD position;
    bool flag;
public:
    Bomb(int i, int _t, COORD _p, bool _f) : id(i), time(_t), position(_p), flag(_f) {}
    friend class Game;
};
