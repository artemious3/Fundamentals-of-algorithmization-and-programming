#include "dequedialog.h"

DequeDialog::DequeDialog(QWidget* parent) : QDialog(parent) {
  setWindowTitle(
      tr("Создать двухсвязную очередь из случайных целых чисел\n. Удалить "
         "элементы, находящиеся между max и min."));
  setMinimumSize(700, 600);

  QPushButton* generateButton = new QPushButton(tr("Generate"));
  connect(generateButton, &QPushButton::clicked, this,
          &DequeDialog::generateQueue);

  QPushButton* removeButton = new QPushButton(tr("Remove"));
  connect(removeButton, &QPushButton::clicked, this,
          &DequeDialog::removeElements);

  maxLabel = new QLabel(tr("MAX"));
  minLabel = new QLabel(tr("MIN"));

  listWidget = new QListWidget(this);

  listWidget->setMinimumWidth(500);

  QVBoxLayout* labelsLayout = new QVBoxLayout;
  labelsLayout->addWidget(minLabel);
  labelsLayout->addWidget(maxLabel);

  QVBoxLayout* buttonsLayout = new QVBoxLayout;
  buttonsLayout->addWidget(generateButton);
  buttonsLayout->addWidget(removeButton);
  buttonsLayout->addLayout(labelsLayout);

  QHBoxLayout* mainLayout = new QHBoxLayout;
  mainLayout->addLayout(buttonsLayout);
  mainLayout->addWidget(listWidget);
  setLayout(mainLayout);
}

void DequeDialog::generateQueue() {

  listWidget->clear();
  queue.clear();

  for (int i = 0; i < 20; ++i) {
    int randomNumber = QRandomGenerator::global()->bounded(100);
    queue.push_back(randomNumber);
    listWidget->addItem(QString::number(randomNumber));
  }
  int maxValue = *std::max_element(queue.begin(), queue.end());
  int minValue = *std::min_element(queue.begin(), queue.end());
  maxLabel->setText(tr("MAX ") + QString::number(maxValue));
  minLabel->setText(tr("MIN ") + QString::number(minValue));
}

void DequeDialog::removeElements() {
  if (queue.empty()) {
    return;
  }
  queue2.clear();

  for (int i = 0; i < 20; ++i) {
    int randomNumber = QRandomGenerator::global()->bounded(100);
    queue2.push_back(randomNumber);
  }

  int maxValue = *std::max_element(queue.begin(), queue.end());
  int minValue = *std::min_element(queue.begin(), queue.end());

  auto itMax = std::find(queue.begin(), queue.end(), maxValue);
  auto itMin = std::find(queue.begin(), queue.end(), minValue);
  if (itMax < itMin) {
    queue.erase(itMax + 1, itMin);
    queue.insert(itMax, queue2.begin(), queue2.end());
  } else {
    queue.erase(itMin + 1, itMax);
    queue.insert(itMin, queue2.begin(), queue2.end());
  }
  // Вставляем вторую очередь на место удаленных элементов

  listWidget->clear();
  for (int value : queue) {
    listWidget->addItem(QString::number(value));
  }
}
