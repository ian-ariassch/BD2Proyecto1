#include "mainwindow.h"
#include "mainwindow.cpp"
#include <QApplication>
#include <QFile>
#include <QtDebug>
#include <QTableWidget>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    bool lock = 0;
    while(!lock){
    QApplication a(argc,argv);
    MainWindow w;
    w.setWindowTitle("Database");
    w.show();

    QFile file("../BD2Proyect/answerQuery.csv");
    QStringList word;
    QString merged;
    int columns = 1;
    bool determinedcols = 0;
    int rows = -1;
    bool quoted = 0;
    QStringList wordList;
        if (!file.open(QIODevice::ReadOnly)) {
                return 1;
            }
        QString onechar = file.read(1);
        while (!file.atEnd()) {
            if(!quoted)
            {
            while(onechar!=';' and onechar!='\n')
            {
                word.append(onechar);
                onechar = file.read(1);
            }

            for(int i=0;i<word.size();i++)
            {
                merged.insert(merged.size(),word[i]);
            }
            if(onechar=='\n' and determinedcols == 0)
            {
                columns = wordList.size()+1;
                determinedcols = 1;
            }
            if(onechar=='\n')
            {
                rows++;
            }
            onechar = file.read(1);
            word.clear();
            wordList.append(merged);
            merged.clear();
            if(onechar == '"'){quoted=1;}
            }
            else
            {
                word.append(onechar);
                onechar = file.read(1);
                if(onechar=='"')quoted=0;
            }
        }
   qDebug() << rows;
   QStringList labels;
   for(int i=0;i<wordList.size();i++)
   {
       if(i<columns)labels.append(wordList[i]);
   }
   w.ui->tableWidget->setColumnCount(columns);
   w.ui->tableWidget->setRowCount(rows);
   w.ui->tableWidget->setHorizontalHeaderLabels(labels);
   int i = labels.size();

      for(int j=0;j<rows;j++)
      {
          for(int k=0; k<columns;k++)
          {
              QTableWidgetItem *temp = new QTableWidgetItem(wordList[i],0);
               w.ui->tableWidget->setItem(j,k,temp);
               i++;
          }
      }
    return a.exec();
    }

}


