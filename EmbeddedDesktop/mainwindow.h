#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QLineEdit>
#include <QVBoxLayout>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
