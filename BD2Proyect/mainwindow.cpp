#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "bika.h"
#include "transacciones.cpp"
#include <QtDebug>
#include <QFile>
#include <QProcess>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    query = arg1;
}

void MainWindow::on_pushButton_clicked()
{
    QFile file("../BD2Proyect/query.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream1(&file);
        stream1 << query <<endl;
    }
    file.close();
    /*QString program = "../BD2Proyecto1/BD2Proyect/a.out";
    QStringList arguments;
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program,(QStringList) arguments);
    myProcess->waitForFinished(-1);
    delete myProcess;*/
    bika();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    T1 = arg1;
}

void MainWindow::on_lineEdit_3_textChanged(const QString &arg1)
{
    T2 = arg1;
}

void MainWindow::on_TransactionsButton_clicked()
{
    QFile file1("../BD2Proyect/T1.txt");
    QFile file2("../BD2Proyect/T2.txt");
    if(file1.open(QIODevice::ReadWrite | QIODevice::Truncate) and file2.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream(&file1);
        QTextStream stream2(&file2);
        stream2 << T2 <<endl;
        stream << T1 <<endl;
    }
    transaccion();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}

void MainWindow::on_reset_clicked()
{
    QFile file("../BD2Proyect/query.txt");
    if(file.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream stream1(&file);
        stream1 << "" <<endl;
    }
    /*QString program = "../BD2Proyecto1/BD2Proyect/a.out";
    QStringList arguments;
    QProcess *myProcess = new QProcess(this);
    myProcess->start(program,(QStringList) arguments);
    myProcess->waitForFinished(-1);
    delete myProcess;*/
    bika();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0],qApp->arguments());
}
