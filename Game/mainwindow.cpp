#include "mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(480, 640);

    QTimer *timer = new QTimer(this);
    timer->start();

    connect(timer, &QTimer::timeout,
            [timer, this]()
            {
                timer->setInterval(rand() % 900 + 100);

                QPushButton *btn = new QPushButton("*", this);
                btn->setGeometry(rand() % (this->width() - SIZE_BTN), 100, SIZE_BTN, SIZE_BTN);
                btn->setStyleSheet("font: 30px");
                btn->show();

                QTimer *timer_btn = new QTimer(this);
                timer_btn->start(rand() % 150 + 20);

                connect(timer_btn, &QTimer::timeout, btn,
                        [btn, this]()
                        {
                            int cursor_x = mapFromGlobal(cursor().pos()).x();
                            int cursor_y = mapFromGlobal(cursor().pos()).y();

                            if (btn->x() <= cursor_x && cursor_x <= btn->x() + SIZE_BTN &&
                                btn->y() <= cursor_y && cursor_y <= btn->y() + SIZE_BTN)
                            {
                                btn->move(btn->x(), btn->y() + 2);
                            }

                            else
                              btn->move(btn->x(), btn->y() + 1);

                            if (btn->y() >= this->height())
                            {
                                this->setPalette(QPalette(Qt::red));
                                this->setWindowTitle("Game Over");
                                btn ->deleteLater();
                            }
                        });

                connect(btn, &QPushButton::clicked, [btn](){btn->deleteLater();});
            });
}

MainWindow::~MainWindow()
{
}
