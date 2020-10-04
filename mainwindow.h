#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void HandleButton();
  void QuitButton();

private:
  void ShowTime();

  Ui::MainWindow *ui;

  bool down;
  QPoint lastPos;

protected:
  bool nativeEvent(const QByteArray &eventType, void *message,
                   long *result) override;
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
};

#endif // MAINWINDOW_H
