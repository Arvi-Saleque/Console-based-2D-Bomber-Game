using namespace std;
class drawGridClass {
protected:
    string *grid;
    int row, col;
    void virtual generateBasicGrid() = 0;
    void virtual generateBlocks() = 0;
    void virtual generatePlayer() = 0;
    void virtual generateEnemy(int) = 0;
    void virtual generateDestination() = 0;
    void virtual printGrid() = 0;
public:
    void virtual draw() = 0;
    void virtual printWinGrid() = 0;
    void virtual printLooseGrid() = 0;
    void generateTheGrid() {
        grid = new string[row + 1];
    }

    void deleteTheGrid() {
        delete grid;
    }
};
