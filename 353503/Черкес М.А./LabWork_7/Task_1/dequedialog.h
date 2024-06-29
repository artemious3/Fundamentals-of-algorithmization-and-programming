#ifndef DEQUEDIALOG_H
#define DEQUEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QRandomGenerator>
#include <QVBoxLayout>
#include <algorithm>
#include <deque>
#include <vector>
#include "deque.h"

class DequeDialog : public QDialog {
  Q_OBJECT

 public:
  explicit DequeDialog(QWidget* parent = nullptr);
  void generateQueue();
  void removeElements();

 private:
  QListWidget* listWidget;
  std::deque<int> queue;
  std::deque<int> queue2;
  QLabel* maxLabel;
  QLabel* minLabel;
};

#endif  // DEQUEDIALOG_H
