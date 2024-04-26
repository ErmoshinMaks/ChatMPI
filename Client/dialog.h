#ifndef DIALOG_H
#define DIALOG_H


class Dialog : public QDialog
{

private:
    QTcpSocket *_sok; //сокет
    quint16 _blockSize;//текущий размер блока данных
    QString _name;//имя клиента
};

#endif // DIALOG_H
