/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_titulo;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLabel *label_remetente;
    QLabel *label_senha;
    QLineEdit *txtRemetente;
    QLineEdit *txtSenha;
    QLabel *label_destinatario;
    QLabel *label_assunto;
    QLineEdit *txtDestinatario;
    QLineEdit *txtAssunto;
    QLabel *label_corpo;
    QTextEdit *txtCorpo;
    QListWidget *lista_anexos;
    QPushButton *bntEnviar;
    QPushButton *bntAnexo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(896, 594);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icone_acoma.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_titulo = new QLabel(centralwidget);
        label_titulo->setObjectName("label_titulo");
        label_titulo->setGeometry(QRect(280, -40, 321, 261));
        label_titulo->setPixmap(QPixmap(QString::fromUtf8(":/logo_acoma.png")));
        label_titulo->setScaledContents(true);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 140, 871, 251));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_remetente = new QLabel(layoutWidget);
        label_remetente->setObjectName("label_remetente");

        gridLayout->addWidget(label_remetente, 0, 0, 1, 1);

        label_senha = new QLabel(layoutWidget);
        label_senha->setObjectName("label_senha");

        gridLayout->addWidget(label_senha, 0, 1, 1, 1);

        txtRemetente = new QLineEdit(layoutWidget);
        txtRemetente->setObjectName("txtRemetente");

        gridLayout->addWidget(txtRemetente, 1, 0, 1, 1);

        txtSenha = new QLineEdit(layoutWidget);
        txtSenha->setObjectName("txtSenha");
        txtSenha->setEchoMode(QLineEdit::EchoMode::Normal);

        gridLayout->addWidget(txtSenha, 1, 1, 1, 1);

        label_destinatario = new QLabel(layoutWidget);
        label_destinatario->setObjectName("label_destinatario");

        gridLayout->addWidget(label_destinatario, 2, 0, 1, 1);

        label_assunto = new QLabel(layoutWidget);
        label_assunto->setObjectName("label_assunto");

        gridLayout->addWidget(label_assunto, 2, 1, 1, 1);

        txtDestinatario = new QLineEdit(layoutWidget);
        txtDestinatario->setObjectName("txtDestinatario");

        gridLayout->addWidget(txtDestinatario, 3, 0, 1, 1);

        txtAssunto = new QLineEdit(layoutWidget);
        txtAssunto->setObjectName("txtAssunto");

        gridLayout->addWidget(txtAssunto, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        label_corpo = new QLabel(layoutWidget);
        label_corpo->setObjectName("label_corpo");

        verticalLayout_3->addWidget(label_corpo);

        txtCorpo = new QTextEdit(layoutWidget);
        txtCorpo->setObjectName("txtCorpo");

        verticalLayout_3->addWidget(txtCorpo);

        lista_anexos = new QListWidget(centralwidget);
        lista_anexos->setObjectName("lista_anexos");
        lista_anexos->setGeometry(QRect(30, 440, 361, 111));
        bntEnviar = new QPushButton(centralwidget);
        bntEnviar->setObjectName("bntEnviar");
        bntEnviar->setGeometry(QRect(490, 400, 361, 31));
        bntAnexo = new QPushButton(centralwidget);
        bntAnexo->setObjectName("bntAnexo");
        bntAnexo->setGeometry(QRect(30, 400, 361, 31));
        MainWindow->setCentralWidget(centralwidget);
        bntEnviar->raise();
        bntAnexo->raise();
        layoutWidget->raise();
        label_titulo->raise();
        lista_anexos->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 896, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Sistema de comunica\303\247\303\243o acoma", nullptr));
        label_remetente->setText(QCoreApplication::translate("MainWindow", "Seu e-mail:", nullptr));
        label_senha->setText(QCoreApplication::translate("MainWindow", "Senha de App:", nullptr));
        label_destinatario->setText(QCoreApplication::translate("MainWindow", "Para:", nullptr));
        label_assunto->setText(QCoreApplication::translate("MainWindow", "Assunto:", nullptr));
        label_corpo->setText(QCoreApplication::translate("MainWindow", "Mensagem:", nullptr));
        bntEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar e-mail", nullptr));
        bntAnexo->setText(QCoreApplication::translate("MainWindow", "Anexar arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
