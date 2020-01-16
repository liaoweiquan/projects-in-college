#ifndef MYMEMORY_H
#define MYMEMORY_H

#include <QDebug>
#include <iostream>
#include <QString>
#include <QChar>
#include <vector>


const int singalBlockLength = 100; //每行的一块节点可容纳的字符数
//块状链表

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

class MyMemory
{

private:
    pNode phead;                                                                            //链表头结点
    pNode ptail;                                                                            //尾结点
    int totalLineNum;                                                                       //总行数
    int totalCharNum;                                                                       //总字符数
    int getStrLen(const char * str);                                                        //获取char*的长度
    bool hasChangeText;                                                                     //文本是否改变的标志
    bool isDigOrNumOrF(QChar ch);                                                           //查询当前字符是否为非中文字符
    pNode getLineNode(int lineNum);                                                         //返回对应行的链表头

public:
    MyMemory();
    ~MyMemory();
    void addNewLineInTail(QString &str);                                                    //行尾添加新一行
    void addNewLineInTail(const char * str);                                                //行尾添加新一行
    void addNewLineInPargh(QString &str, int lineNum);                                      //行中间添加一行  >=lineNum均后移
    void addNewLineInPargh(const char * str, int lineNum);                                  //行中间添加一行  >=lineNum均后移
    void addCharInLineTail(QChar ch, int lineNum);                                          //行尾添加字符
    void addCharInLineTail(char ch, int lineNum);                                           //行尾添加字符
    void addCharInLine(QChar ch, int lineNum, int linePos);                                 //行中添加字符
    void addCharInLine(char ch, int lineNum, int linePos);                                  //行中添加字符
    void addStrInLine(QString & str, int lineNum, int linePos);                             //行中间添加字符串
    void addStrInLine(const char * str, int lineNum, int linePos);                          //行中间添加字符串
    void divideStrInLine(int lineNum, int linePos);                                         //行一分为二
    void deleteCharInTail(int lineNum);                                                     //行尾删除字符
    void deleteCharInLine(int lineNum, int linePos);                                        //行内删除字符
    void deletLine(int lineNum);                                                            //删除行
    void deleteLineMemory(pNode node);                                                      //清除行内存
    void blockDelete(int sLineNum, int sLinePos, int eLineNum, int eLinePos);               //块删除
    QString blockCopy(int sLineNum, int sLinePos, int eLineNum, int eLinePos);              //块复制
    void qDebugAllLine();                                                                   //输出调试信息
    void qdDebugList();                                                                     //输出调试信息
    QChar getLineChar(int lineNum, int linePos);                                            //获取指定位置字符
    int helpCalCurX(int lineNum);                                                           //计算坐标
    int getTotalLineNum();                                                                  //获取总行数
    bool getChangeState();                                                                  //获取当前文本状态
    void setChangeState(bool state);                                                        //改变文本状态
    int getLineCharNums(int lineNum);                                                       //返回当前行的字符数
    int getTotalCharNums(){
        return totalCharNum;
    }
    //5.27 重构
    //加入字符长度的计算
    int caluBefLength(int lineNum, int pos);
    int caluAftLength(int lineNum, int pos);


    //迭代器
    class iterator{
    private:
        pNode m_ptr;                                                                        //操作对象为指针

    public:
        iterator(pNode p = nullptr) : m_ptr(p) {}
        QString operator*() const{                                                          //取值 取出该行
            QString str;
            pBlock  bptr = m_ptr->_pstr;
            while(bptr){
                for(int i = 0; i < bptr->_size; ++i)
                    str += bptr->_str[i];
                bptr = bptr->nextBlock;
            }

            return str;
        }
        pNode operator->() const{                                                           //获取该行指针
            return m_ptr;
        }
        iterator& operator++(){
            m_ptr = m_ptr->nextNode;
            return *this;
        }
        iterator operator++(int){                                                           //指向下一行
            pNode temp = m_ptr;
            m_ptr = m_ptr->nextNode;
            return iterator(temp);
        }
        bool operator==(const iterator &arg) const{                                         //比较是否与该行相等
            return arg.m_ptr == this->m_ptr;
        }
        bool operator!=(const iterator &arg) const{                                         //是否不等
            return arg.m_ptr != this->m_ptr;
        }

    };

    iterator begin() const{                                                                 //返回迭代器的首部
        return iterator(phead->nextNode);
    }
    iterator end() const{                                                                   //返回迭代器的末尾
        return iterator(ptail->nextNode);
    }
};

#endif // MYMEMORY_H
