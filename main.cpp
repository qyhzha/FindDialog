#include <QApplication>
#include "QFindDialog.h"

int main(int argc, char **argv)
{
    int ret = 0;
    QApplication app(argc, argv);

    QFindDialog *dialog = QFindDialog::NewInstance();

    if (dialog != NULL)
    {
        dialog->show();

        ret = app.exec();
        delete dialog;
    }

    return ret;
}