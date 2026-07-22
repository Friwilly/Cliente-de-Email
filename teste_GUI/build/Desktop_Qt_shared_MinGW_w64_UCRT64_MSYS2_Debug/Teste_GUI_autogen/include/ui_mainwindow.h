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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_corpo;
    QLabel *label_senha;
    QLabel *label_destinatario;
    QLabel *label_remetente;
    QLabel *label_assunto;
    QLineEdit *txtAssunto;
    QLineEdit *txtDestinatario;
    QLineEdit *txtSenha;
    QLineEdit *txtRemetente;
    QTextEdit *txtCorpo;
    QPushButton *bntEnviar;
    QLabel *label_titulo;
    QPushButton *bntAnexo;
    QLabel *label_anexo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(600, 450);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_corpo = new QLabel(centralwidget);
        label_corpo->setObjectName("label_corpo");
        label_corpo->setGeometry(QRect(260, 150, 81, 20));
        label_senha = new QLabel(centralwidget);
        label_senha->setObjectName("label_senha");
        label_senha->setGeometry(QRect(320, 30, 101, 20));
        label_destinatario = new QLabel(centralwidget);
        label_destinatario->setObjectName("label_destinatario");
        label_destinatario->setGeometry(QRect(20, 90, 63, 20));
        label_remetente = new QLabel(centralwidget);
        label_remetente->setObjectName("label_remetente");
        label_remetente->setGeometry(QRect(20, 30, 81, 20));
        label_assunto = new QLabel(centralwidget);
        label_assunto->setObjectName("label_assunto");
        label_assunto->setGeometry(QRect(320, 90, 63, 20));
        txtAssunto = new QLineEdit(centralwidget);
        txtAssunto->setObjectName("txtAssunto");
        txtAssunto->setGeometry(QRect(320, 110, 251, 31));
        txtDestinatario = new QLineEdit(centralwidget);
        txtDestinatario->setObjectName("txtDestinatario");
        txtDestinatario->setGeometry(QRect(20, 110, 251, 31));
        txtSenha = new QLineEdit(centralwidget);
        txtSenha->setObjectName("txtSenha");
        txtSenha->setGeometry(QRect(320, 50, 251, 31));
        txtSenha->setEchoMode(QLineEdit::Normal);
        txtRemetente = new QLineEdit(centralwidget);
        txtRemetente->setObjectName("txtRemetente");
        txtRemetente->setGeometry(QRect(20, 50, 251, 31));
        txtCorpo = new QTextEdit(centralwidget);
        txtCorpo->setObjectName("txtCorpo");
        txtCorpo->setGeometry(QRect(40, 170, 501, 75));
        bntEnviar = new QPushButton(centralwidget);
        bntEnviar->setObjectName("bntEnviar");
        bntEnviar->setGeometry(QRect(300, 260, 231, 81));
        label_titulo = new QLabel(centralwidget);
        label_titulo->setObjectName("label_titulo");
        label_titulo->setGeometry(QRect(250, 0, 101, 20));
        bntAnexo = new QPushButton(centralwidget);
        bntAnexo->setObjectName("bntAnexo");
        bntAnexo->setGeometry(QRect(40, 260, 191, 29));
        label_anexo = new QLabel(centralwidget);
        label_anexo->setObjectName("label_anexo");
        label_anexo->setGeometry(QRect(40, 290, 191, 20));
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
        label_corpo->setText(QCoreApplication::translate("MainWindow", "Mensagem:", nullptr));
        label_senha->setText(QCoreApplication::translate("MainWindow", "Senha de App:", nullptr));
        label_destinatario->setText(QCoreApplication::translate("MainWindow", "Para:", nullptr));
        label_remetente->setText(QCoreApplication::translate("MainWindow", "Seu e-mail:", nullptr));
        label_assunto->setText(QCoreApplication::translate("MainWindow", "Assunto:", nullptr));
        bntEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar e-mail", nullptr));
        label_titulo->setText(QCoreApplication::translate("MainWindow", "CORREIO ILLIT", nullptr));
        bntAnexo->setText(QCoreApplication::translate("MainWindow", "Anexar arquivo", nullptr));
        label_anexo->setText(QCoreApplication::translate("MainWindow", "Nenhum arquivo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
