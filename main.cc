#include <stdio.h>
#include <stdlib.h>

#include <QApplication>
#include <QFile>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include <boost/accumulators/statistics/moment.hpp>
#include <boost/accumulators/statistics/stats.hpp>

#include "mainwindow.h"


int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QFile File("flow_clock.qss");
  File.open(QFile::ReadOnly);
  QString StyleSheet = QLatin1String(File.readAll());
  a.setStyleSheet(StyleSheet);

  MainWindow w;
  w.show();

  return a.exec();
}
