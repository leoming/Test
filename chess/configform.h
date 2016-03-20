#ifndef CONFIGFORM_H
#define CONFIGFORM_H

#include <qvariant.h>

class CChessGame;

#include <QtWidgets/QGroupBox>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

class ConfigForm : public QDialog
{
    Q_OBJECT
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox1;
    QGridLayout *gridLayout1;
    QLabel *textLabel2;
    QComboBox *comboRedPlayer;
    QLabel *textLabel3;
    QComboBox *comboBlackPlayer;
    QLabel *textLabel4;
    QComboBox *comboWhoIsOnTop;
    QPushButton *buttonCancel;
    QPushButton *buttonOK;
    QGroupBox *groupBox2;
    QGridLayout *gridLayout2;
    QComboBox *comboEngine;
    QLabel *textLabel6;
    QComboBox *comboComputerLevel;
    QLabel *textLabel5;

    void setupUi(QDialog *ConfigForm)
    {
        if (ConfigForm->objectName().isEmpty())
            ConfigForm->setObjectName(QString::fromUtf8("ConfigForm"));
        ConfigForm->resize(363, 243);
        gridLayout = new QGridLayout(ConfigForm);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox1 = new QGroupBox(ConfigForm);
        groupBox1->setObjectName(QString::fromUtf8("groupBox1"));
        //groupBox1->setColumnLayout(0, Qt::Vertical);
        groupBox1->setLayout(new QVBoxLayout());
        groupBox1->layout()->setSpacing(6);
        groupBox1->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout1 = new QGridLayout();
        QBoxLayout *boxlayout = qobject_cast<QBoxLayout *>(groupBox1->layout());
        if (boxlayout)
            boxlayout->addLayout(gridLayout1);
        gridLayout1->setAlignment(Qt::AlignTop);
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        textLabel2 = new QLabel(groupBox1);
        textLabel2->setObjectName(QString::fromUtf8("textLabel2"));
        textLabel2->setWordWrap(false);

        gridLayout1->addWidget(textLabel2, 0, 0, 1, 1);

        comboRedPlayer = new QComboBox(groupBox1);
        comboRedPlayer->setObjectName(QString::fromUtf8("comboRedPlayer"));

        gridLayout1->addWidget(comboRedPlayer, 0, 1, 1, 1);

        textLabel3 = new QLabel(groupBox1);
        textLabel3->setObjectName(QString::fromUtf8("textLabel3"));
        textLabel3->setWordWrap(false);

        gridLayout1->addWidget(textLabel3, 1, 0, 1, 1);

        comboBlackPlayer = new QComboBox(groupBox1);
        comboBlackPlayer->setObjectName(QString::fromUtf8("comboBlackPlayer"));

        gridLayout1->addWidget(comboBlackPlayer, 1, 1, 1, 1);

        textLabel4 = new QLabel(groupBox1);
        textLabel4->setObjectName(QString::fromUtf8("textLabel4"));
        textLabel4->setWordWrap(false);

        gridLayout1->addWidget(textLabel4, 2, 0, 1, 1);

        comboWhoIsOnTop = new QComboBox(groupBox1);
        comboWhoIsOnTop->setObjectName(QString::fromUtf8("comboWhoIsOnTop"));

        gridLayout1->addWidget(comboWhoIsOnTop, 2, 1, 1, 1);


        gridLayout->addWidget(groupBox1, 0, 0, 1, 2);

        buttonCancel = new QPushButton(ConfigForm);
        buttonCancel->setObjectName(QString::fromUtf8("buttonCancel"));

        gridLayout->addWidget(buttonCancel, 2, 1, 1, 1);

        buttonOK = new QPushButton(ConfigForm);
        buttonOK->setObjectName(QString::fromUtf8("buttonOK"));

        gridLayout->addWidget(buttonOK, 2, 0, 1, 1);

        groupBox2 = new QGroupBox(ConfigForm);
        groupBox2->setObjectName(QString::fromUtf8("groupBox2"));
        //groupBox2->setColumnLayout(0, Qt::Vertical);
        groupBox2->setLayout(new QVBoxLayout());
        groupBox2->layout()->setSpacing(6);
        groupBox2->layout()->setContentsMargins(11, 11, 11, 11);
        gridLayout2 = new QGridLayout();
        QBoxLayout *boxlayout1 = qobject_cast<QBoxLayout *>(groupBox2->layout());
        if (boxlayout1)
            boxlayout1->addLayout(gridLayout2);
        gridLayout2->setAlignment(Qt::AlignTop);
        gridLayout2->setObjectName(QString::fromUtf8("gridLayout2"));
        comboEngine = new QComboBox(groupBox2);
        comboEngine->setObjectName(QString::fromUtf8("comboEngine"));

        gridLayout2->addWidget(comboEngine, 0, 1, 1, 1);

        textLabel6 = new QLabel(groupBox2);
        textLabel6->setObjectName(QString::fromUtf8("textLabel6"));
        textLabel6->setWordWrap(false);

        gridLayout2->addWidget(textLabel6, 1, 0, 1, 1);

        comboComputerLevel = new QComboBox(groupBox2);
        comboComputerLevel->setObjectName(QString::fromUtf8("comboComputerLevel"));

        gridLayout2->addWidget(comboComputerLevel, 1, 1, 1, 1);

        textLabel5 = new QLabel(groupBox2);
        textLabel5->setObjectName(QString::fromUtf8("textLabel5"));
        textLabel5->setWordWrap(false);

        gridLayout2->addWidget(textLabel5, 0, 0, 1, 1);


        gridLayout->addWidget(groupBox2, 1, 0, 1, 2);


        retranslateUi(ConfigForm);
        QObject::connect(buttonOK, SIGNAL(clicked()), ConfigForm, SLOT(buttonOK_clicked()));
        QObject::connect(buttonCancel, SIGNAL(clicked()), ConfigForm, SLOT(buttonCancel_clicked()));
        QObject::connect(comboRedPlayer, SIGNAL(activated(int)), ConfigForm, SLOT(comboRedPlayer_activated(int)));
        QObject::connect(comboBlackPlayer, SIGNAL(activated(int)), ConfigForm, SLOT(comboBlackPlayer_activated(int)));

        QMetaObject::connectSlotsByName(ConfigForm);
    } // setupUi

