#include "QFindDialog.h"

void QFindDialog::onTextChanged(const QString &text)
{
    findButton->setEnabled(!text.isEmpty());
}

void QFindDialog::onClickedFindButton()
{
    emit clicked(lineEdit->text(),
                 caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive,
                 !backwardCheckBox->isChecked());
}

QFindDialog::QFindDialog(QWidget *parent) : QDialog(parent)
{
    label = NULL;
    lineEdit = NULL;
    groupBox = NULL;
    caseCheckBox = NULL;
    backwardCheckBox = NULL;
    findButton = NULL;
    closeButton = NULL;

    setWindowTitle("查找");
    resize(500, 250);
}

bool QFindDialog::construct()
{
    bool ret = true;

    ret = ret && (label = new QLabel(this));
    ret = ret && (lineEdit = new QLineEdit(this));
    ret = ret && (groupBox = new QGroupBox(this));
    ret = ret && (caseCheckBox = new QCheckBox(this));
    ret = ret && (backwardCheckBox = new QCheckBox(this));
    ret = ret && (findButton = new QPushButton(this));
    ret = ret && (closeButton = new QPushButton(this));

    if (ret)
    {
        label->setText("查找目标(&F)：");
        label->setBuddy(lineEdit);

        lineEdit->clear();
        connect(lineEdit, SIGNAL(textChanged(QString)), this,
                SLOT(onTextChanged(QString)));

        ret = ret && initGroupBox();

        caseCheckBox->setText("匹配大小写");
        caseCheckBox->setChecked(true);

        backwardCheckBox->setText("反向查找");
        backwardCheckBox->setChecked(false);

        findButton->setText("查找");
        findButton->setDefault(true);
        findButton->setEnabled(false);
        connect(findButton, SIGNAL(clicked()), this, SLOT(onClickedFindButton()));

        closeButton->setText("关闭");
        connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

        ret = ret && initFindDialog();
    }

    return ret;
}

bool QFindDialog::initFindDialog()
{
    bool ret = true;
    QHBoxLayout *topLayout = new QHBoxLayout(this);

    ret = ret && topLayout;

    if (ret)
    {
        topLayout->setSpacing(4);
        //topLayout->setParent(this);

        ret = ret && initLeftLayout(topLayout);
        ret = ret && initRightLayout(topLayout);

        //setLayout(topLayout);
        //qDebug() << "topLayout->parent = " << topLayout->parent();
    }

    return ret;
}

bool QFindDialog::initLeftLayout(QHBoxLayout *layout)
{
    bool ret = true;
    QVBoxLayout *leftLayout = NULL;
    QHBoxLayout *hLayout = NULL;
    ret = ret && (leftLayout = new QVBoxLayout());
    ret = ret && (hLayout = new QHBoxLayout());

    if (ret)
    {
        leftLayout->setSpacing(4);
        //leftLayout->setParent(layout);

        hLayout->setSpacing(4);
        //hLayout->setParent(leftLayout);
        hLayout->addWidget(label, 1, Qt::AlignCenter);
        hLayout->addWidget(lineEdit, 1, Qt::AlignCenter);

        leftLayout->addLayout(hLayout, 1);
        leftLayout->addWidget(groupBox, 2);
        //qDebug() << "groupBox->parent = " << groupBox->parent();

        layout->addLayout(leftLayout, 1);
        //qDebug() << "leftLayout->parent = " << leftLayout->parent();
    }
    else
    {
        delete leftLayout;
        delete hLayout;
    }

    return ret;
}

bool QFindDialog::initGroupBox()
{
    bool ret = true;
    QVBoxLayout *vLayout = new QVBoxLayout(groupBox);
    ret = ret && vLayout;

    if (ret)
    {
        vLayout->setSpacing(4);
        vLayout->setContentsMargins(20, 0, 20, 0);
        vLayout->addWidget(backwardCheckBox, 1, Qt::AlignLeft);
        vLayout->addWidget(caseCheckBox, 1, Qt::AlignLeft);
        //groupBox->setLayout(vLayout);
    }

    return ret;
}

bool QFindDialog::initRightLayout(QHBoxLayout *layout)
{
    bool ret = true;
    QVBoxLayout *rightLayout = new QVBoxLayout();
    ret = ret && rightLayout;

    if (ret)
    {
        rightLayout->setSpacing(4);
        //rightLayout->setParent(layout);
        rightLayout->addWidget(findButton, 1, Qt::AlignCenter);
        rightLayout->addWidget(closeButton, 1, Qt::AlignCenter);
        rightLayout->addStretch(5);

        layout->addLayout(rightLayout, 1);
    }
    else
    {
        delete rightLayout;
    }

    return ret;
}

QFindDialog *QFindDialog::NewInstance(QWidget *parent)
{
    QFindDialog *ret = new QFindDialog(parent);

    if (ret == NULL || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

QFindDialog::~QFindDialog()
{
}
