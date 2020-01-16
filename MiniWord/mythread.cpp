#include "mythread.h"
#include "mymemory.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPoint>
#include <QImage>
#include <QDebug>
#include <QColor>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QRect>
#include <queue>

using namespace std;

QString ThreatStr;
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}

bool MyThread::isDigOrNOrF(QChar c){
    if((c >= 'A' && c <= 'Z')||(c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
            return true;
    return mpc[c];
}

void MyThread::drawText(){
    //定义QImage绘图设备

    QImage image(winWidth,winHeigh - 105,QImage::Format_ARGB32);
    //QImage image(1000,1000,QImage::Format_ARGB32);
    image.fill(QColor(255,255,255));
    //定义绘图设备
    QPainter p(&image);

    QFont font = p.font();

    font.setFamily("MONACO");
    //设定字体大小

    font.setPixelSize(20);
    p.setFont(font);

    //下面是画矩形区域 用于块操作的直观定位
    if(AllowBlock == true){
        //AllowBlock = false;
        if(BlockPos->startLineNum != BlockPos->endLineNum){
            if(BlockPos->endLineNum - BlockPos->startLineNum > 1){
                queue<int> que;
                for(int k = BlockPos->startLineNum + 1; k < BlockPos->endLineNum; ++k)
                    que.push(k);
                while(!que.empty()){
                    int k = que.front();
                    que.pop();
                    int curLen = memory->helpCalCurX(k);
                    QRect rect(0,(k - 1) * 25, curLen,22);
                    QBrush brush(QColor(0,255,255), Qt::SolidPattern);
                    p.setBrush(brush);
                    p.fillRect(rect,brush);
                }
            }

            int BlockStartCurX = 0;
            int BlockStartCurY = (BlockPos->startLineNum - 1) * 25;

            int BlockEndCurX = 0;
            int BlockENdCurY = (BlockPos->endLineNum - 1) * 25;
            QString temp1,temp2;
            int num = 0;
            for(MyMemory::iterator it = memory->begin(); it != memory->end(); ++it){
                if(num + 1 == BlockPos->startLineNum)
                    temp1 = *it;
                if(num + 1 == BlockPos->endLineNum){
                    temp2 = *it;
                    break;
                }
                ++num;
            }
            int l1 = memory->getLineCharNums(BlockPos->startLineNum);
            for(int i = 0; i < BlockPos->startLinePos; ++i){
                if(isDigOrNOrF(temp1[i]))
                    BlockStartCurX += 12;
                else
                    BlockStartCurX += 22;
            }
            int curLen1 = BlockStartCurX;
            for(int i = BlockPos->startLinePos; i < l1 ; ++i){
                if(isDigOrNOrF(temp1[i]))
                    curLen1 += 12;
                else
                    curLen1 += 22;
            }

            for(int i = 0 ; i < BlockPos->endLinePos; ++i){
                if(isDigOrNOrF(temp2[i]))
                    BlockEndCurX += 12;
                else
                    BlockEndCurX += 22;
            }

            QRect rect1(BlockStartCurX,BlockStartCurY,curLen1 - BlockStartCurX,22);
            QBrush brush(QColor(0,255,255), Qt::SolidPattern);
            p.setBrush(brush);
            p.fillRect(rect1,brush);

            QRect rect2(0,BlockENdCurY,BlockEndCurX,22);
            p.fillRect(rect2,brush);

        }
        else{
            int BlockStartCurX = 0;
            int BlockStartCurY = (BlockPos->startLineNum - 1) * 25;
            int BlockEndCurX = 0;
            QString strtemp;
            int num = 0;
            for(MyMemory::iterator it = memory->begin(); it != memory->end(); ++it){
                if(num + 1 == BlockPos->startLineNum){
                    strtemp = * it;
                    break;
                }
                ++ num;
            }
            for(int i = 0;i < BlockPos->startLinePos; ++i){
                if(isDigOrNOrF(strtemp[i]))
                    BlockStartCurX += 12;
                else
                    BlockStartCurX += 22;
            }
            BlockEndCurX = BlockStartCurX;
            for(int i = BlockPos->startLinePos; i < BlockPos->endLinePos; ++i){
                if(isDigOrNOrF(strtemp[i]))
                    BlockEndCurX += 12;
                else
                    BlockEndCurX += 22;
            }

            QRect rect(BlockStartCurX,BlockStartCurY,BlockEndCurX - BlockStartCurX,22);
            QBrush brush(QColor(0,255,255), Qt::SolidPattern);
            p.setBrush(brush);
            p.fillRect(rect,brush);
        }
    }

    int posX = 0, posY = 20, cnt = 25;
    int i = 0;
    //行间距为25
    int k = 1;
    MyMemory::iterator it = memory->begin();
    while(k < lineNumpp){
        ++ k;
        ++it;
    }
    for( ; it != memory->end(); ++it){
        if(i + 1 == LineNum)
            ThreatStr = *it;
        p.drawText(posX, posY + i * cnt, *it);
        ++i;
    }
    curPosY = (LineNum - lineNumpp - 1) * 25;
    if(sec % 2 == 0){
        //画光标
        QPoint startPoint(curPosX,curPosY);
        QPoint endPoint(curPosX, 22 + curPosY);
        p.drawLine(startPoint,endPoint);
    }
    //发送信号 提示绘图事件函数绘图 传参为在内存中绘好的图片
    emit updateText(image);
}
