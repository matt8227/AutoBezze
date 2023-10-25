#include "mainwindow.h"
#include "home.h"
#include "inseriscicliente.h"
#include "model.h"
#include "privato.h"
#include "rappresentante.h"
#include "handler.h"
#include "data.h"
#include "vett.h"
#include <QApplication>
#include <QString>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Model m;
	Presenter c;
    Handler w;

    c.setModel(&m);
    c.setView(&w);
	w.setPresenter(&c);

    c.caricaDaDisco();

    w.show();

    w.setGeometry(
       QStyle::alignedRect(
           Qt::RightToLeft,
           Qt::AlignCenter,
           w.size(),
           qApp->desktop()->availableGeometry()
       )
                );


    return a.exec();
}
