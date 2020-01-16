#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymemory.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QPainter>
#include <QCursor>
#include <QTextStream>//只能操作文本
#include <QFile>
#include <QString>
#include <QDebug>
#include <QByteArray>
#include <QEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QBrush>
#include <QPoint>
#include <map>
//#include <Windows.h>
#include <QClipboard>

using namespace std;
int winWidth;    //窗口宽度
int winHeigh;    //窗口高度
int myPosX;      //
int myPosY;
int LineNum;     //当前行
int LinePos;     //当前行内序号
int curPosX;     //当前光标坐标x
int curPosY;     //当前光标坐标y
int newLineNum;  //新一行的行号
int newLinePos;  //新一行的序号
int newCurPosX;  //新一行的光标x
int newCurPosY;  //新一行的光标y
int lineNumpp;   //行偏移量

MyMemory * memory;//存储字符的类
int sec;             //计时器秒数
bool AllowBlock;     //允许块操作
map<QChar,bool> mpc; //表驱动
struct BlockOt * BlockPos;//存放块操作的向量
QString editText;        //搜索框
QString replText;        //替换框
bool BlockOperation;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("MiniWord");
    memory = new MyMemory();
    memory->addNewLineInTail("");
    BlockPos = new Bo();                    //记录块操作的起始位置
    timerId1 = this->startTimer(500);       //设定光标计时器 500ms
    board = QApplication::clipboard();      //剪切板相关
    BlockOperation = false;                 //初始状态不允许块操作
    lineNumpp = 0;
    LineNum = 1;
    LinePos = 0;
    newLineNum = 0;
    newLinePos = 0;
    newCurPosX = 0;
    newCurPosY = 0;
    sec = 0;
    AllowBlock = false;

    //页面相关
    QMenuBar *mBar = menuBar();
    //添加菜单
    QMenu *pFile = mBar->addMenu("文件");

    //添加菜单项
    QAction * pNew = pFile->addAction("新建");
    connect(pNew, &QAction::triggered,
            [=]()
            {
                //qDebug() << "新建按钮被按下";
                if(memory->getChangeState() == true){
                    int ret = QMessageBox::question(this,"询问","新建文本前是否保存当前内容");
                    if(ret == QMessageBox::Yes)
                        saveFile();
                }
                delete memory;
                memory = new MyMemory();        //重新申请内存
                memory->addNewLineInTail("");
                memory->setChangeState(false);
                LineNum = 1;
                lineNumpp = 0;
                LinePos = 0;
                helpCal();              //重新计算坐标
                emit startThreat();     //绘图
            }
    );
    //添加分割线
    pFile->addSeparator();
    //菜单项
    QAction *pOpen = pFile->addAction("打开");
    connect(pOpen, &QAction::triggered,
            [=]()
            {
        if(memory->getChangeState() == true){
            int ret = QMessageBox::question(this,"询问","打开新文本前是否保存当前内容");
            if(ret == QMessageBox::Yes)
                saveFile();
        }
                //返回打开的路径
                QString path = QFileDialog::getOpenFileName(
                            this,
                            "open",
                            //上一级目录
                            "../",
                            //文件过滤规则 多种文件+每种文件的不同格式
                            //"souce(*.cpp *.h);;"
                            "Text(*.txt);;"
                            //"all(*.*)"
                            );
                qDebug() << path;

                if(!path.isEmpty()){
                    //读入内存
                    QFile file;
                    file.setFileName(path);
                    if(file.open(QIODevice::ReadOnly)){
                        QTextStream stream(&file);
                        stream.setCodec("UTF-8");
                        delete memory;
                        memory = new MyMemory();

                        while(!stream.atEnd()){
                            QString str;
                            str = stream.readLine();
                            memory->addNewLineInTail(str);
                        }
                        update();

                        file.close();
                        emit startThreat();
                    }
                }
            }
            );

    QAction *pSave = pFile->addAction("保存");
    connect(pSave,&QAction::triggered,
            [=](){
                //memory->setChangeState(false);
                saveFile();
                }
    );

    QAction *pQuit = pFile->addAction("关闭");
    connect(pQuit,&QAction::triggered,this,&MainWindow::close);

    pSearch = pFile->addAction("搜索");
    connect(pSearch,&QAction::triggered,
            [=](){
                w.show();
                }
    );


    QAction *pAbout = pFile->addAction("关于");
    connect(pAbout,&QAction::triggered,
            [=](){
                QMessageBox::about(this,"关于","QMiniWord2.0内测版\n   Built by 2018   ");
                }
    );

    //工具栏 菜单栏的快捷方式
    QToolBar *toolBar = addToolBar("toolBar");
    //添加快捷键
    //也可以换成按钮
    toolBar->addAction(pNew);
    toolBar->addAction(pOpen);
    toolBar->addAction(pSave);
    //状态栏
    sBar = statusBar();
    leftLab1 = new QLabel(this);
    leftLab1->setText("总行数:");
    sBar->addWidget(leftLab1);

    //从左往右依次添加标签
    leftLab2 = new QLabel("1",this);
    sBar->addWidget(leftLab2);

    //从右往左添加标签
    rightLab1 = new QLabel("当前行:",this);
    sBar->addPermanentWidget(rightLab1);
    rightLab2 = new QLabel("-",this);
    sBar->addPermanentWidget(rightLab2);
    myT = new MyThread;

    //创建子线程
    thread = new QThread(this);
    //自定义模块添加到子线程
    myT->moveToThread(thread);
    //启动子线程 但是并没有启动线程处理函数
    thread->start();

    //线程处理函数 singal- slot
    connect(pNew, &QAction::triggered, myT, &MyThread::drawText);
    connect(myT,&MyThread::updateText,this,&MainWindow::dealSignal);
    connect(this,&MainWindow::startThreat,myT,&MyThread::drawText);
    connect(myT, &MyThread::updateText, this, &MainWindow::getImage);
    connect(this, &MainWindow::destroyed,this, &MainWindow::dealClose);

    //表驱动
    /*表驱动
     * 用于改善switch case 或 多重if-else语句 的复杂度
     * 只需利用哈希表存下所需的逻辑
     * 添加逻辑转换为添加数据
     * 时间复杂度约为O(1)
     * 以下为表驱动所需哈希表的初始化
    */
    for(int i = Qt::Key_A, j = 0; i <= Qt::Key_Z; ++i, ++j){
        mpt1.insert(make_pair(i,'a' + j));
    }
    for(int i = Qt::Key_A, j = 0; i <= Qt::Key_Z; ++i, ++j){
        mpt2.insert(make_pair(i,'A' + j));
    }

    for(int i = Qt::Key_0, j = 0; i <= Qt::Key_9; ++i, ++j){
        mpt1.insert(make_pair(i,'0' + j));
    }
    mpt1.insert(make_pair(Qt::Key_Minus,'-'));
    mpt1.insert(make_pair(Qt::Key_Equal,'='));
    mpt1.insert(make_pair(Qt::Key_BracketLeft,'['));
    mpt1.insert(make_pair(Qt::Key_BracketRight,']'));
    mpt1.insert(make_pair(Qt::Key_Backslash,'\\'));
    mpt1.insert(make_pair(Qt::Key_Semicolon,';'));
    mpt1.insert(make_pair(Qt::Key_Apostrophe,'\''));
    mpt1.insert(make_pair(Qt::Key_Comma,','));
    mpt1.insert(make_pair(Qt::Key_Period,'.'));
    mpt1.insert(make_pair(Qt::Key_Slash,'/'));
    mpt1.insert(make_pair(Qt::Key_Space,' '));
    //mpt1.insert(make_pair(Qt::Key_Tab,""))

    mpt2.insert(make_pair(Qt::Key_ParenRight,')'));
    mpt2.insert(make_pair(Qt::Key_ParenLeft,'('));
    mpt2.insert(make_pair(Qt::Key_Exclam,'!'));
    mpt2.insert(make_pair(Qt::Key_At,'@'));
    mpt2.insert(make_pair(Qt::Key_NumberSign,'#'));
    mpt2.insert(make_pair(Qt::Key_Dollar,'$'));
    mpt2.insert(make_pair(Qt::Key_Percent,'%'));
    mpt2.insert(make_pair(Qt::Key_AsciiCircum,'^'));
    mpt2.insert(make_pair(Qt::Key_Ampersand,'&'));
    mpt2.insert(make_pair(Qt::Key_Asterisk,'*'));
    mpt2.insert(make_pair(Qt::Key_Question,'?'));
    mpt2.insert(make_pair(Qt::Key_Plus,'+'));
    mpt2.insert(make_pair(Qt::Key_Underscore,'_'));
    mpt2.insert(make_pair(Qt::Key_BraceLeft,'{'));
    mpt2.insert(make_pair(Qt::Key_BraceRight,'}'));
    mpt2.insert(make_pair(Qt::Key_Bar,'|'));
    mpt2.insert(make_pair(Qt::Key_Colon,':'));
    mpt2.insert(make_pair(Qt::Key_QuoteDbl,'\"'));
    mpt2.insert(make_pair(Qt::Key_Less,'<'));
    mpt2.insert(make_pair(Qt::Key_Greater,'>'));

    mpc.insert(make_pair(' ',1));
    mpc.insert(make_pair('!',1));
    mpc.insert(make_pair('@',1));
    mpc.insert(make_pair('#',1));
    mpc.insert(make_pair('$',1));
    mpc.insert(make_pair('%',1));
    mpc.insert(make_pair('^',1));
    mpc.insert(make_pair('&',1));
    mpc.insert(make_pair('*',1));
    mpc.insert(make_pair('(',1));
    mpc.insert(make_pair(')',1));
    mpc.insert(make_pair('-',1));
    mpc.insert(make_pair('_',1));
    mpc.insert(make_pair('+',1));
    mpc.insert(make_pair('=',1));
    mpc.insert(make_pair('[',1));
    mpc.insert(make_pair(']',1));
    mpc.insert(make_pair('{',1));
    mpc.insert(make_pair('}',1));
    mpc.insert(make_pair('\\',1));
    mpc.insert(make_pair('|',1));
    mpc.insert(make_pair(';',1));
    mpc.insert(make_pair(':',1));
    mpc.insert(make_pair('\'',1));
    mpc.insert(make_pair('\"',1));
    mpc.insert(make_pair(',',1));
    mpc.insert(make_pair('<',1));
    mpc.insert(make_pair('.',1));
    mpc.insert(make_pair('>',1));
    mpc.insert(make_pair('/',1));
    mpc.insert(make_pair('?',1));

    //判断是否开启了大写锁定
    if(LOBYTE(GetKeyState(VK_CAPITAL)))
        //qDebug() << "Lock On";
        capalock = true;
    else
        capalock = false;
        //qDebug() << "Lock off";
    //开启鼠标跟踪
    this->setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dealSignal(){

}

