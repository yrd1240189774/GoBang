#include <graphics.h>

#include <conio.h>
#include "Myprint.h"


using namespace std;

int main()
{
    Myprint chess;
    initgraph(480, 480);
    chess.printboard();
    chess.printstart();
    /*while(true){
        chess.printboard();
        chess.printchess();
        if (chess.chessjudge(chess.currentPos.Y,chess.currentPos.X,chess.chessboard)){
            chess.printend();
            break;
        }
        if (chess.flag==-1) {
            chess.printact();
            chess.printmouse();
        }
        else{
            chess.Robot();
            chess.printact();
        }
    }*/
    getch();
    closegraph();
    return 0;
}