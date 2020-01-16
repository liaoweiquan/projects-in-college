#include "mymemory.h"
#include "mainwindow.h"
#include <QDebug>
#include <String>
#include <QChar>

//块状链表
/*
typedef struct LineBlock{
    int _size;                                                                              //每一块实际存的长度
    struct LineBlock * nextBlock;                                                           //指向下一块的指针
    QChar * _str;                                                                           //块内的堆
    LineBlock(): _size(0), nextBlock(nullptr), _str(new QChar[singalBlockLength]){}         //结点的构造函数
}Block,*pBlock;

typedef struct ListNode{
    struct ListNode * nextNode;                                                             //指向下一行
    struct LineBlock * _pstr;                                                               //指向第一块
    int _lineNum;                                                                           //行序号
    int _charSize;                                                                          //每行实际存放字符数
    ListNode(): nextNode(nullptr), _pstr(nullptr), _lineNum(0),_charSize(0){}               //行结点构造函数
}Node,*pNode;
*/

MyMemory::MyMemory()                                                                        //构造函数
{                                                                                           //new行以及块
    phead = new Node();
    ptail = phead;
    ptail->_pstr = new Block();
    totalLineNum = 0;
    totalCharNum = 0;}

MyMemory::~MyMemory(){                                                                      //析构函数 释放空间

    pNode ptr = phead->nextNode;
    pNode next = nullptr;
    while(ptr){
        next = ptr->nextNode;
        pBlock lptr = ptr->_pstr;
        pBlock lnext = nullptr;
        while(lptr){
            lnext = lptr->nextBlock;
            delete lptr;
            lptr = lnext;

        }
        delete ptr;

        ptr = next;
    }

    delete phead;
}

int MyMemory::getStrLen(const char *str){
    //获取char*str的长度
    int strlength = 0;
    while(str[strlength++]);
    return -- strlength;
}

void MyMemory::qDebugAllLine(){
    //输出调试信息
    pNode ptr = phead->nextNode;
    while(ptr){
        QString str;
        pBlock bptr = ptr->_pstr;
        while(bptr){
            for(int i = 0; i < bptr->_size; ++i)
                str += bptr->_str[i];
            bptr = bptr->nextBlock;
        }
        qDebug()<<"LineNum:" << ptr->_lineNum << "LineCharNums:" << ptr->_charSize << str;
        ptr = ptr->nextNode;
    }
}

void MyMemory::qdDebugList(){
    //输出调试信息
    pNode ptr = phead->nextNode;
    while(ptr){
        pBlock bptr = ptr->_pstr;
        QString str;
        while(bptr){
            for(int i = 0; i < bptr->_size; ++i){
                str += bptr->_str[i];

            }
            if(bptr->nextBlock)
                str += "->";
            bptr = bptr->nextBlock;
        }
        qDebug()<<"LineNum:" << ptr->_lineNum << str;

        ptr = ptr->nextNode;
    }
}

