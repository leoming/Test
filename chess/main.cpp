#include <QApplication>
#include "main_form.h"

int main(int argc, char ** argv )
{
    QApplication a(argc, argv);
    MainForm w;
    w.initializeAll();
    w.show();
    a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
    return a.exec();
}
