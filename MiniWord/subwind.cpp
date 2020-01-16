#include "subwind.h"
#include "mainwindow.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

subWind::subWind(QWidget *parent) : QWidget(parent)
{
    //默认从头开始搜索
    this->setWindowTitle("搜索框");
    this->resize(300,150);
    //b.setParent(this);
    b = new QPushButton(this);
    b->setText("search");
    b->resize(50,25);
    b->move(220,10);


    b_1 = new QPushButton(this);
    b_1->setText("replace");
    b_1->resize(50,28);
    b_1->move(220,60);

    edit = new QTextEdit(this);
    edit->resize(200,50);
    edit->move(0,0);

    replace_text = new QTextEdit(this);
    replace_text->resize(200,50);
    edit->move(0,60);

    connect(b, &QPushButton::clicked,
            [=](){
        editText.clear();
        editText = edit->toPlainText();
        qDebug() << editText;
        std::vector<int> next(editText.size() + 1, 0);
        if(kmp(editText)){
            qDebug() << "找到";
            //渲染 选中 可复制

        }
        else
            qDebug() << "未找到";
    }
            );
    connect(b_1,&QPushButton::clicked,[=](){
        editText.clear();
        editText = edit->toPlainText();

        replText.clear();
        replText = replace_text->toPlainText();

        qDebug() << editText;
        qDebug() << replText;
        std::vector<int> next(editText.size() + 1, 0);
        if(kmp(replText)){
            qDebug() << "找到";
            //渲染 选中 可复制
            memory->blockDelete(BlockPos->startLineNum,BlockPos->startLinePos,BlockPos->endLineNum,BlockPos->endLinePos);
            memory->addStrInLine(editText,BlockPos->startLineNum,BlockPos->startLinePos);

        }
        else
            qDebug() << "未找到";
    });
}

void subWind::get_next(QString b, std::vector<int> &next){
    int i = 0, j = -1;
        next[0] = -1;
        int m = b.size();
        while(i < m){
            if(j == -1 || b[i] == b[j]){
                ++ i;
                ++ j;
                next[i] = j;
            }
            else
                j = next[j];
        }
}
bool subWind::kmp(QString b){

    //BlockPos
    int i = 0, j = 0;
    std::vector<int> next(b.size() + 1, 0);
    get_next(b, next);
        int n = memory->getTotalCharNums(), m = b.size();
        int lineN = 1, lineP = 0;
        int stL = 1, stP = 0;
        MyMemory::iterator it = memory->begin();
        while(i < n && it != memory->end()){
            if(j == -1 || (*it)[lineP] == b[j]){
                if(lineP >= (*it).size() - 1){
                    ++ it;
                    ++ lineN;
                    lineP = 0;
                }
                else{

                    ++ lineP;
                }
                ++ j;
                ++ i;
            }
            else{
                //不匹配 记录新开始位置
                j = next[j];

                if(lineP >= (*it).size() - 1){
                    stP = 0;
                    stL = lineN + 1;
                }
                else{
                    stP = lineP + 1;
                    stL = lineN;
                }
            }

            if(j >= m - 1){
                BlockPos->startLineNum = stL;
                BlockPos->startLinePos = stP;
                BlockPos->endLineNum = lineN;
                BlockPos->endLinePos = lineP + 1;
                AllowBlock = true;
                qDebug() << "startLine:" << stL;
                qDebug() << "startPos:" << stP;
                qDebug() << "endLine:" << lineN;
                qDebug() << "endPos:" << lineP;
                return true;
            }

        }
        return false;
}
