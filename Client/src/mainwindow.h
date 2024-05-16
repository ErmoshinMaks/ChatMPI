#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QTimer>
#include <string>
#include "threadsqueue.hpp"
#include "ClientDTO.h"

namespace Ui {
class MainWindow;
}
 
class MainWindow : public QMainWindow
{
    Q_OBJECT
 
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void get_queues(ThreadSafeQueue<ClientDTO>* q_send, ThreadSafeQueue<ClientDTO>* q_rcv);
    void login(QString);
    
    ~MainWindow();
private:
    void add_mes(QString, QString, bool);

private slots:
    void check_mes();
    void send_mes();
 
private:
    Ui::MainWindow *ui;
    ThreadSafeQueue<ClientDTO>* m_q_send;
    ThreadSafeQueue<ClientDTO>* m_q_rcv;
    QString username;
    QTimer *timer = new QTimer(this);
};
 
#endif // MAINWINDOW_H