#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <Windows.h>

bool enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) {
        return TRUE;
    };

    HWND sndWnd;
    if (!(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL))) {
        return TRUE;
    }
    HWND targetWnd;
    if (!(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView"))) {
        return TRUE;
    }

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowFlag(Qt::FramelessWindowHint);

    HWND resultHwnd = NULL;
            EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
            HWND desktopHwnd = resultHwnd; //findDesktopIconWnd();
            if(desktopHwnd)
                SetParent((HWND)this->winId(), desktopHwnd);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //当鼠标左键点击时.
    if (event->button() == Qt::LeftButton)
    {
        m_move = true;
        //记录鼠标的世界坐标.
        m_startPoint = event->globalPos();
        //记录窗体的世界坐标.
        m_windowPoint = this->frameGeometry().topLeft();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        //移动中的鼠标位置相对于初始位置的相对位置.
        QPoint relativePos = event->globalPos() - m_startPoint;

        //然后移动窗体即可.
        //this->move(m_windowPoint + relativePos );

        //方法1：
                //QDesktopWidget* desktop = QApplication::desktop();
                QRect windowRect(QApplication::desktop()->availableGeometry());
                QRect widgetRect(this->geometry());
        //以下是防止窗口拖出可见范围外
        QPoint point=m_windowPoint + relativePos ;
                //左边
                if (point.x() <= 0)
                {
                    point = QPoint(0,point.y());
                }
                //右边
                int y = windowRect.bottomRight().y() - this->size().height();
                if (point.y() >= y && widgetRect.topLeft().y() >= y)
                {
                    point = QPoint(point.x(),y);
                }
                //上边
                if (point.y() <= 0)
                {
                    point = QPoint(point.x(),0);
                }
                //下边
                int x = windowRect.bottomRight().x() - this->size().width();
                if (point.x() >= x && widgetRect.topLeft().x() >= x)
                {
                    point = QPoint(x,point.y());
                }
                move(point);




                //方法2：
                //可以通过判断QRect windowRect是否包含（contains） QRect widgetRect 再移动
                //这里没有给出代码
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        //改变移动状态.
        m_move = false;
    }
}