    void retranslateUi(QDialog *ConfigForm)
    {
        ConfigForm->setWindowTitle(QApplication::translate("ConfigForm", "Config Form", 0));
        groupBox1->setTitle(QApplication::translate("ConfigForm", "Choose Mode", 0));
        textLabel2->setText(QApplication::translate("ConfigForm", "Red player", 0));
        comboRedPlayer->clear();
        comboRedPlayer->insertItems(0, QStringList()
         << QApplication::translate("ConfigForm", "Man", 0)
         << QApplication::translate("ConfigForm", "Computer", 0)
        );
        textLabel3->setText(QApplication::translate("ConfigForm", "Black Player", 0));
        comboBlackPlayer->clear();
        comboBlackPlayer->insertItems(0, QStringList()
         << QApplication::translate("ConfigForm", "Man", 0)
         << QApplication::translate("ConfigForm", "Computer", 0)
        );
        textLabel4->setText(QApplication::translate("ConfigForm", "Who is on top", 0));
        comboWhoIsOnTop->clear();
        comboWhoIsOnTop->insertItems(0, QStringList()
         << QApplication::translate("ConfigForm", "Red", 0)
         << QApplication::translate("ConfigForm", "Black", 0)
        );
        buttonCancel->setText(QApplication::translate("ConfigForm", "&Cancel", 0));
        buttonCancel->setShortcut(QApplication::translate("ConfigForm", "Alt+C", 0));
        buttonOK->setText(QApplication::translate("ConfigForm", "&OK", 0));
        buttonOK->setShortcut(QApplication::translate("ConfigForm", "Alt+O", 0));
        groupBox2->setTitle(QApplication::translate("ConfigForm", "Computer setting", 0));
        textLabel6->setText(QApplication::translate("ConfigForm", "Computer level", 0));
        comboComputerLevel->clear();
        comboComputerLevel->insertItems(0, QStringList()
         << QApplication::translate("ConfigForm", "1", 0)
         << QApplication::translate("ConfigForm", "2", 0)
         << QApplication::translate("ConfigForm", "3", 0)
         << QApplication::translate("ConfigForm", "4", 0)
         << QApplication::translate("ConfigForm", "5", 0)
        );
        textLabel5->setText(QApplication::translate("ConfigForm", "Choose Engine", 0));
    } // retranslateUi


public:
    ConfigForm(QWidget* parent = 0, Qt::WindowFlags fl = 0);
    ~ConfigForm();

    bool blackOnTop;
    bool blackIsMan;
    bool redIsMan;

    virtual void initializeAll( CChessGame * game );
    virtual void updateUI( bool refreshUI );
    virtual void applyChanges();

public slots:
    virtual void buttonOK_clicked();
    virtual void buttonCancel_clicked();
    virtual void comboRedPlayer_activated( int );
    virtual void comboBlackPlayer_activated( int );

protected:
    CChessGame* chessGame;
    int computerEngine;
    int computerLevel;

protected slots:
    virtual void languageChange();

};

#endif // CONFIGFORM_H
