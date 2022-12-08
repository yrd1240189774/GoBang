//

// Created by 12401 on 2022/10/26.
//
#include <graphics.h>// 引用 EasyX 图形库
#include <iostream>
#include "Myprint.h"
#include <conio.h>
#include <algorithm>
#include <string>
#include <time.h>
#define ONE 10
#define TWO 100
#define THREE 1000
#define FOUR 10000
#define FIVE 1000000
#define BLOCKED_ONE 1
#define BLOCKED_TWO 10
#define BLOCKED_THREE 100
#define BLOCKED_FOUR 1000
#define deep  8
using namespace std;

double x=0,f=0;
int cut=0;

void Myprint::printboard() {
    BeginBatchDraw();
    setbkcolor(RGB(244, 164, 96));
    cleardevice();
    setlinestyle(PS_SOLID, 2);  // 画实线，宽度为2个像素
    setcolor(RGB(0, 0, 0));  // 设置为黑色
    for (int i = 1; i <= 15; i++)  // 画横线和竖线
    {
        char arr[4];
        wsprintf(arr, "%d", i);
        outtextxy(10, i * 30 - 10, 64 + i);
        outtextxy(i * 30 - 8, 10, arr);
        line(i * step, 1 * step, i * step, 15 * step);
        line(1 * step, i * step, 15 * step, i * step);
    }
    setfillcolor(BLACK);
    fillcircle(8 * step, 8 * step, step / 8);
    EndBatchDraw();
}

void Myprint::printchess() {
    BeginBatchDraw();
    setcolor(RGB(0, 0, 0));
    int step = 30;
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            if (chessboard[i][j] == 1) {
                setfillcolor(BLACK);
                fillcircle(j * step, i * step, step / 3);
            } else if (chessboard[i][j] == -1) {
                setfillcolor(WHITE);
                fillcircle(j * step, i * step, step / 3);
            }
        }
    }
    EndBatchDraw();
}

void Myprint::printmouse() {
    MOUSEMSG msg = GetMouseMsg();
    switch (msg.uMsg) {
        case WM_MOUSEMOVE:
            if (msg.x >= 30 && msg.x <= 450 && msg.y > 30 && msg.y <= 450) {
                waitPos.X = (msg.x + 15) / 30;
                waitPos.Y = (msg.y + 15) / 30;
            }
            break;
        case WM_LBUTTONUP:
            if (msg.x >= 15 && msg.x <= 465 && msg.y >= 15 && msg.y <= 465 &&
                chessboard[(msg.y + 15) / 30][(msg.x + 15) / 30] == 0) {
                //此处无子
                currentPos.X = (msg.x + 15) / 30;
                currentPos.Y = (msg.y + 15) / 30;
                chessboard[currentPos.Y][currentPos.X] = flag;
                flag *= -1;
            }
            break;
    }
}

void Myprint::printact() {
    BeginBatchDraw();
    setlinecolor(RED);              //设置线颜色
    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 2; x++) {
            //currentPos绘制
            //画横线
            line(currentPos.X * 30 - 15, currentPos.Y * 30 - 15 + y * 30,
                 currentPos.X * 30 - 5, currentPos.Y * 30 - 15 + y * 30);
            line(currentPos.X * 30 + 5, currentPos.Y * 30 - 15 + y * 30,
                 currentPos.X * 30 + 15, currentPos.Y * 30 - 15 + y * 30);
            //画竖线
            line(currentPos.X * 30 - 15 + 30 * y, currentPos.Y * 30 - 15,
                 currentPos.X * 30 - 15 + 30 * y, currentPos.Y * 30 - 5);
            line(currentPos.X * 30 - 15 + 30 * y, currentPos.Y * 30 + 5,
                 currentPos.X * 30 - 15 + 30 * y, currentPos.Y * 30 + 15);
            //waitPos绘制
            line(waitPos.X * 30 - 15, waitPos.Y * 30 - 15 + y * 30,
                 waitPos.X * 30 - 5, waitPos.Y * 30 - 15 + y * 30);
            line(waitPos.X * 30 + 5, waitPos.Y * 30 - 15 + y * 30,
                 waitPos.X * 30 + 15, waitPos.Y * 30 - 15 + y * 30);
            //画竖线
            line(waitPos.X * 30 - 15 + 30 * y, waitPos.Y * 30 - 15,
                 waitPos.X * 30 - 15 + 30 * y, waitPos.Y * 30 - 5);
            line(waitPos.X * 30 - 15 + 30 * y, waitPos.Y * 30 + 5,
                 waitPos.X * 30 - 15 + 30 * y, waitPos.Y * 30 + 15);
        }
    }
    EndBatchDraw();
}

