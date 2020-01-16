#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QDockWidget>
#include "mythread.h"
#include "mymemory.h"
#include "subwind.h"
#include <map>

using namespace std;

extern int winWidth;    //窗口宽度
extern int winHeigh;    //窗口高度
extern int myPosX;      //
extern int myPosY;
extern int LineNum;     //当前行
extern int LinePos;     //当前行内序号
extern int curPosX;     //当前光标坐标x
extern int curPosY;     //当前光标坐标y

extern int newLineNum;  //新一行的行号
extern int newLinePos;  //新一行的序号
extern int newCurPosX;  //新一行的光标x
extern int newCurPosY;  //新一行的光标y
extern int lineNumpp;   //行偏移量

extern MyMemory * memory;//存储字符的类
extern int sec;             //计时器秒数
extern bool AllowBlock;     //允许块操作
extern map<QChar,bool> mpc; //表驱动
extern struct BlockOt * BlockPos;//存放块操作的向量
extern QString editText;        //搜索框
extern QString replText;        //替换框

//允许块操作
extern bool BlockOperation;
//记录块操作的起始位置
typedef struct BlockOt{
    int startLineNum;
    int startLinePos;
    int endLineNum;
    int endLinePos;
    BlockOt():startLineNum(0),startLinePos(0),endLineNum(0),endLinePos(0){}
}Bo,*pBo;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //槽函数
    void dealSignal();
    void getImage(QImage);
    void dealClose();
    void saveFile();
    void helpCal();

protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //鼠标事件
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    //键盘事件
    void keyPressEvent(QKeyEvent *);
    void keyReleaseEvent(QKeyEvent *);
    //关闭事件
    void closeEvent(QCloseEvent *);
    //时间事件
    void timerEvent(QTimerEvent *);
    //窗口大小改变
    void resizeEvent(QResizeEvent *);

signals:
    void startThreat();//启动子线程的信号
private:
    Ui::MainWindow *ui;
    subWind w;
    QImage image; //画布
    MyThread * myT;//自定义线程对象
    QThread * thread;
    QStatusBar *sBar;
    QLabel *leftLab1;
    QLabel *leftLab2;
    QLabel *rightLab1;
    QLabel *rightLab2;
    QAction *pSearch;
    map<int,char> mpt1;//表驱动
    map<int,char> mpt2;
    bool capalock;//大写锁定
    int timerId1;//计时器
    QClipboard * board;//剪切板

    bool isDorNorF(QChar c);

};

#endif // MAINWINDOW_H