void MyMemory::addNewLineInTail(QString &str){
    //获取字符串长度
    int len = str.size();
    ptail->nextNode = new Node();
    ptail = ptail->nextNode;
    ptail->_pstr = new Block();

    ptail->_lineNum = ++totalLineNum;
    pBlock ptr = ptail->_pstr;
    for(int i = 0; i < len; ++i){
        //依次将字符加入
        if(ptr->_size >= singalBlockLength){
            //超出该块大小 再申请一块
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = str[i];
    }
    //文本已改变
    hasChangeText = true;
    //维护长度
    ptail->_charSize = len;
    totalCharNum += str.size();
}

void MyMemory::addNewLineInTail(const char *str){
    int len = getStrLen(str);
    ptail->nextNode = new Node();
    ptail = ptail->nextNode;
    ptail->_pstr = new Block();

    ptail->_lineNum = ++totalLineNum;
    pBlock ptr = ptail->_pstr;
    for(int i = 0; i < len; ++i){
        if(ptr->_size >= singalBlockLength){
            //超出该块大小 再申请一块
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = str[i];
    }
    hasChangeText = true;
    ptail->_charSize = len;
    totalCharNum += len;
}

void MyMemory::addNewLineInPargh(QString &str, int lineNum){
    int len = str.size();
    //新建新的行 赋予字符串 再插入到lineNum处
    pNode addLine = new Node();
    addLine->_pstr = new Block();
    addLine->_lineNum = lineNum;
    pBlock ptr = addLine->_pstr;
    for(int i = 0; i < len; ++i){
        if(ptr->_size >= singalBlockLength){
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = str[i];
    }
    addLine->_charSize = len;
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum - 1)
        cur = cur->nextNode;
    //移动到该行
    pNode addNext = cur->nextNode;
    cur->nextNode = addLine;
    addLine->nextNode = addNext;
    while(addNext){
        addNext->_lineNum += 1;
        addNext = addNext->nextNode;
    }
    ++totalLineNum;
    while(ptail->nextNode)
        ptail = ptail->nextNode;
    hasChangeText = true;
    totalCharNum += len;
}

void MyMemory::addNewLineInPargh(const char *str, int lineNum){
    //重载 与上一函数思路类似
    int len = getStrLen(str);
    pNode addLine = new Node();
    addLine->_pstr = new Block();
    addLine->_lineNum = lineNum;

    pBlock ptr = addLine->_pstr;
    for(int i = 0; i < len; ++i){
        if(ptr->_size >= singalBlockLength){
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = str[i];
    }
    addLine->_charSize = len;
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum - 1)
        cur = cur->nextNode;
    pNode addNext = cur->nextNode;
    cur->nextNode = addLine;
    addLine->nextNode = addNext;
    while(addNext){
        addNext->_lineNum += 1;
        addNext = addNext->nextNode;
    }
    ++totalLineNum;
    while(ptail->nextNode)
        ptail = ptail->nextNode;
    hasChangeText = true;
    totalCharNum += len;
}

void MyMemory::addCharInLineTail(QChar ch, int lineNum){
    //在一行的末尾加入一个字符

    //移动到该行
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    pBlock bptr = cur->_pstr;
    cur->_charSize += 1;
    while(bptr->nextBlock)
        bptr = bptr->nextBlock;
    //判断该块是否已满
    if(bptr->_size >= singalBlockLength){
        bptr->nextBlock = new Block();
        bptr = bptr->nextBlock;
    }
    bptr->_str[bptr->_size++] = ch;
    hasChangeText = true;
    totalCharNum += 1;
}

void MyMemory::addCharInLineTail(char ch, int lineNum){
    //重载函数 思路与上一函数类似
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    pBlock bptr = cur->_pstr;
    cur->_charSize += 1;
    while(bptr->nextBlock)
        bptr = bptr->nextBlock;
    if(bptr->_size >= singalBlockLength){
        bptr->nextBlock = new Block();
        bptr = bptr->nextBlock;
    }
    bptr->_str[bptr->_size++] = ch;
    hasChangeText = true;
    totalCharNum += 1;
}

void MyMemory::addCharInLine(QChar ch, int lineNum, int linePos){
    //在指定行 指定序号加入字符
    //先移动到该行
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    cur->_charSize += 1;
    int i = 0,j = 0;
    pBlock bptr = cur->_pstr;
    //移动到该序号
    while(i < linePos){

        if(j + 1 > bptr->_size){
            j = 0;
            bptr = bptr->nextBlock;
        }
        ++i;
        ++j;
    }
    if(bptr->_size >= singalBlockLength){
        pBlock dptr = new Block();
        dptr->_str[dptr->_size++] = ch;

        for(i = j; i < bptr->_size; ++i)
            dptr->_str[dptr->_size++] = bptr->_str[j];
        dptr->nextBlock = bptr->nextBlock;
        bptr->nextBlock = dptr;
        bptr->_size = j;
    }
    else{
        for(i = bptr->_size ++; i > j; --i)
            bptr[i] = bptr[i - 1];
        //++bptr->_size;
        bptr->_str[j] = ch;

    }
    hasChangeText = true;
    totalCharNum += 1;
}

void MyMemory::addCharInLine(char ch, int lineNum, int linePos){
    //重载函数
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    cur->_charSize += 1;
    int i = 0,j = 0;
    pBlock bptr = cur->_pstr;
    while(i < linePos){

        if(j + 1 > bptr->_size){
            j = 0;
            bptr = bptr->nextBlock;
        }
        ++i;
        ++j;
    }
    if(bptr->_size >= singalBlockLength){
        pBlock dptr = new Block();
        dptr->_str[dptr->_size++] = ch;

        for(i = j; i < bptr->_size; ++i)
            dptr->_str[dptr->_size++] = bptr->_str[j];

        dptr->nextBlock = bptr->nextBlock;
        bptr->nextBlock = dptr;
        bptr->_size = j;
    }
    else{
        //++bptr->_size;
        for(i = bptr->_size ++; i > j; --i)
            bptr->_str[i] = bptr->_str[i - 1];

        bptr->_str[j] = ch;
    }
    hasChangeText = true;
    totalCharNum += 1;
}

pNode MyMemory::getLineNode(int lineNum){
    //移动指针到该行
    if(lineNum > totalLineNum)
        return nullptr;
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    return cur;
}

void MyMemory::deleteCharInTail(int lineNum){
    //删除行的末尾字符
    pNode cur = phead->nextNode;
    //移动到该行
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    //判断是否已无字符
    if(cur->_charSize <= 0) return;
    pBlock bptr = cur->_pstr, lastptr = cur->_pstr;
    while(bptr->nextBlock){
        lastptr = bptr;
        bptr = bptr->nextBlock;
    }
    //判断该块是否可以直接丢弃
    if(bptr->_size - 1 <= 0 && cur->_charSize > 1){
        lastptr->nextBlock = nullptr;
        delete bptr;
    }
    else
        --bptr->_size;
    hasChangeText = true;
    cur->_charSize -= 1;
    totalCharNum -= 1;
}

void MyMemory::deleteCharInLine(int lineNum, int linePos){
    //删除指定行指定序号的字符
    pNode cur = phead->nextNode;
    //移动到该行
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    if(cur->_charSize <= 0) return;
    int j = 0;
    pBlock bptr = cur->_pstr, lastb = cur->_pstr;

    //移动到指定序号
    while(linePos){
        if(!bptr) return;
        if(bptr && linePos + 1 > bptr->_size){
            linePos -= bptr->_size;
            lastb = bptr;
            bptr = bptr->nextBlock;
        }
        else{
            j = linePos;
            linePos = 0;
        }
    }
    if(bptr->_size <= 1){
        lastb->nextBlock = bptr->nextBlock;
        if(cur->_pstr == bptr){//debug
            cur->_pstr = bptr->nextBlock;
        }
        delete bptr;
        cur->_charSize -= 1;
        return;
    }
    for(int i = j; i < bptr->_size - 1; ++i)
        bptr->_str[i] = bptr->_str[i + 1];
    -- bptr->_size;
    hasChangeText = true;
    cur->_charSize -= 1;
    totalCharNum -= 1;
}

void MyMemory::deletLine(int lineNum){
    //删除该行
    //注意 第一行不可以直接删掉
    if(lineNum > totalLineNum || lineNum <= 1) return;

    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum - 1)
        cur = cur->nextNode;
    pNode deLine = cur->nextNode;
    cur->nextNode = deLine->nextNode;

    if(deLine->_charSize <= 0){
        delete deLine;
        cur = cur->nextNode;

        while(cur){
            cur->_lineNum -= 1;
            cur = cur->nextNode;
        }
        ptail = phead->nextNode;
        while(ptail->nextNode)
            ptail = ptail->nextNode;
        -- totalLineNum;
        return;
    }
    cur->_charSize += deLine->_charSize;
    if(deLine->_pstr){
        pBlock bptr = cur->_pstr;
        while(bptr->nextBlock)
            bptr = bptr->nextBlock;
        bptr->nextBlock = deLine->_pstr;
    }

    delete deLine;
    cur = cur->nextNode;
    while(cur){
        cur->_lineNum -= 1;
        cur = cur->nextNode;
    }
    ptail = phead->nextNode;
    while(ptail->nextNode)
        ptail = ptail->nextNode;
    -- totalLineNum;
    hasChangeText = true;
}

QChar MyMemory::getLineChar(int lineNum, int linePos){
    //获取指定行 指定序号的字符
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    int j = 0;
    pBlock bptr = cur->_pstr;

    while(linePos){
        if(!bptr) return ' ';
        if(bptr && linePos + 1 > bptr->_size){
            linePos -= bptr->_size;
            //lastb = bptr;
            bptr = bptr->nextBlock;
        }
        else{
            j = linePos;
            linePos = 0;
        }
    }
    return bptr->_str[j];
}

void MyMemory::divideStrInLine(int lineNum, int linePos){
    //分裂行
    if(lineNum < 1 || lineNum > totalLineNum)
        return;
    //首先定位该行
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum <lineNum)
        cur = cur->nextNode;
    int totalChar = cur->_charSize;
    cur->_charSize = linePos;

    pNode newLine = new Node();
    newLine->_lineNum = cur->_lineNum + 1;
    newLine->_charSize = totalChar - cur->_charSize;
    int j = 0;
    pBlock bptr = cur->_pstr;
    //定位到指定序号
    while(linePos){
        if(!bptr) return;
        if(bptr && linePos + 1 > bptr->_size){
            linePos -= bptr->_size;
            //lastb = bptr;
            bptr = bptr->nextBlock;
        }
        else{
            j = linePos;
            linePos = 0;
        }
    }
    //将序号所在内容的剩余内容放入新块
    pBlock ftBlock = new Block();
    for(int i = j; i < bptr->_size; ++i)
        ftBlock->_str[ftBlock->_size++] = bptr->_str[i];
    newLine->_pstr = ftBlock;
    ftBlock->nextBlock = bptr->nextBlock;
    bptr->nextBlock = nullptr;
    bptr->_size = j;
    //delete bptr;
    newLine->nextNode = cur->nextNode;
    cur->nextNode = newLine;
    cur = newLine->nextNode;
    while(cur){
        cur->_lineNum += 1;
        cur = cur->nextNode;
    }
    totalLineNum += 1;
    //维护尾指针
    if(ptail->nextNode){
        while(ptail->nextNode)
            ptail = ptail->nextNode;
    }
    hasChangeText = true;
}

