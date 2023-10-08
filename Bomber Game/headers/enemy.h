class Enemy {
    COORD position;
    bool alive;
public:
    bool operator ==(const pair<int, int> a) {
        pair<int, int> b = {position.X, position.Y};
        return a == b;
    }
    friend class Game;
};
