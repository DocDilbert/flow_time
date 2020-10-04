#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTime>
#include <QTimer>
#include <stdio.h>

#ifdef Q_OS_WIN
#include <Windows.h>
#include <windowsx.h>
#endif // Q_OS_WIN

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {

  setWindowFlags(Qt::Window | Qt::FramelessWindowHint |
                 Qt::WindowStaysOnTopHint);
  //
  this->setAttribute(Qt::WA_TranslucentBackground, true);
  ui->setupUi(this);

  connect(ui->start_button_, SIGNAL(released()), this, SLOT(HandleButton()));
  connect(ui->quit_button_, SIGNAL(released()), this, SLOT(QuitButton()));
  // ui->flow_clock_->setSegmentStyle(QLCDNumber::Outline);
  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, this, &MainWindow::ShowTime);
  ShowTime();
  timer->start(1000);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::HandleButton() { printf("HALLO\n"); }
void MainWindow::QuitButton() { close(); }

void MainWindow::ShowTime() {
  QTime time = QTime::currentTime();
  QString text = time.toString("hh:mm");
  if ((time.second() % 2) == 0)
    text[2] = ' ';

  ui->flow_clock_->display(text);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message,
                             long *result) {
  MSG *msg = static_cast<MSG *>(message);

  if (msg->message == WM_NCHITTEST) {
    if (isMaximized()) {
      return false;
    }

    *result = 0;
    const LONG borderWidth = 8;
    RECT winrect;
    GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);

    // must be short to correctly work with multiple monitors (negative
    // coordinates)
    short x = msg->lParam & 0x0000FFFF;
    short y = (msg->lParam & 0xFFFF0000) >> 16;

    bool resizeWidth = minimumWidth() != maximumWidth();
    bool resizeHeight = minimumHeight() != maximumHeight();
    if (resizeWidth) {
      // left border
      if (x >= winrect.left && x < winrect.left + borderWidth) {
        *result = HTLEFT;
      }
      // right border
      if (x < winrect.right && x >= winrect.right - borderWidth) {
        *result = HTRIGHT;
      }
    }
    if (resizeHeight) {
      // bottom border
      if (y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        *result = HTBOTTOM;
      }
      // top border
      if (y >= winrect.top && y < winrect.top + borderWidth) {
        *result = HTTOP;
      }
    }
    if (resizeWidth && resizeHeight) {
      // bottom left corner
      if (x >= winrect.left && x < winrect.left + borderWidth &&
          y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        *result = HTBOTTOMLEFT;
      }
      // bottom right corner
      if (x < winrect.right && x >= winrect.right - borderWidth &&
          y < winrect.bottom && y >= winrect.bottom - borderWidth) {
        *result = HTBOTTOMRIGHT;
      }
      // top left corner
      if (x >= winrect.left && x < winrect.left + borderWidth &&
          y >= winrect.top && y < winrect.top + borderWidth) {
        *result = HTTOPLEFT;
      }
      // top right corner
      if (x < winrect.right && x >= winrect.right - borderWidth &&
          y >= winrect.top && y < winrect.top + borderWidth) {
        *result = HTTOPRIGHT;
      }
    }

    if (*result != 0)
      return true;

    QWidget *action = QApplication::widgetAt(QCursor::pos());
    if (action == this) {
      *result = HTCAPTION;
      return true;
    }
  }

  return false;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    down = true;
    lastPos = event->globalPos();
  }

  QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
  down = false;
  QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
  if (down) {
    QPoint curPos = event->globalPos();
    if (curPos != lastPos) {
      QPoint diff = (lastPos - curPos);
      move(pos() - diff);
      lastPos = curPos;
    }
  }

  QMainWindow::mouseMoveEvent(event);
}