bool Myprint::chessjudge(int y,int x,int board[16][16]) {
    //横向判断
    int arr[4] = {0}, index = 1;
    while (x - index > 0 && board[y][x - index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[0]++;
    }
    index = 1;
    while (x + index <= 15 && board[y][x + index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[0]++;
    }
    //纵向判断
    index = 1;
    while (y - index > 0 && board[y - index][x] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[1]++;
    }
    index = 1;
    while (y + index <= 15 && board[y + index][x] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[1]++;
    }
    //判断左上
    index = 1;
    while (x - index > 0 && y - index > 0 && board[y - index][x - index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[2]++;
    }
    index = 1;
    while (x + index <= 15 && y + index <= 15 && board[y + index][x + index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[2]++;
    }
    //判断右上
    index = 1;
    while (x - index > 0 && y + index <= 15 && board[y + index][x - index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[3]++;
    }
    index = 1;
    while (x + index <= 15 && y - index > 0 && board[y - index][x + index] == board[y][x] && board[y][x] != 0) {
        index++;
        arr[3]++;
    }
    for (index = 0; index < 4; index++) {
        if (arr[index] >= 4) {
            return true;
        }
    }
    return false;
}

void Myprint::printend() {
    //获取窗口句柄
    HWND hnd = GetHWnd();
    //设置窗口标题
    SetWindowText(hnd, "GoBang Game");
    //弹出窗口，提示用户操作
    int is_ok;
    if (flag==-1) {
        is_ok = MessageBox(hnd, "Black Win!", "Game Over", MB_OK);
    }
    else {
        is_ok = MessageBox(hnd, "White Win!", "Game Over", MB_OK);
    }
}

void Myprint::printstart() {
    //获取窗口句柄
    HWND hnd = GetHWnd();
    //设置窗口标题
    SetWindowText(hnd, "GoBang Game");
    //弹出窗口，提示用户操作
    int is_first;
    is_first=MessageBox(hnd, "You Fisrt?", "Game Start", MB_YESNO);
    if (is_first==IDNO) {
        chessboard[8][8] = 1;
        /*flag *= -1;*/
        while (true) {
            printboard();
            printchess();
            if (chessjudge(currentPos.Y, currentPos.X, chessboard)) {
                printend();
                break;
            }
            if (flag == -1) {
                printact();
                printmouse();
            } else {
                Robot();
                printact();
            }
        }
    }
    else{
        while(true){
            printboard();
            printchess();
            if (chessjudge(currentPos.Y,currentPos.X,chessboard)){
                printend();
                break;
            }
            if (flag==-1) {
                printact();
                printmouse();
            }
            else{
                Robot();
                printact();
            }
        }
    }
}

void Myprint::Attack(int y,int x,int flag,int Vmboard[16][16],int ScoreBoard[16][16]) {
    int empty=0;
    int count=1;
    int block=0;
    int roable=0;
    for (int i=x+1;true;i++){
        if (i>15){
            block++;
            break;
        }
        int tmp=Vmboard[y][i];
        if (flag==tmp){
            count++;
            /*cout<<cross->count<<'\t';*/
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[y][i+1]==0||Vmboard[y][i+1]==-flag||i+1>15){
                while (Vmboard[y][i]!=-flag&&i<=15&&roable+empty+count<=6){
                    roable++;
                    i++;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    for (int i=x-1;true;i--){
        if (i<1){
            block++;
            break;
        }
        int tmp=Vmboard[y][i];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[y][i-1]==0||Vmboard[y][i-1]==-flag||i-1<1){
                while (Vmboard[y][i]!=-flag&&i>=1&&roable+empty+count<=6){
                    roable++;
                    i--;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    ScoreBoard[y][x]+=ScoreGet(empty,count,block,roable);
    //竖向判断
    empty=0;
    count=1;
    block=0;
    roable=0;
    for (int i=y+1;true;i++){
        if (i>16){
            block++;
            break;
        }
        int tmp=Vmboard[i][x];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i+1][x]==0||Vmboard[i+1][x]==-flag||i+1>15){
                while (Vmboard[i+1][x]!=-flag&&i<=15&&roable+empty+count<=6){
                    roable++;
                    i++;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    for (int i=y-1;true;i--){
        if (i<1){
            block++;
            break;
        }
        int tmp=Vmboard[i][x];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i-1][x]==0||Vmboard[i-1][x]==-flag||i-1<1){
                while (Vmboard[i-1][x]!=-flag&&i>=1&&roable+empty+count<=6){
                    roable++;
                    i--;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    ScoreBoard[y][x]+=ScoreGet(empty,count,block,roable);
    //左上判断
    empty=0;
    count=1;
    block=0;
    roable=0;
    for (int i=y+1,j=x+1;true;i++,j++){
        if (i>15||j>15){
            block++;
            break;
        }
        int tmp=Vmboard[i][j];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i+1][j+1]==0||Vmboard[i+1][j+1]==-flag||i+1>15||j+1>15){
                while (Vmboard[i+1][j+1]!=-flag&&i<=15&&j<=15&&roable+empty+count<=6){
                    roable++;
                    i++;j++;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    for (int i=y-1,j=x-1;true;i--,j--){
        if (i<1||j<1){
            block++;
            break;
        }
        int tmp=Vmboard[i][j];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i-1][j-1]==0||Vmboard[i-1][j-1]==-flag||i-1<1||j-1<1){
                while (Vmboard[i-1][j-1]!=-flag&&i>=1&&j>=1&&roable+empty+count<=6){
                    roable++;
                    i--;j--;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    ScoreBoard[y][x]+=ScoreGet(empty,count,block,roable);
    //右上判断
    empty=0;
    count=1;
    block=0;
    roable=0;
    for (int i=y+1,j=x-1;true;i++,j--){
        if (i>15||j<1){
            block++;
            break;
        }
        int tmp=Vmboard[i][j];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i+1][j-1]==0||Vmboard[i+1][j-1]==-flag||i+1>15||j-1<1){
                while (Vmboard[i+1][j-1]!=-flag&&i<=15&&j>=1&&roable+empty+count<=6){
                    roable++;
                    i++;j--;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    for (int i=y-1,j=x+1;true;i--,j++){
        if (i<1||j>15){
            block++;
            break;
        }
        int tmp=Vmboard[i][j];
        if (flag==tmp){
            count++;
        }
        else if (tmp==-flag){
            block++;
            break;
        }
        else {
            if (Vmboard[i-1][j+1]==0||Vmboard[i-1][j+1]==-flag||i-1<1||j+1>15){
                while (Vmboard[i-1][j+1]!=-flag&&i>=1&&j<=15&&roable+empty+count<=6){
                    roable++;
                    i--;j++;
                }
                break;
            }
            else {
                empty++;
            }
        }
    }
    ScoreBoard[y][x]+=ScoreGet(empty,count,block,roable);
    /*cout<<ScoreBoard[y][x]<<'\t';*/
}

int Myprint::AllScore(Node_Tree *p) {
    clock_t start, finish;
    start = clock();
    int score = 0;
    int NumDash = 0;
    string array[100];
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            array[i] = array[i] + char(int(p->VmBoard[i][j] + 1) + '0');
            array[i + 15] = array[i + 15] + char(int(p->VmBoard[j][i] + 1) + '0');
        }
    }
    for (int k = 1; k <= 15; k++) {
        for (int i = k, j = 1; i <= 15; ++i, ++j) {
            array[k + 30] = array[k + 30] + char(int(p->VmBoard[i][j] + 1) + '0');
            array[k + 45] = array[k + 45] + char(int(p->VmBoard[16 - i][j] + 1) + '0');
            array[k + 60] = array[k + 60] + char(int(p->VmBoard[16 - j][i] + 1) + '0');
            array[k + 75] = array[k + 75] + char(int(p->VmBoard[j][i] + 1) + '0');
        }
    }
    array[61] = "0";
    array[31] = "0";
    //black
    string five[10] = {"22222", "1222211", "1122221"};//活五活四
    string four[10] = {"022221", "122220", "22212", "22122", "21222"};//冲四
    string three[10] = {"122211", "112221", "121221", "122121"};//活三
    string LowRank[10] = {"022211", "112220", "022121", "121220", "021221", "122120", "1211221", "1221121", "1212121",
                          "0122210"};//眠三
    string LiveTwo[10] = {"112211", "12121", "121121"};//活二
    string SleepTwo[10] = {"022111", "111220", "021211", "112120", "021121", "121120", "21112"};//眠二
    //white
    string Wfive[10] = {"00000", "1000011", "1100001"};//活五活四
    string Wfour[10] = {"200001", "100002", "00010", "00100", "01000"};//冲四
    string Wthree[10] = {"100011", "110001", "101001", "100101"};//活三
    string WLowRank[10] = {"200011", "110002", "200101", "101002", "201001", "100102", "1011001", "1001101", "1010101",
                           "2100012"};//眠三
    string WLiveTwo[10] = {"110011", "10101", "101101"};//活二
    string WSleepTwo[10] = {"200111", "111002", "201011", "110102", "201101", "101102", "01110"};//眠二
    for (int i = 1; i <= 90; i++) {
        int length = array[i].length();
        if (array[i].find(five[0], 0) < length) {
            score += 100000;
        }
        if (array[i].find(Wfive[0], 0) < length) {
            score -= 100000;
        }
        if (array[i].find(five[1], 0) < length || array[i].find(five[2], 0) < length) {
            score += 10000;
        }
        if (array[i].find(Wfive[1], 0) < length || array[i].find(Wfive[2], 0) < length) {
            score -= 10000;
        }
        if (array[i].find(four[0], 0) < length || array[i].find(four[1], 0) < length ||
            array[i].find(four[2], 0) < length || array[i].find(four[3], 0) < length ||
            array[i].find(four[4], 0) < length) {
            NumDash++;
        }
        if (array[i].find(three[0], 0) < length || array[i].find(three[1], 0) < length ||
            array[i].find(three[2], 0) < length || array[i].find(three[3], 0) < length) {
            score += 1000;
        }
        if (array[i].find(Wfour[0], 0) < length || array[i].find(Wfour[1], 0) < length ||
            array[i].find(Wfour[2], 0) < length || array[i].find(Wfour[3], 0) < length ||
            array[i].find(Wfour[4], 0) < length) {
            NumDash--;
        }
        if (array[i].find(Wthree[0], 0) < length || array[i].find(Wthree[1], 0) < length ||
            array[i].find(Wthree[2], 0) < length || array[i].find(Wthree[3], 0) < length) {
            score -= 1000;
        }
        if (array[i].find(LowRank[0], 0) < length || array[i].find(LowRank[1], 0) < length ||
            array[i].find(LowRank[2], 0) < length || array[i].find(LowRank[3], 0) < length ||
            array[i].find(LowRank[4], 0) < length || array[i].find(LowRank[5], 0) < length ||
            array[i].find(LowRank[6], 0) < length || array[i].find(LowRank[7], 0) < length ||
            array[i].find(LowRank[8], 0) < length || array[i].find(LowRank[9], 0) < length) {
            score += 100;
        }
        if (array[i].find(WLowRank[0], 0) < length || array[i].find(WLowRank[1], 0) < length ||
            array[i].find(WLowRank[2], 0) < length || array[i].find(WLowRank[3], 0) < length ||
            array[i].find(WLowRank[4], 0) < length || array[i].find(WLowRank[5], 0) < length ||
            array[i].find(LowRank[6], 0) < length || array[i].find(WLowRank[7], 0) < length ||
            array[i].find(WLowRank[8], 0) < length || array[i].find(WLowRank[9], 0) < length) {
            score -= 100;
        }
        if (array[i].find(LiveTwo[1], 0) < length || array[i].find(LiveTwo[2], 0) < length ||
            array[i].find(LiveTwo[0], 0) < length) {
            score += 100;
        }
        if (array[i].find(WLiveTwo[1], 0) < length || array[i].find(WLiveTwo[2], 0) < length ||
            array[i].find(WLiveTwo[0], 0) < length) {
            score -= 100;
        }
        if (array[i].find(SleepTwo[0], 0) < length || array[i].find(SleepTwo[1], 0) < length ||
            array[i].find(SleepTwo[2], 0) < length || array[i].find(SleepTwo[3], 0) < length ||
            array[i].find(SleepTwo[4], 0) < length || array[i].find(SleepTwo[5], 0) < length ||
            array[i].find(SleepTwo[6], 0) < length) {
            score += 10;
        }
        if (array[i].find(WSleepTwo[0], 0) < length || array[i].find(WSleepTwo[1], 0) < length ||
            array[i].find(WSleepTwo[2], 0) < length || array[i].find(WSleepTwo[3], 0) < length ||
            array[i].find(WSleepTwo[4], 0) < length || array[i].find(WSleepTwo[5], 0) < length ||
            array[i].find(WSleepTwo[6], 0) < length) {
            score -= 10;
        }
    }
    if (NumDash == 1 || NumDash == -1) {
        score += NumDash * 990;
    } else if (NumDash != 0) {
        score += NumDash * 1010;
    }
    finish = clock();
    x+=(double)(finish - start) / CLOCKS_PER_SEC;
    return score;
}

Myprint::Node_Tree *Myprint::createroot() {
    Node_Tree *head = new Node_Tree;
    memcpy(head->VmBoard, chessboard, sizeof(chessboard));
    /*head->score=AllScore(head);*/
    head->depth = 0;
    head->flag = flag;
    head->cnt = 0;
    head->Last = NULL;
    PrintScore(head);
    return head;
}

Myprint::Node_Tree *Myprint::createleaf(Node_Tree *p)  {
    p->son[p->cnt] = new Node_Tree;
    Node_Tree *tmp = p->son[p->cnt];
    tmp->cnt = 0;
    tmp->Last = p;
    tmp->depth = p->depth + 1;
    tmp->flag = -p->flag;
    tmp->Alpha=p->Alpha;
    tmp->Beta=p->Beta;
    memcpy(tmp->VmBoard, p->VmBoard, sizeof(p->VmBoard));
    tmp->VmBoard[p->site[p->cnt].Y][p->site[p->cnt].X] = p->flag;
    if (chessjudge(p->site[p->cnt].Y, p->site[p->cnt].X, tmp->VmBoard)) {
        if (tmp->depth % 2 == 0) {
            p->cnt++;
            tmp->Alpha = AllScore(tmp);
            tmp->result = 2;
            return tmp;
        } else {
            p->cnt++;
            tmp->Beta = AllScore(tmp);
            tmp->result = 1;
            return tmp;
        }
    }
    p->cnt++;
    if (tmp->depth!=8)PrintScore(tmp);
    return tmp;
}

void Myprint::PrintScore(Node_Tree *p) {
    /*cout<<1<<'\t';*/
    clock_t start,finish;
    start=clock();
    int scoreboard[16][16] = {0};
    int num=0;
    for (int i = 1; i <= 15; i++) {
        for (int j = 1; j <= 15; j++) {
            if (p->VmBoard[i][j] == 0) {
                num++;
                Attack(i, j,-p->flag, p->VmBoard,scoreboard);
                Attack(i, j,p->flag, p->VmBoard,scoreboard);
                /*cout<<scoreboard[i][j]<<'\t'<<1<<'\t';*/
                if (scoreboard[i][j]<50){
                    num--;
                }
                /*if (f==0)cout<<scoreboard[i][j]<<'\t';*/
            }
            /*else if (f==0) cout<<'w'<<'\t';*/
        }
        /*if (f==0)cout<<endl;*/
    }
    /*cout<<num<<'\t';*/
    f=1;
    if (p->depth>1)num=4;
    finish = clock();
    p->number=num;
    /*cout<<num<<endl;*/
    for (int k=0;k<num;k++){
        int max = 0;
        for (int i = 1; i <= 15; i++) {
            for (int j = 1; j <= 15; j++) {
                if (scoreboard[i][j]> max)
                {
                    /*cout<<scoreboard[i][j]<<'\t'<<1<<'\t';*/
                    max = scoreboard[i][j];
                    p->site[k].Y = i;
                    p->site[k].X = j;
                }
            }
        }
        scoreboard[p->site[k].Y][p->site[k].X] = 0;
    }
    /*cout<<p->site[0].Y<<'\t'<<p->site[0].X<<endl;*/
    x+=(double)(finish - start) / CLOCKS_PER_SEC;
}

Myprint::Node_Tree *Myprint::createlist(Myprint::Node_Tree *p) {
    Node_Tree *tmp = p;
    while (tmp->depth < deep) {
        if (tmp->result == 1 || tmp->result == 2) {
            /*cout<<tmp->score<<'\t';*/
            return tmp;
        }
        tmp = createleaf(tmp);
    }
    if (tmp->depth%2==0) {
        tmp->Alpha = AllScore(tmp);
    }
    /*cout<<tmp->score<<'\t';*/
    else {
        tmp->Beta= AllScore(tmp);
    }
    return tmp;
}

Myprint::Node_Tree *Myprint::Minimax(Myprint::Node_Tree *p) {
    /*cout<<cut++<<'\t';*/
    Node_Tree *tmp = p;
    /*cout<<p->depth<<'\t';*/
    while (tmp->depth != 0) {
        if (tmp->depth%2==0&&tmp->Alpha<tmp->Last->Beta){
            tmp->Last->Beta=tmp->Alpha;
        }
        else if (tmp->depth%2==1&&tmp->Beta>tmp->Last->Alpha){
            tmp->Last->Alpha=tmp->Beta;
        }
       /* Node_Tree *del=tmp;*/
        tmp = tmp->Last;
        /*if (del->depth>=3)delete del;*/
        if (tmp->Beta<=tmp->Alpha&&tmp->depth!=0){
            Minimax(tmp);
        }
        else if (tmp->cnt == tmp->number){
            Minimax(tmp);
        }
        else {
            Node_Tree *n = createlist(tmp);
            Minimax(n);
        }
    }
}

void Myprint::Robot() {
    f=0;
    Node_Tree *head = createroot();
    Minimax(createlist(head));
    /*cout<<head->son[0]->score<<'\t'<<head->son[1]->score<<'\t'<<head->son[2]->score<<endl;*/
    int max = head->son[0]->Beta;
    currentPos.Y = head->site[0].Y;
    currentPos.X = head->site[0].X;
    for (int i = 1; i < head->number; i++) {
        if (head->son[i]->Beta > max) {
            max = head->son[i]->Beta;
            currentPos.Y = head->site[i].Y;
            currentPos.X = head->site[i].X;
        }
    }
    /*cout<<max<<'\t'<<head->son[0]->Beta<<endl;*/
    cout<<x<<'\t'<<head->son[0]->Beta<<'\t'<<max<<endl;
    x=0;
    /*cout<<head->site[1].Y<<'\t'<<head->site[1].X<<1<<endl;*/
    /*cout<<head->son[0]->Beta<<'\t'<<max<<endl;*/
    chessboard[currentPos.Y][currentPos.X] = flag;
    flag *= -1;
}

int Myprint::ScoreGet(int empty,int count,int block,int roable){
    /*cout<<empty<<'\t'<<count<<'\t'<<block<<'\t'<<roable<<endl;*/
    //没有空位
    if (count+empty+roable>=5){
        if(empty == 0) {
            if(count >= 5) return FIVE;
            if(block == 0) {
                switch(count) {
                    case 1: return 0;
                    case 2: return TWO;
                    case 3: return THREE;
                    case 4: return FOUR;
                    case 5: return FIVE;
                }
            }

            if(block == 1) {
                switch(count) {
                    case 1: return 0;
                    case 2: return BLOCKED_TWO;
                    case 3: return BLOCKED_THREE;
                    case 4: return BLOCKED_FOUR;
                    case 5: return FIVE;
                }
            }
        }
        else if(empty == 1) {
            //第1个是空位
            if(block == 0) {
                switch(count) {
                    case 2: return TWO/2;
                    case 3: return THREE;
                    case 4: return BLOCKED_FOUR;
                    case 5: return FOUR;
                }
            }

            if(block == 1) {
                switch(count) {
                    case 2: return BLOCKED_TWO;
                    case 3: return BLOCKED_THREE;
                    case 4: return BLOCKED_FOUR;
                    case 5: return BLOCKED_FOUR;
                }
            }
        }
        else if(empty == 2) {
            //有二个是空位
            if(block == 0) {
                switch(count) {
                    case 3: return BLOCKED_THREE;
                    case 4: return THREE-TWO;
                    case 5: return BLOCKED_FOUR-TWO;
                    case 6: return FOUR;
                }
            }

            if(block == 1) {
                switch(count) {
                    case 3: return BLOCKED_THREE;
                    case 4: return BLOCKED_FOUR;
                    case 5: return BLOCKED_FOUR;
                    case 6: return FOUR;
                }
            }

            if(block == 2) {
                switch(count) {
                    case 4:
                    case 5:
                    case 6: return BLOCKED_FOUR;
                }
            }
        }
    }
    return 0;
}



