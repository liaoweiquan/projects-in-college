#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>
extern QString ThreatStr;
class MyThread : public QObject
{
    Q_OBJECT

public:
    explicit MyThread(QObject *parent = nullptr);
    //线程处理函数
    void drawText();
signals:
    //信号 发送给主函数
    void updateText(QImage);

private:
    //判断是否为非中文字符
    bool isDigOrNOrF(QChar c);

public slots:

};

#endif // MYTHREAD_H
