#ifndef SHIFRO_H
#define SHIFRO_H
#include<QString>
#include<QVector>
#include<string.h>
#include <uchar.h>
#include <qdebug.h>
class Shifro
{
    QString key; //235abc.
    QVector<QVector<int>> tabl;
    int *cryptoTabl;
    int symbol_ToCode(int symbol, QVector<int> tabl);
    int code_ToSymbol (int code, QVector<int> tabl);
    QVector<int> init_Tabl(int keyVal);
    QVector<int> key_transform();
public:
    Shifro(QString Key);
    QString message_ToCode(QString message);
    QString code_ToMessage(QString cipherText);
    QString messToCodeTwo(QString message);
};

#endif // SHIFRO_H
