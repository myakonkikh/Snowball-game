#include "mainwindow.h"

#include <QTimer>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    resize(480, 640);

    QTimer *timer = new QTimer(this);
    timer->start();

    connect(timer, &QTimer::timeout,
            [timer, this]
            {
                timer->setInterval(rand() % 900 + 100);

                QPushButton *btn = new QPushButton("*", this);
                btn->setGeometry(rand() % (this->width() - SIZE_BTN), 100, SIZE_BTN, SIZE_BTN);
                btn->setStyleSheet("font: 30px");
                btn->show();

                QTimer *timer_btn = new QTimer(btn);
                timer_btn->start(rand() % 150 + 20);

                connect(timer_btn, &QTimer::timeout, btn,
                        [btn, this]
                        {
                            const int cursor_x = mapFromGlobal(cursor().pos()).x();
                            const int cursor_y = mapFromGlobal(cursor().pos()).y();
                            const int btn_x = btn->x();
                            const int btn_y = btn->y();

                            if ((btn_x <= cursor_x && cursor_x <= btn_x + SIZE_BTN) &&
                                (btn_y <= cursor_y && cursor_y <= btn_y + SIZE_BTN))
                            {
                                btn->move(btn_x, btn_y + 2);
                            }

                            else
                              btn->move(btn_x, btn_y + 1);

                            if (btn_y >= this->height())
                            {
                                this->setPalette(QPalette(Qt::red));
                                this->setWindowTitle(QStringLiteral("Game Over"));
                                btn->deleteLater();
                            }

                            else if (btn_x >= this->width() - SIZE_BTN)
                              btn->deleteLater();
                        });

                connect(btn, &QPushButton::clicked, [btn]{btn->deleteLater();});
            });
}

MainWindow::~MainWindow()
{
}
