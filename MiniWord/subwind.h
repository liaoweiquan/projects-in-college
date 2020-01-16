#ifndef SUBWIND_H
#define SUBWIND_H

#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <vector>
#include <QString>

class subWind : public QWidget
{
    Q_OBJECT
public:
    explicit subWind(QWidget *parent = nullptr);
    void get_next(QString b, std::vector<int> & next);
    bool kmp(QString b);
private:
    QPushButton*  b;
    QPushButton*  b_1;
    QTextEdit* edit;
    QTextEdit* replace_text;

signals:

public slots:
};

#endif // SUBWIND_H
