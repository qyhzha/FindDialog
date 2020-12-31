#ifndef __QFINDDIALOG_H__
#define __QFINDDIALOG_H__

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

class QFindDialog : public QDialog
{
        Q_OBJECT

    protected:
        QLabel *label;
        QLineEdit *lineEdit;
        QGroupBox *groupBox;
        QCheckBox *caseCheckBox;
        QCheckBox *backwardCheckBox;
        QPushButton *findButton;
        QPushButton *closeButton;

    signals:
        void clicked(const QString &str, Qt::CaseSensitivity cs, bool direct);

    protected slots:
        void onTextChanged(const QString &text);
        void onClickedFindButton();

    protected:
        QFindDialog(QWidget *parent = NULL);
        bool construct();
        bool initFindDialog();
        bool initLeftLayout(QHBoxLayout *layout);
        bool initGroupBox();
        bool initRightLayout(QHBoxLayout *layout);

    public:
        static QFindDialog *NewInstance(QWidget *parent = NULL);
        virtual ~QFindDialog();
};

#endif
