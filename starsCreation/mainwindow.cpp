#include "mainwindow.h"
#include "math.h"
#include <star.h>
#include "ui_mainwindow.h"
#include <QPainter>
#include <QTime>
#include <QtCore>

QElapsedTimer now;
galaxy *galactika = new galaxy;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    now.start();
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::update));
    ui->lineEdit_mass->setText(QString::number(galactika->GetMass()));
    timer->start(1);
    timerId = startTimer(1);
}
MainWindow::~MainWindow(){delete ui;}

const int topX0 = 100, topY0 = 100,/* h = 800,*/ length = 800;

void MainWindow::timerEvent(QTimerEvent *evt){
    if (evt->timerId() == timerId){
        QTime currTime = QTime::currentTime();
        ui->TimeLabel->setText(currTime.toString("hh:mm:ss"));
    }
}

istream& operator >> (istream& stream, MainWindow& w){
    Q_UNUSED(w);
    double size, distance;
    int count;
    stream >> count >> size >> distance;
    galactika->SetAll(count, size, distance);
    galactika = new galaxy;
    return stream;
}

ostream& operator << (ostream& out, MainWindow& w){
    Q_UNUSED(w);
    out << "Звёзды:" << endl;
    for(int i = 0; i < galactika->num; ++i){
        if(galactika->stars[i] != nullptr){
            out << "Масса = " << galactika->stars[i]->m << ";";
            out << " (" << galactika->stars[i]->x[0] << ";" << galactika->stars[i]->x[1] <<" );";
            out << " (" << galactika->stars[i]->v[0] << ";" << galactika->stars[i]->v[1] << " )" << endl;
        }
    }
    return out;
}

void MainWindow::paintEvent(QPaintEvent *e){
  Q_UNUSED(e);
  QPainter painter(this);
  QPen pen(Qt::black, 1, Qt::SolidLine);
  painter.setPen(pen);
  QBrush brush;//(Qt::yellow);
  brush.setStyle(Qt::SolidPattern);
  double coefX = length / 2 / 1e12; // system radius
  int centerX = length / 2;
  for(int i = 0; i < galactika->num; ++i){
      if(galactika->stars[i]){
          brush.setColor(galactika->stars[i]->col);
          if(!i) brush.setColor(Qt::yellow);
          painter.setBrush(brush);
          for(int k = 0; k < 2; ++k){
                    painter.drawEllipse(galactika->stars[i]->x[0] * coefX + centerX + topX0,
                                        galactika->stars[i]->x[1] * coefX + centerX + topY0, 6 + 4 * !i, 6 + 4 * !i);
          }
      }
  }
  galactika->move();
  galactika->Absorption();

  ui->lineEdit->setText(QString::number(star::starCounter));
  ui->timeText->setText(QTime(0,0,0).addMSecs(now.elapsed()).toString("hh:mm:ss:zzz"));
}

void MainWindow::on_pushButton_clicked(){
    star* s = galactika->getStars();
    ui->lineEditX->setText(QString::number(s[0].x[0]) + "; " + QString::number(s[0].x[1]));
    ui->lineEditV->setText(QString::number(s[0].v[0]) + "; " + QString::number(s[0].v[1]));
    ui->lineEditM->setText(QString::number(s[0].m));
    ui->lineEditX1->setText(QString::number(s[1].x[0]) + "; " + QString::number(s[1].x[1]));
    ui->lineEditV1->setText(QString::number(s[1].v[0]) + "; " + QString::number(s[1].v[1]));
    ui->lineEditM1->setText(QString::number(s[1].m));
    ui->lineEditX2->setText(QString::number(s[2].x[0]) + "; " + QString::number(s[2].x[1]));
    ui->lineEditV2->setText(QString::number(s[2].v[0]) + "; " + QString::number(s[2].v[1]));
    ui->lineEditM2->setText(QString::number(s[2].m));
    delete [] s;
}

