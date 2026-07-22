#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    // Inicializa o sistema gráfico do Qt
    QApplication a(argc, argv);
    
    // Cria a sua janela principal (baseada no mainwindow.ui e mainwindow.cpp)
    MainWindow w;
    
    // Exibe a janela na tela
    w.show();
    
    // Coloca o programa em loop aguardando os cliques do usuário
    return a.exec();
}