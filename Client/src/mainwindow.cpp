#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "ClientDTO.h" 

#include <QtGui>
#include <QInputDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
 
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(timer, SIGNAL(timeout()), this, SLOT(check_mes()));
    timer->setInterval(300);
    timer->start();
    
    ui->setupUi(this);
    

    // QPushButton *button1 = new QPushButton("One");
    // QPushButton *button2 = new QPushButton("Two");
    // QPushButton *button3 = new QPushButton("Three");
    // QPushButton *button4 = new QPushButton("Four");
    // QPushButton *button5 = new QPushButton("Five");


    // ui->output_3->addWidget(button1);
    // ui->output_3->addWidget(button2);
    // ui->output_3->addWidget(button3);
    // ui->output_3->addWidget(button4);
    // ui->output_3->addWidget(button5);

    
    // Инициализируем второе окно
    // sWindow = new AnotherWindow();
    // // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(ui->send_button, SIGNAL(released()), this, SLOT(send_mes()));
 
    // // Инициализируем третье окно
    // thirdWindow = new AnotherWindow();
    // // подключаем к слоту запуска главного окна по кнопке в третьем окне
    // connect(thirdWindow, &AnotherWindow::firstWindow, this, &MainWindow::show);
}
 
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::get_queues(ThreadSafeQueue<ClientDTO>* q_send, ThreadSafeQueue<ClientDTO>* q_rcv)
{
    m_q_send = q_send;
    m_q_rcv  = q_rcv;
}

void MainWindow::login(QString name)
{
    username = name;
}

void MainWindow::check_mes()
{
    ClientDTO data;
    if (m_q_rcv->empty() || !m_q_rcv->try_pop(data))
        return;
    switch(data.mes.type){
        case mes_t::POST:
            if(QString(data.from) != username)
                add_mes(QString(data.mes.data), QString(data.from), 0);
            // ui->mesLabel->setText(ui->mesLabel->text() + data.message + QString("/n"));
            break;
        case mes_t::GETU:
            QString line(data.mes.data);
            QStringList list = line.split(';').filter(QString(""));
            list.removeLast();
            list.removeOne(username);
            ui->comboBoxClients->clear();
            ui->comboBoxClients->addItems(list);
            break;
    }
}

void MainWindow::send_mes()
{   
    QString mes = ui->input->toPlainText();
    ui->input->clear();
    if(mes.size() == 0)
        return;
    if(ui->comboBoxClients->count() == 0)
        return;
    
    QString to = ui->comboBoxClients->currentText();
    add_mes(mes, username, 1);

    ClientDTO data;
    data.mes.type = mes_t::POST;
    memcpy(data.to, to.toStdString().c_str(), MESSAGE_SIZE);
    memcpy(data.from, username.toStdString().c_str(), MESSAGE_SIZE);
    memcpy(data.mes.data, mes.toStdString().c_str(), MESSAGE_SIZE);
    m_q_send->push(data);
}

void MainWindow::add_mes(QString mes, QString name, bool t = false)
{
    QLabel* label = new QLabel;
    // QPushButton *button5 = new QPushButton(mes);
    // label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setText(mes);
    if(!t)
        label->setAlignment(Qt::AlignRight);
    else
        label->setAlignment(Qt::AlignLeft);
    ui->mes_layout->addWidget(label);
}