void MainWindow::paintEvent(QPaintEvent *){
    //指定绘图设备为窗口
    QPainter p(this);
    p.drawImage(0,45,image);
    //显示行数
    leftLab2->setText(QString::number(memory->getTotalLineNum()));
}

void MainWindow::dealClose(){

    //退出前结束线程
    thread->quit();
    thread->wait();
    //清除内存
    delete myT;
}

bool MainWindow::isDorNorF(QChar c){
    //判断是否为非中文字符
    if((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
            return true;
    return mpc[c];
}
void MainWindow::getImage(QImage temp){
    image = temp;
    update();//间接调用paintEvent()
}

void MainWindow::mouseMoveEvent(QMouseEvent *e){
    //鼠标移动事件
    int movX = e->x();
    int movY = e->y();
    if((movX >= 0 && movX <= winWidth) && (movY >= 45 && movY <= winHeigh))
        this->setCursor(Qt::IBeamCursor);    
    else
        this->setCursor(Qt::ArrowCursor);

}

void MainWindow::mousePressEvent(QMouseEvent *e){
    //鼠标点击事件
    if(AllowBlock == true)
        AllowBlock = false;

    myPosX = e->x();
    myPosY = e->y();

    //鼠标在窗口范围内则设置为编辑样式
    if((myPosX >= 0 && myPosX <= winWidth) && (myPosY >= 45 && myPosY <= winHeigh))
        this->setCursor(Qt::IBeamCursor);
    else
        this->setCursor(Qt::ArrowCursor);

    //计算行
    int row = (myPosY - 45) / 25 + 1;
    if(row > memory->getTotalLineNum()){
        row = memory->getTotalLineNum();
    }

    LineNum = row + lineNumpp;
    qDebug() << LineNum;

    //计算序号
    int lpos = (myPosX / 12) * 12;
    int cnt = 0;
    int newCurX = 0;
    for(int i = 0; i < ThreatStr.size() && lpos > 0; ++i){
        if(isDorNorF(ThreatStr[i])){
            lpos -= 12;
            ++cnt;
            newCurX += 12;
        }
        else{
            lpos -= 20;
            newCurX += 20;
            ++cnt;
        }
    }
    LinePos = cnt;
    curPosX = newCurX;
    qDebug() << "LineNum:" << LineNum  << " LineChars:" << memory->getLineCharNums(LineNum) << " LinePos:" << LinePos;
    //刷新
    emit startThreat();

}

void MainWindow::mouseReleaseEvent(QMouseEvent *e){
    //鼠标点击释放 通常用于块操作 记录尾
    int movPosX = e->x();
    int movPosY = e->y();
    //int newPosX = 0, newPosY = 0;

    if(movPosX <= 0) movPosX = 0;
    else if(movPosX >= winWidth) movPosX = winWidth;
    if(movPosY <= 45) movPosY = 45;
    else if(movPosY >= winHeigh) movPosY = winHeigh;
    qDebug() << "movPosX:" << movPosX << " movPosY:" << movPosY;

    int row = (movPosY - 45) / 25 + 1;
    if(row > memory->getTotalLineNum())
        row = memory->getTotalLineNum();
    newLineNum = row + lineNumpp;

    int lpos = (movPosX / 12) * 12;
    int cnt = 0;
    int newCurX = 0;
    for(int i = 0; i < ThreatStr.size() && lpos > 0; ++i){
        if(isDorNorF(ThreatStr[i])){
            lpos -= 12;
            ++cnt;
            newCurX += 12;
        }
        else{
            lpos -= 20;
            newCurX += 20;
            ++cnt;
        }
    }
    newLinePos = cnt;

    //记录块操作的首尾地址
    BlockPos->startLineNum = LineNum <= newLineNum ? LineNum : newLineNum;
    BlockPos->endLineNum = LineNum >= newLineNum ? LineNum : newLineNum;
    if(LineNum == newLineNum){
        BlockPos->startLinePos = LinePos < newLinePos ? LinePos : newLinePos;
        BlockPos->endLinePos = LinePos > newLinePos ? LinePos : newLinePos;
    }
    else{
        BlockPos->startLinePos = BlockPos->startLineNum == LineNum ? LinePos : newLinePos;
        BlockPos->endLinePos = BlockPos->endLineNum == LineNum ? LinePos : newLinePos;
    }
    QString str;
    str.clear();
    int i = 1;
    for(MyMemory::iterator it = memory->begin(); it != memory->end(); ++it){
        if(i == newLineNum){
            str = * it;
            break;
        }
        ++i;
    }
    i = newLinePos;
    newCurPosX = 0;
    for(QChar ch: str){
        if(!i) break;
        if(isDorNorF(ch))
            newCurPosX += 12;
        else newCurPosX += 22;
        -- i;
    }
    newCurPosY = (newLineNum - 1) * 25;
    if(LinePos != newLinePos || LineNum != newLineNum){
        AllowBlock = true;
        BlockOperation = true;
    }
}

void MainWindow::helpCal(){
    //计算光标
    QString str;
    str.clear();
    int i = 1;
    for(MyMemory::iterator it = memory->begin(); it != memory->end(); ++it){
        if(i == LineNum){
            str = * it;
            break;
        }
        ++i;
    }
    i = LinePos;
    curPosX = 0;
    for(QChar ch: str){
        if(!i) break;
        if(isDorNorF(ch))
            curPosX += 12;
        else curPosX += 22;
        -- i;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *e){
    //键盘事件
    if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_F){
        w.show();
    }
    else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_C){
        if(BlockOperation == true){
            qDebug() << "Copy online.";
            qDebug() << "sL:" << BlockPos->startLineNum << " sPo:" << BlockPos->startLinePos << " eL:" << BlockPos->endLineNum << " ePo:" << BlockPos->endLinePos;

            QString str = memory->blockCopy(BlockPos->startLineNum,BlockPos->startLinePos,BlockPos->endLineNum,BlockPos->endLinePos);
            qDebug() << "Cpoy str: " << str;
            board->setText(str);
            BlockOperation = false;
        }
    }
    else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_V){
        //QMessageBox::about(this,"抱歉","当然也不能粘贴哦");
        QString clipstr = board->text();
        memory->addStrInLine(clipstr,LineNum,LinePos);
        LinePos += clipstr.size();
        helpCal();
        qDebug() << "LineNum:" << LineNum << " LineChars:" << memory->getLineCharNums(LineNum) << " LinePos:" << LinePos;
        emit startThreat();
    }
    else if(e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_G){
        QMessageBox::about(this,"注意","CTRL+F可以替换了");
    }
    else if(e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return){
        //回车键
        if(BlockOperation == true){
            qDebug() << "Copy online.";
            qDebug() << "sL:" << BlockPos->startLineNum << " sPo:" << BlockPos->startLinePos << " eL:" << BlockPos->endLineNum << " ePo:" << BlockPos->endLinePos;

            QString str = memory->blockCopy(BlockPos->startLineNum,BlockPos->startLinePos,BlockPos->endLineNum,BlockPos->endLinePos);
            qDebug() << "Cpoy str: " << str;
            board->setText(str);
            BlockOperation = false;
        }

        //判断几种不同的回车情况
        //加入新行
        if(LinePos <= 0){
            memory->divideStrInLine(LineNum,0);
            ++ LineNum;
            LinePos = 0;
            helpCal();
        }
        else if(LinePos + 1 > memory->getLineCharNums(LineNum ) && LineNum >= memory->getTotalLineNum()){
            memory->addNewLineInTail("");
            ++LineNum;
            LinePos = 0;
            helpCal();
        }
        else if(LinePos + 1 > memory->getLineCharNums(LineNum)){
            ++ LineNum;
            memory->addNewLineInPargh("",LineNum);
            LinePos = 0;
            helpCal();
        }   
        else{
            memory->divideStrInLine(LineNum,LinePos);
            ++ LineNum;
            LinePos = 0;
            helpCal();
        }
        emit startThreat();

    }
    else if(e->modifiers() != Qt::ShiftModifier){
        //非shift组合键的情况
        switch(e->key()){
        case Qt::Key_Backspace:
            if(AllowBlock == true)
                AllowBlock = false;

            if(BlockOperation == true){
                //执行块操作 删除
                qDebug() << "块操作-删除";
                memory->blockDelete(BlockPos->startLineNum,BlockPos->startLinePos,BlockPos->endLineNum,BlockPos->endLinePos);
                LineNum = BlockPos->startLineNum;
                LinePos = BlockPos->startLinePos;
                curPosY = (LineNum - 1) * 25;
                helpCal();
                BlockOperation = false;
            }
            else{
                qDebug() << "非块操作-删除";
                if(LinePos <= 0){
                    if(LineNum - 1 >= 1)
                        LinePos = memory->getLineCharNums(LineNum - 1);
                    memory->deletLine(LineNum);
                    -- LineNum;
                    helpCal();
                }
                else if(LinePos >= memory->getLineCharNums(LineNum)){
                    memory->deleteCharInTail(LineNum);
                    -- LinePos;
                    helpCal();
                }
                else{
                    memory->deleteCharInLine(LineNum,--LinePos);
                    helpCal();
                }
            }
            emit startThreat();
            break;
        case Qt::Key_Delete:{//代码块避免程序崩溃
            int lefCharNum = memory->getLineCharNums(LineNum);
            if(LinePos <  lefCharNum){
                if(lefCharNum <= 1){
                    memory->deleteCharInTail(LineNum);
                }
                else memory->deleteCharInLine(LineNum,LinePos);
            }
            else if(LineNum + 1 <= memory->getTotalLineNum()){
                memory->deletLine(LineNum + 1);
            }
            emit startThreat();
            break;
        }
        case Qt::Key_PageUp:{
            qDebug() << "PageUp";
//            int totalLineNums = memory->getTotalLineNum();
//            int cnt = 25;//行间距为25
//            int containLineNums = (winHeigh - 20) / cnt;
//            if(lineNumpp <= containLineNums)
//                lineNumpp = 0;
//            else
//                lineNumpp -= containLineNums;
//            emit startThreat();
            break;
        }
        case Qt::Key_PageDown:{
            qDebug() << "PageDown";
//            int totalLineNums = memory->getTotalLineNum();
//            qDebug() << totalLineNums;
//            int cnt = 25;//行间距为25
//            int containLineNums = (winHeigh - 20) / cnt;
//            qDebug() << containLineNums;
//            //剩余内容 total - linepp - contain <= contain linepp =  total  - contain
//            if(totalLineNums - lineNumpp <= 2 * containLineNums && totalLineNums - lineNumpp >= containLineNums){
//                //小于等于一页
//                lineNumpp += totalLineNums - containLineNums;
//            }
//            else if (totalLineNums - lineNumpp > 2 * containLineNums){
//                lineNumpp += containLineNums;
//            }
//            emit startThreat();
            break;
        }
        case Qt::Key_Up:
            if(LineNum+lineNumpp -  1 >= 1){
                -- LineNum;
                int lasCharNum = memory->getLineCharNums(LineNum +lineNumpp);
                if(LinePos >= lasCharNum){
                    LinePos = lasCharNum;
                }
            }
            emit startThreat();
            break;
        case Qt::Key_Down:
            if(LineNum +lineNumpp + 1 <= memory->getTotalLineNum()){
                ++ LineNum;
                int nextCharNum = memory->getLineCharNums(LineNum+lineNumpp);
                if(LinePos >= nextCharNum)
                    LinePos = nextCharNum;
                helpCal();
            }
            emit startThreat();
            break;
        case Qt::Key_Left:
            if(LinePos - 1 >= 0){
                LinePos -= 1;
                helpCal();
            }
            else{
                if(LineNum+lineNumpp - 1 >= 1){
                    -- LineNum;
                    LinePos = memory->getLineCharNums(LineNum+lineNumpp);
                    helpCal();
                }
            }
            emit startThreat();
            break;
        case Qt::Key_Right:
            if(LinePos+ 1 <= ThreatStr.size()){

                if(isDorNorF(ThreatStr[LinePos])){
                    curPosX += 12;
                }
                else curPosX += 20;
                LinePos += 1;
            }
            else{
                //跳下一行 如果有一下一行的话
                if(LineNum +lineNumpp + 1 <= memory->getTotalLineNum()){
                    ++ LineNum;
                    LinePos = 0;
                    curPosX = 0;
                }
            }
            emit startThreat();
            break;
        case Qt::Key_CapsLock:
            if(LOBYTE(GetKeyState(VK_CAPITAL))) {
                //qDebug() << "大写锁定打开";
                capalock = true;
            }
            else {
                //qDebug() << "大写锁定关闭";
                capalock = false;
            }
            break;
        default:
            //字符输入
            if(!capalock){
                //小写
                //表驱动的应用
                //先查找是否存在对应的输入 然后 打印对应的值
                if(mpt1.find(e->key())!= mpt1.end()){
                    memory->addCharInLine(mpt1[e->key()],LineNum + lineNumpp,LinePos++);
                    curPosX += 12;
                }
                else if(mpt2.find(e->key())!= mpt2.end()){
                    memory->addCharInLine(mpt2[e->key()],LineNum+lineNumpp,LinePos++);
                    curPosX += 12;
                }
                emit startThreat();
            }
            else{
                //大写
                if(mpt2.find(e->key()) != mpt2.end()){
                    memory->addCharInLine(mpt2[e->key()],LineNum+lineNumpp,LinePos++);
                    curPosX += 12;
                }
                else if(mpt1.find(e->key())!= mpt1.end()){
                    memory->addCharInLine(mpt1[e->key()],LineNum+lineNumpp,LinePos++);
                    curPosX += 12;
                }
                emit startThreat();
            }
            break;
        }
    }
    else if(e->modifiers() == Qt::ShiftModifier){
        //字符输入
        //大写锁定下 加shift为小写 反之为大写
        if(capalock){
            if(mpt1.find(e->key())!= mpt1.end()){
                memory->addCharInLine(mpt1[e->key()],LineNum+lineNumpp,LinePos++);
                curPosX += 12;
            }

            else if(mpt2.find(e->key())!= mpt2.end()){
                memory->addCharInLine(mpt2[e->key()],LineNum+lineNumpp,LinePos++);
                curPosX += 12;
            }

            emit startThreat();
        }
        else{
            if(mpt2.find(e->key()) != mpt2.end()){
                memory->addCharInLine(mpt2[e->key()],LineNum+lineNumpp,LinePos++);
                curPosX += 12;
            }
            else if(mpt1.find(e->key())!= mpt1.end()){
                memory->addCharInLine(mpt1[e->key()],LineNum+lineNumpp,LinePos++);
                curPosX += 12;
            }
            emit startThreat();
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e){
    if(e->key() == Qt::Key_CapsLock){
        if(LOBYTE(GetKeyState(VK_CAPITAL))) {
            //qDebug() << "大写锁定打开";
            capalock = true;
        }
        else {
//            qDebug() << "大写锁定关闭";
            capalock = false;
        }
    }
}

void MainWindow::saveFile(){
    //QTextStream下保存文本文件
    QString path = QFileDialog::getSaveFileName(this,"save","../","TXT(*.txt)");
    if(path.isEmpty() == false){
        QFile file;
        file.setFileName(path);
        bool isopen = file.open(QIODevice::Text | QIODevice::WriteOnly);
        if(isopen){
            //QString str;
            QTextStream out(&file);
            //int cnt = 0;
            for(MyMemory::iterator it = memory->begin(); it != memory->end(); ++it){
                out << *it << endl;
            }
        }
        memory->setChangeState(false);//保存完毕才允许修改状态
        file.close();
    }

}

void MainWindow::closeEvent(QCloseEvent *e){

    QMessageBox msgBox;
    //这里加一个判断是否已经保存过了
    if(memory->getChangeState() == true){
        msgBox.setText("文本内容已更新但未保存");
        msgBox.setInformativeText("你想保存更改吗?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        int ret = msgBox.exec();
        switch(ret){
        case QMessageBox::Save:
            saveFile();
            e->accept();
            break;
        case QMessageBox::Discard:
            e->accept();
            break;
        case QMessageBox::Cancel:
            e->ignore();
            break;
        default:
            break;
        }
    }
    else
        qDebug() << "文本处于保存状态 直接关闭";

}

void MainWindow::timerEvent(QTimerEvent *e){
    //重写时间事件
    //每500ms全局变量sec自增一次
    //当sec%2==0时画光标
    if(e->timerId() == timerId1){
        if(sec >= 255) sec = 0; //防止sec溢出
        ++ sec;
        emit startThreat();//绘图
    }
}

void MainWindow::resizeEvent(QResizeEvent *){
    //获取窗体的大小
    winWidth = frameGeometry().width();
    winHeigh = frameGeometry().height();
    emit startThreat();//绘图
}