void MyMemory::addStrInLine(QString &str, int lineNum, int linePos){
    //在指定行指定序号添加字符串
    pBlock head = new Block();
    pBlock ptr = head;
    for(QChar ch: str){
        if(ptr->_size >= singalBlockLength){
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = ch;
    }

    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    int i = 0,j = 0;
    pBlock bptr = cur->_pstr;
    while(i < linePos){

        if(j + 1 > bptr->_size){
            j = 0;
            bptr = bptr->nextBlock;
        }
        ++i;
        ++j;
    }
    //bptr所在块为linepos所在 j为linepos在该块的索引
    if(bptr->_size >= singalBlockLength || j >= bptr->_size){
        //直接加新块 n块
        ptr->nextBlock = bptr->nextBlock;
        bptr->nextBlock = head;
    }
    else{
        //分裂这一块
        pBlock dBlock = new Block();
        for(int i = j; i < bptr->_size; ++i)
            dBlock->_str[dBlock->_size++] = bptr->_str[i];
        bptr->_size = j;

        ptr->nextBlock = dBlock;
        dBlock->nextBlock = bptr->nextBlock;
        bptr->nextBlock = head;
    }
    cur->_charSize += str.size();
    totalCharNum += str.size();
}

void MyMemory::addStrInLine(const char *str, int lineNum, int linePos){
    //重载函数
    int i = 0,j = 0;
    int len = getStrLen(str);
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;

    pBlock bptr = cur->_pstr;
    while(i < linePos){

        if(j + 1 > bptr->_size){
            j = 0;
            bptr = bptr->nextBlock;
        }
        ++i;
        ++j;
    }

    pBlock head = new Block();
    pBlock ptr = head;
    for(i = 0; i < len; ++i){
        char ch = str[i];
        if(ptr->_size < singalBlockLength){
            ptr->nextBlock = new Block();
            ptr = ptr->nextBlock;
        }
        ptr->_str[ptr->_size++] = ch;
    }
    //bptr所在块为linepos所在 j为linepos在该块的索引
    if(bptr->_size >= singalBlockLength || j >= bptr->_size){
        //直接加新块 n块
        ptr->nextBlock = bptr->nextBlock;
        bptr->nextBlock = head;
    }
    else{
        //分裂这一块
        pBlock dBlock = new Block();
        for(int i = j; i < bptr->_size; ++i)
            dBlock->_str[dBlock->_size++] = bptr->_str[i];
        bptr->_size = j;

        ptr->nextBlock = dBlock;
        dBlock->nextBlock = bptr->nextBlock;
        bptr->nextBlock = head;
    }
    cur->_charSize += len;
    totalCharNum += len;
}

void MyMemory::blockDelete(int sLineNum, int sLinePos, int eLineNum, int eLinePos){
    //块操作之删除
    //定位操作首行
    pNode scur = phead->nextNode;
    while(scur && scur->_lineNum < sLineNum)
        scur = scur->nextNode;
    //定位操作尾行
    pNode ecur = scur;
    while(ecur && ecur->_lineNum < eLineNum)
        ecur = ecur->nextNode;

    if(eLineNum == sLineNum){
        if(sLinePos <= 0 && eLinePos >= scur->_charSize){
            //一整行删除
            qDebug() << "一整行删除";
            scur->_charSize = 0;
            pBlock deBlock = scur->_pstr, decur = scur->_pstr;

            scur->_pstr = new Block();

            while(deBlock){
                decur = deBlock->nextBlock;
                delete deBlock;
                deBlock = decur;
            }
        }
        else if(eLinePos > scur->_charSize){
            //删除一行的后半段
            qDebug() << "删除一行的后半段";
            int j = 0, i = 0;
            //scur->_charSize -= eLinePos - sLinePos + 1;
            pBlock bptr = scur->_pstr;
            while(bptr && i < sLinePos){
                if(j + 1 > bptr->_size){
                    j = 0;
                    bptr = bptr->nextBlock;
                }
                ++i;
                ++j;
            }
            //bptr所在块为linepos所在 j为linepos在该块的索引
            pBlock nexptr = bptr->nextBlock, decur = nullptr;
            bptr->nextBlock = nullptr;
            bptr->_size = j;
            while(nexptr){
                decur = nexptr->nextBlock;
                delete nexptr;
                nexptr = decur;
            }
            bptr = scur->_pstr;
            scur->_charSize = 0;
            while(bptr){
                scur->_charSize += bptr->_size;
                bptr = bptr->nextBlock;
            }
        }
        else if(sLinePos <= 0 && eLinePos < scur->_charSize){
            qDebug() << "sLinePos <= 0";
            int j = 0, i = 0;
            pBlock bptr = scur->_pstr;
            while(i < eLinePos && bptr){
                if(j + 1 > bptr->_size){
                    j = 0;
                    bptr = bptr->nextBlock;
                }
                ++i;
                ++j;
            }
            //bptr所在块为linepos所在 j为linepos在该块的索引
            pBlock newHead = new Block();
            while(j < bptr->_size)
                newHead->_str[newHead->_size ++] = bptr->_str[j++];
            newHead->nextBlock = bptr->nextBlock;
            scur->_pstr = newHead;
            delete bptr;
            scur->_charSize = 0;
            bptr = scur->_pstr;
            while(bptr){
                scur->_charSize += bptr->_size;
                bptr = bptr->nextBlock;
            }
        }
        else{
            //qDebug() << "Same Line Block delete start";
            //删除中间部分
            qDebug() << "删除中间部分";
            int j = 0, i = 0;
            pBlock bptr = scur->_pstr;
            while(i < sLinePos && bptr){
                if(j + 1 > bptr->_size){
                    j = 0;
                    bptr = bptr->nextBlock;
                }
                ++i;
                ++j;
            }
            //bptr所在块为linepos所在 j为linepos在该块的索引
            //从删除部分的开始pos处截断
            int cnt = eLinePos - sLinePos + 1;
            qDebug() << "删除了" << cnt;
            //scur->_charSize -= cnt;
            int lasPos = j;
            pBlock dhead = new Block();//将删除部分处在的块的后半部分存入dhead中
            while(j < bptr->_size){
                dhead->_str[dhead->_size++] = bptr->_str[j++];
            }
            dhead->nextBlock = bptr->nextBlock;
            bptr->nextBlock = dhead;
            bptr->_size = lasPos;

            //下面执行删除操作
            j = 0;
            pBlock bcur = dhead;
            while(-- cnt){
                if(j >= bcur->_size){
                    j = 0;
                    bcur = bcur->nextBlock;
                }
                else
                    ++ j;
            }
            pBlock newHead = new Block();
            while(j < bcur->_size){
                //qDebug() << bcur->_str[j];
                newHead->_str[newHead->_size++] = bcur->_str[j++];
            }
            newHead->nextBlock = bcur->nextBlock;
            if(sLineNum > 0)
                bptr->nextBlock = newHead;
            else scur->_pstr = newHead;

            scur->_charSize = 0;
            bptr = scur->_pstr;
            while(bptr){
                scur->_charSize += bptr->_size;
                bptr = bptr->nextBlock;
            }
        }
    }
    else{
        //跨行删除
        if(BlockPos->startLineNum <= 1 && BlockPos->endLineNum >= memory->getTotalLineNum()){
            //int startLen = memory->getLineCharNums(BlockPos->startLineNum);
            int endLen = memory->getLineCharNums(BlockPos->endLineNum);
            if(BlockPos->startLinePos <= 0 && BlockPos->endLinePos + 1 >= endLen){
                //删除全文
                pNode cur = phead->nextNode;
                pNode next = cur;
                while(cur){
                    next = cur->nextNode;
                    delete cur;
                    cur = next;
                }
                phead->nextNode = new Node();
                ptail = phead->nextNode;
                ptail->_lineNum = 1;
                ptail->_pstr = new Block();
                totalLineNum = 1;

            }
            else if(BlockPos->startLinePos <= 0 && BlockPos->endLinePos + 1 < endLen){
                //保留文末小尾巴
                QString strtail;
                pBlock bptr = ptail->_pstr;
                int i = 0, j = 0;
                while(i < eLinePos && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                while(i < ptail->_charSize && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    strtail += bptr->_str[j];
                    ++i;
                    ++j;
                }
                //qDebug() << strtail;
                pNode cur = phead->nextNode;
                pNode next = cur;
                while(cur){
                    next = cur->nextNode;
                    delete cur;
                    cur = next;
                }
                phead->nextNode = nullptr;
                ptail = phead;
                totalLineNum = 0;
                //ptail->_lineNum = 1;
                addNewLineInTail(strtail);


            }
            else if(BlockPos->startLinePos > 0 && BlockPos->endLinePos + 1 >= endLen){
                //保留开头一点点
                QString strhead;
                pBlock bptr = phead->nextNode->_pstr;
                int i = 0, j = 0;
                while(i < sLinePos && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    strhead += bptr->_str[j];
                    ++i;
                    ++j;
                }
                //bptr所在块为linepos所在 j为linepos在该块的索引
                //qDebug() << strhead;
                pNode cur = phead->nextNode;
                pNode next = cur;
                while(cur){
                    next = cur->nextNode;
                    delete cur;
                    cur = next;
                }
                phead->nextNode = nullptr;
                ptail = phead;
                totalLineNum = 0;
                //ptail->_lineNum = 1;
                addNewLineInTail(strhead);

            }
            else{
                //头尾都留一点
                QString strhead;
                pBlock bptr = phead->nextNode->_pstr;
                int i = 0, j = 0;
                while(i < sLinePos && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    strhead += bptr->_str[j];
                    ++i;
                    ++j;
                }

                QString strtail;
                bptr = ptail->_pstr;
                //int i = 0, j = 0;
                while(i < eLinePos && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                while(i < ptail->_charSize && bptr){
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    strtail += bptr->_str[j];
                    ++i;
                    ++j;
                }
                //qDebug() << strhead + strtail;
                pNode cur = phead->nextNode;
                pNode next = cur;
                while(cur){
                    next = cur->nextNode;
                    delete cur;
                    cur = next;
                }
                phead->nextNode = nullptr;
                ptail = phead;
                totalLineNum = 0;
                //ptail->_lineNum = 1;
                strhead += strtail;
                addNewLineInTail(strhead);

            }
        }
        else if(BlockPos->startLineNum <= 1 && BlockPos->endLineNum < totalLineNum){
            //保留后k + 1行
            if(eLinePos + 1 >= getLineCharNums(eLineNum)){
                //k行全删
                pNode ncur = phead->nextNode;
                pNode next = nullptr;
                //ecur 为第k行 跳到k + 1行
                next = ecur->nextNode;
                ecur->nextNode = nullptr;
                ecur = next;
                phead->nextNode = ecur;
                totalLineNum = 0;
                while(ecur){
                    ecur->_lineNum = ++ totalLineNum;
                    ecur = ecur->nextNode;
                }
                ecur = phead->nextNode;
                while(ecur->nextNode)
                    ecur = ecur->nextNode;
                ptail = ecur;

                while(ncur){
                    next = ncur->nextNode;
                    delete ncur;
                    ncur = next;
                }
            }
            else{
                //k行保留一些
                //ecur k line
                //删除k行前半部分
                int i = 0,j = 0;
                pBlock bptr = ecur->_pstr;
                while(i < eLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                //bptr所在块为linepos所在 j为eLinePos在该块的索引
                pBlock nHead = new Block;
                while(j < bptr->_size){
                    nHead->_str[nHead->_size ++] = bptr->_str[j++];
                }
                nHead->nextBlock = bptr->nextBlock;
                bptr = ecur->_pstr;
                ecur->_pstr = nHead;

                totalLineNum = 0;
                pNode next = phead->nextNode;
                phead->nextNode = ecur;

                //维护行字符数
                ecur->_charSize = 0;
                bptr = ecur->_pstr;
                while(bptr){
                    ecur->_charSize += bptr->_size;
                    bptr = bptr->nextBlock;
                }

                while(ecur){
                    ecur->_lineNum = ++totalLineNum;
                    ecur = ecur->nextNode;
                }
                pNode bcur = next;
                while(next->nextNode != phead->nextNode)
                    next = next->nextNode;
                next->nextNode = nullptr;
                while(bcur){
                    next = bcur->nextNode;
                    delete bcur;
                    bcur = next;
                }
                ecur = phead->nextNode;
                while(ecur->nextNode)
                    ecur = ecur->nextNode;
                ptail = ecur;


            }
        }
        else if(BlockPos->startLineNum > 1 && BlockPos->endLineNum >= totalLineNum){
            //保留前k行
            qDebug() << "开始执行-保留前k行";
            if(sLinePos <= 0){
                pNode next = phead;
                while(next && next->nextNode != scur)
                    next = next->nextNode;

                ptail = next;
                ptail->nextNode = nullptr;

                //delete memory
                //维护totallinenum
                totalLineNum = BlockPos->startLineNum - 1;
                addNewLineInTail("");
            }
            else if(sLinePos + 1 >= getLineCharNums(sLineNum)){
                ptail = scur;
                scur->nextNode = nullptr;
                totalLineNum = BlockPos->startLineNum;
            }
            else{
                int i = 0,j = 0;
                pBlock bptr = scur->_pstr;

                while(i < sLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                scur->_charSize = sLinePos;
                qDebug() << scur->_charSize;
                //bptr所在块为linepos所在 j为eLinePos在该块的索引
                bptr->_size = j;
                pBlock deptr = bptr->nextBlock;
                bptr->nextBlock = nullptr;
                pBlock nextptr = nullptr;
                while(deptr){
                    nextptr = deptr->nextBlock;
                    delete deptr;
                    deptr = nextptr;
                }
                ptail = scur;
                ptail->nextNode = nullptr;
                //delete memory
                //维护totallinenum
                totalLineNum = BlockPos->startLineNum;
            }
            qDebug() << "执行-保留前k行-完成";
        }
        else{
            //删除中间隔行
            //1-k行 删除 2~k-1 之间
            qDebug() << "2~k-1";
            if(sLinePos <=0 && eLinePos + 1 >= getLineCharNums(eLineNum)){
                //2 k-1 全删 正常
                qDebug() << "2 k-1 全删";
                pNode next = phead->nextNode;
                while(next->nextNode != scur)
                    next = next->nextNode;
                next->nextNode = ecur->nextNode;
                next = phead->nextNode;
                totalLineNum = 0;
                while(next){
                    next->_lineNum = ++ totalLineNum;
                    next = next->nextNode;
                }
            }
            else if(sLinePos <=0 && eLinePos + 1 < getLineCharNums(eLineNum)){
                //k-1 留尾巴 正常
                qDebug() << "k-1 留尾巴";
                pNode next = phead->nextNode;
                while(next->nextNode != scur)
                    next = next->nextNode;
                next->nextNode = ecur;
                next = phead->nextNode;
                totalLineNum = 0;
                while(next){
                    next->_lineNum = ++ totalLineNum;
                    next = next->nextNode;
                }
                int i = 0,j = 0;
                pBlock bptr = ecur->_pstr;

                while(i < eLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                //scur->_charSize = sLinePos;
                pBlock newHead = new Block;
                while(j < bptr->_size)
                    newHead->_str[newHead->_size++] = bptr->_str[j ++];
                newHead->nextBlock = bptr->nextBlock;
                bptr->nextBlock = nullptr;
                //TODO::delete head

                //...
                ecur->_pstr = newHead;
                ecur->_charSize -= eLinePos + 1;
            }
            else if(sLinePos > 0 && eLinePos + 1 >= getLineCharNums(eLineNum)){
                //2 留头
                qDebug() << "2 留头";
                pNode lcur = scur->nextNode, next = nullptr;
                scur->nextNode = ecur->nextNode;
                ecur->nextNode = nullptr;

                while(lcur){
                    next = lcur->nextNode;
                    delete lcur;
                    lcur = next;
                }

                int i = 0,j = 0;
                pBlock bptr = scur->_pstr;
                while(i < sLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                bptr->_size = j;
                bptr->nextBlock = nullptr;
                // TODO:: delete bptr->nextBlock->...->nullptr

                //...
                scur->_charSize = sLinePos;
                totalLineNum = 0;
                scur = phead->nextNode;
                while(scur){
                    scur->_lineNum = ++totalLineNum;
                    scur = scur->nextNode;
                }

            }
            else{
                //头尾皆留
                qDebug() << "头尾皆留";
                pNode lcur = scur->nextNode;

                lcur = ecur;
                scur->nextNode = ecur;
                int i = 0,j = 0;
                pBlock bptr = scur->_pstr;

                while(i < sLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }
                bptr->_size = j;
                bptr->nextBlock = nullptr;
                scur->_charSize = sLinePos;

                bptr = ecur->_pstr;
                i = j = 0;
                while(i < eLinePos){

                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++i;
                    ++j;
                }

                pBlock newHead = new Block;
                while(j < bptr->_size)
                    newHead->_str[newHead->_size++] = bptr->_str[j ++];
                newHead->nextBlock = bptr->nextBlock;
                bptr->nextBlock = nullptr;
                //TODO::delete head

                //...
                ecur->_pstr = newHead;
                ecur->_charSize -= eLinePos + 1;

                scur->nextNode = ecur->nextNode;
                bptr = scur->_pstr;
                while(bptr->nextBlock != nullptr)
                    bptr = bptr->nextBlock;
                bptr->nextBlock = ecur->_pstr;
                scur->_charSize = 0;

                ecur->nextNode = nullptr;
                pNode next = nullptr;
                while(lcur){
                    next = lcur->nextNode;
                    delete lcur;
                    lcur = next;
                }
                bptr = scur->_pstr;
                while(bptr){
                    scur->_charSize += bptr->_size;
                    bptr = bptr->nextBlock;
                }
                scur = phead->nextNode;

                totalLineNum = 0;
                while(scur){
                    scur->_lineNum = ++ totalLineNum;
                    scur = scur->nextNode;
                }
            }
        }
    }
}

//复制比较正常
QString MyMemory::blockCopy(int sLineNum, int sLinePos, int eLineNum, int eLinePos){
    QString str_1, str_2, str;

    pNode scur = phead->nextNode;
    while(scur && scur->_lineNum < sLineNum)
        scur = scur->nextNode;
    pNode ecur = scur;
    while(ecur && ecur->_lineNum < eLineNum)
        ecur = ecur->nextNode;

    if(eLineNum == sLineNum){
        //同一行
        int j = 0, i = 0;
        pBlock bptr = scur->_pstr;
        while(i < sLinePos && bptr){
            if(j + 1 > bptr->_size){
                j = 0;
                bptr = bptr->nextBlock;
            }
            ++i;
            ++j;
        }
        //bptr所在块为linepos所在 j为linepos在该块的索引
        while(i < eLinePos && bptr){
            str += bptr->_str[j];
            if(j + 1 > bptr->_size){
                j = 0;
                bptr = bptr->nextBlock;
            }
            ++i;
            ++j;
        }

        return str;
    }
    else{
        // get str_1 and str_2
        int i = 0, j = 0;
        pBlock bptr = scur->_pstr;
        while(i < sLinePos && bptr){
            if(j + 1 > bptr->_size){
                j = 0;
                bptr = bptr->nextBlock;
            }
            ++i;
            ++j;
        }
        //bptr所在块为linepos所在 j为linepos在该块的索引
        while(i < scur->_charSize && bptr){
            str_1 += bptr->_str[j];
            if(j + 1 > bptr->_size){
                j = 0;
                bptr = bptr->nextBlock;
            }
            ++i;
            ++j;
        }
        i = 0;
        j = 0;
        bptr = ecur->_pstr;
        while(i < eLinePos && bptr){
            str_2 += bptr->_str[j];
            if(j + 1 > bptr->_size){
                j = 0;
                bptr = bptr->nextBlock;
            }
            ++i;
            ++j;
        }
        if(eLineNum - sLineNum <= 1)
            return str_1 + str_2;
        else{
            //Todo::
            pNode ncur = scur->nextNode;
            while(ncur && ncur != ecur){
                bptr = ncur->_pstr;
                i = 0;
                j = 0;
                while(i < ncur->_charSize && bptr){
                    str += bptr->_str[j];
                    if(j + 1 > bptr->_size){
                        j = 0;
                        bptr = bptr->nextBlock;
                    }
                    ++j;
                    ++i;
                }
                ncur = ncur->nextNode;
            }
            return str_1 + str + str_2;
        }
    }
}

void MyMemory::deleteLineMemory(pNode node){
    if(node){
        pBlock bptr = node->_pstr;
        pBlock next = nullptr;
        while(bptr){
            next = bptr->nextBlock;
            delete bptr;
            bptr = next;
        }
        node->_charSize = 0;
    }
}

int MyMemory::getTotalLineNum(){
    return totalLineNum;
}

bool MyMemory::getChangeState(){
    return hasChangeText;
}

void MyMemory::setChangeState(bool state){
    hasChangeText = state;
}

int MyMemory::getLineCharNums(int lineNum){
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    return cur->_charSize;
}

//判断是否中文
bool MyMemory::isDigOrNumOrF(QChar ch){
    if((ch >= 'A' && ch <= 'Z')||(ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            return true;
    return mpc[ch];
}

int MyMemory::helpCalCurX(int lineNum){
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    int curLen = 0;
    int cnt = cur->_charSize;
    int i = 0;
    pBlock bptr = cur->_pstr;
    while(cnt--){
        if(i + 1 >= bptr->_size && bptr->nextBlock){
            i = 0;
            bptr = bptr->nextBlock;
        }
        if(isDigOrNumOrF(bptr->_str[i++]))
            curLen += 12;
        else
            curLen += 22;
    }
    return curLen;
}

int MyMemory::caluAftLength(int lineNum, int pos){
    //计算pos后所有的字符长度

    //定位到该行
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    pBlock bptr = cur->_pstr;
    //往后没有字符了
    if(pos >= cur->_charSize)
        return 0;
    if(pos <= 0)
        return cur->_charSize;
    int i = 0;
    int cnt = cur->_charSize;
    int k = 0;
    int retLen = 0;
    while(-- cnt){
        if(i + 1 >= bptr->_size && bptr->nextBlock){
            i = 0;
            bptr = bptr->nextBlock;
        }
        if(k >= pos){
            if(isDigOrNumOrF(bptr->_str[i]))
                retLen += 12;
            else
                retLen += 22;
        }
        ++ k;
        ++ i;
    }
    return retLen;
}

int MyMemory::caluBefLength(int lineNum, int pos){
    //计算pos前所有的字符长度
    //定位到该行

    //这种情况前面也没有了
    if(pos <= 0)
        return 0;
    pNode cur = phead->nextNode;
    while(cur && cur->_lineNum < lineNum)
        cur = cur->nextNode;
    pBlock bptr = cur->_pstr;
    if(pos >= cur->_charSize - 1)
        return cur->_charSize;
    int i = 0, k = 0, retLen = 0, cnt = cur->_charSize;
    while(cnt--){
        if(i + 1 >= bptr->_size && bptr->nextBlock){
            i = 0;
            bptr = bptr->nextBlock;
        }
        if(k <= pos){
            if(isDigOrNumOrF(bptr->_str[i]))
                retLen += 12;
            else
                retLen += 22;
        }
        ++ k;
        ++ i;
    }
    return retLen;
}
