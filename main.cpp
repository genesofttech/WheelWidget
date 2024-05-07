#include <QtWidgets>
#include <qmath.h>

#include "wheelwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(bool touch)
        : QMainWindow()
    {
        makeSlotMachine(touch);
        setCentralWidget(m_slotMachine);
    }

    void makeSlotMachine(bool touch)
    {
        //if (QApplication::desktop()->width() > 1000) {
            QFont f = font();
            qDebug() << "font size b4 is " << f.pointSize() << f.pixelSize();
            if (f.pointSize() != -1)
                f.setPointSize(f.pointSize() * 8);
            else
                f.setPixelSize(f.pixelSize() * 4);
            qDebug() << "font size aft is " << f.pointSize() << f.pixelSize();
            setFont(f);
        //}

        m_slotMachine = new QWidget(this);
        QGridLayout *grid = new QGridLayout(m_slotMachine);
        grid->setSpacing(0);

        QStringList sl, sl1, sl2;
        //sl << "Red" << "Magenta" << "Peach" << "Orange" << "Yellow" << "Citro" << "Green" << "Cyan" << "Blue" << "Violet";
        for (int i = 0; i < 12; i++) {
            sl << QString::number(i + 1).rightJustified(2, '0');
        }

        for (int i = 0; i < 60; i++) {
            sl1 << QString::number(i).rightJustified(2, '0');
        }

        sl2 << "AM" << "PM";

        m_wheel1 = new StringWheelWidget(touch);
        m_wheel1->setItems( sl );
        grid->addWidget( m_wheel1, 0, 0 );

        m_wheel2 = new StringWheelWidget(touch);
        m_wheel2->setItems( sl1 );
        grid->addWidget( m_wheel2, 0, 1 );

        m_wheel3 = new StringWheelWidget(touch);
        m_wheel3->setFreeSpinning(false);
        m_wheel3->setItems( sl2 );
        grid->addWidget( m_wheel3, 0, 2 );

        QPushButton *shakeButton = new QPushButton(tr("Shake"));
        connect(shakeButton, SIGNAL(clicked()), this, SLOT(rotateRandom()));

        grid->addWidget( shakeButton, 1, 0, 1, 3 );
    }

private slots:
    void rotateRandom()
    {
        m_wheel1->scrollTo(m_wheel1->currentIndex() + (qrand() % 200));
        m_wheel2->scrollTo(m_wheel2->currentIndex() + (qrand() % 200));
        m_wheel3->scrollTo(m_wheel3->currentIndex() + (qrand() % 200));
    }

private:
    QWidget *m_slotMachine;

    StringWheelWidget *m_wheel1;
    StringWheelWidget *m_wheel2;
    StringWheelWidget *m_wheel3;
};

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    bool touch = a.arguments().contains(QLatin1String("--touch"));
    MainWindow mw(touch);
#ifdef Q_WS_S60
    mw.showMaximized();
#else
    mw.show();
#endif
#ifdef Q_WS_MAC
    mw.raise();
#endif
    return a.exec();
}

#include "main.moc"
