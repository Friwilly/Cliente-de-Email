#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {class MainWindow;}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Slot que responderá ao clique do botão
    void on_bntEnviar_clicked();
    void on_bntAnexo_clicked();

private:
    Ui::MainWindow *ui;
    QString caminhoAnexo; //variavel para armazenar o endereço do arquivo
};
#endif 