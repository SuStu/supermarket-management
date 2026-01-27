#include "login_main_form.h"

#include <QApplication>
#include <QtSql/QSqlDatabase>
void openDatabase()
{

}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login_main_Form w;
    w.show();
    return a.exec();
}
#include "main.moc"
