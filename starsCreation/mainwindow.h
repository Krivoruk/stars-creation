#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QTimer>
#include <fstream>
using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTimer *timer = new QTimer(this);
    friend istream& operator >> (istream& in, MainWindow& w);
    friend ostream& operator << (ostream& out, MainWindow& w);
private:
    Ui::MainWindow *ui;
    int timerId;
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void on_pushButton_clicked();
    void timerEvent(QTimerEvent *evt);
};
#endif // MAINWINDOW_H
