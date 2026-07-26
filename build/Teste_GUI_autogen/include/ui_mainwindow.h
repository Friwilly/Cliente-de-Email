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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
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
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *bntAnexo;
    QPushButton *bntEnviar;
    QLabel *label_anexo;
    QWidget *widget1;
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
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 450);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_titulo = new QLabel(centralwidget);
        label_titulo->setObjectName("label_titulo");
        label_titulo->setGeometry(QRect(250, 0, 101, 20));
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(40, 270, 501, 71));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        bntAnexo = new QPushButton(widget);
        bntAnexo->setObjectName("bntAnexo");

        horizontalLayout->addWidget(bntAnexo);

        bntEnviar = new QPushButton(widget);
        bntEnviar->setObjectName("bntEnviar");

        horizontalLayout->addWidget(bntEnviar);


        verticalLayout_2->addLayout(horizontalLayout);

        label_anexo = new QLabel(widget);
        label_anexo->setObjectName("label_anexo");

        verticalLayout_2->addWidget(label_anexo);

        widget1 = new QWidget(centralwidget);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(20, 30, 551, 221));
        verticalLayout_3 = new QVBoxLayout(widget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_remetente = new QLabel(widget1);
        label_remetente->setObjectName("label_remetente");

        gridLayout->addWidget(label_remetente, 0, 0, 1, 1);

        label_senha = new QLabel(widget1);
        label_senha->setObjectName("label_senha");

        gridLayout->addWidget(label_senha, 0, 1, 1, 1);

        txtRemetente = new QLineEdit(widget1);
        txtRemetente->setObjectName("txtRemetente");

        gridLayout->addWidget(txtRemetente, 1, 0, 1, 1);

        txtSenha = new QLineEdit(widget1);
        txtSenha->setObjectName("txtSenha");
        txtSenha->setEchoMode(QLineEdit::Normal);

        gridLayout->addWidget(txtSenha, 1, 1, 1, 1);

        label_destinatario = new QLabel(widget1);
        label_destinatario->setObjectName("label_destinatario");

        gridLayout->addWidget(label_destinatario, 2, 0, 1, 1);

        label_assunto = new QLabel(widget1);
        label_assunto->setObjectName("label_assunto");

        gridLayout->addWidget(label_assunto, 2, 1, 1, 1);

        txtDestinatario = new QLineEdit(widget1);
        txtDestinatario->setObjectName("txtDestinatario");

        gridLayout->addWidget(txtDestinatario, 3, 0, 1, 1);

        txtAssunto = new QLineEdit(widget1);
        txtAssunto->setObjectName("txtAssunto");

        gridLayout->addWidget(txtAssunto, 3, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        label_corpo = new QLabel(widget1);
        label_corpo->setObjectName("label_corpo");

        verticalLayout_3->addWidget(label_corpo);

        txtCorpo = new QTextEdit(widget1);
        txtCorpo->setObjectName("txtCorpo");

        verticalLayout_3->addWidget(txtCorpo);

        MainWindow->setCentralWidget(centralwidget);
        txtCorpo->raise();
        txtAssunto->raise();
        txtDestinatario->raise();
        txtSenha->raise();
        txtRemetente->raise();
        label_corpo->raise();
        label_senha->raise();
        label_destinatario->raise();
        label_remetente->raise();
        label_assunto->raise();
        bntEnviar->raise();
        label_titulo->raise();
        bntAnexo->raise();
        label_anexo->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 600, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Correio Illit", nullptr));
        label_titulo->setText(QCoreApplication::translate("MainWindow", "CORREIO ILLIT", nullptr));
        bntAnexo->setText(QCoreApplication::translate("MainWindow", "Anexar arquivo", nullptr));
        bntEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar e-mail", nullptr));
        label_anexo->setText(QCoreApplication::translate("MainWindow", "Nenhum arquivo", nullptr));
        label_remetente->setText(QCoreApplication::translate("MainWindow", "Seu e-mail:", nullptr));
        label_senha->setText(QCoreApplication::translate("MainWindow", "Senha de App:", nullptr));
        label_destinatario->setText(QCoreApplication::translate("MainWindow", "Para:", nullptr));
        label_assunto->setText(QCoreApplication::translate("MainWindow", "Assunto:", nullptr));
        label_corpo->setText(QCoreApplication::translate("MainWindow", "Mensagem:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
