#include "shifro.h"

QVector<int> Shifro::init_Tabl(int keyVal)
{
        srand(keyVal);
        QVector<int> tabl;
        tabl.resize(256);
        int x;
        for(int i=0; i<256;i++)
        {
            x =rand()%256;
            if(i==0)
                tabl[i]=x;
            else
            {
                int k=0;
                for(k=0; k<i;k++)
                 {   if( tabl.at(k)==x)
                       { i--;
                        break;
                        }
                    else
                    {
                        continue;
                    }
                 }
                if(i==k)
                tabl[i]=x;
            }
        }
        return tabl;
}

QVector<int> Shifro::key_transform()
{
    QVector<int> keyMat;
    for(int i=0; i<key.length();i++)
    {
        keyMat.push_back(key[i].cell());
    }
    return keyMat;
}


Shifro::Shifro(QString Key):key(Key)
{
    QVector<int> m = key_transform();
    for(int i =0; i< m.size(); i++)
        tabl.push_back(init_Tabl(m[i]));
}

QString Shifro::message_ToCode(QString message)
{
     QString code;
     for(int i=0;i<message.size();i++)
     {

         unsigned char s = message[i].cell();
         for(int m=0;m<tabl.size();m++)
             s = symbol_ToCode(s,tabl[m]);
         s = s+7;
         for(int m = tabl.size()-1; m>=0;m--)
             s = code_ToSymbol(s,tabl[m]);
         code[i] = s;
     }
     return code;
}

QString Shifro::code_ToMessage(QString cipherText)
{
    QString message;
    for(int i=0;i<cipherText.size();i++)
    {
        unsigned char s = cipherText[i].cell();
        for(int m=0;m<tabl.size();m++)
            s = symbol_ToCode(s,tabl[m]);
        s = s-7;
        for(int m = tabl.size()-1; m>=0;m--)
            s = code_ToSymbol(s,tabl[m]);
        message[i]=s;
    }
    return message;
}

QString Shifro::messToCodeTwo(QString message)
{
    QString code;
    QChar *bMas = new QChar[message.size()];
    bMas=message.data();
   // char * str = static_cast<char>(bMas);
  //  char *cSymMas = new char[message.size()];
    for(int i=0;i<message.size();i++)
    {
       char s = static_cast<char>(bMas[i].cell());//message[i].cell();
        qDebug() << s;


       //cSymMas[i] = static_cast<char>(s);
    }
    return code;
}

int Shifro::symbol_ToCode(int symbol, QVector<int>tabl)
{
    return tabl[symbol];
}
int Shifro::code_ToSymbol(int code, QVector<int> tabl)
{
    for(int i=0; i<256;i++)
    if (tabl[i] == code)
        return i;
    else
        continue ;
    return -1;
}

