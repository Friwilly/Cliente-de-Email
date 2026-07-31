#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPoint> // para lidar com a posição do mouse

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
    void mostrarMenuContextoLista(const QPoint &pos);
    void removerAnexo();
    void renomearAnexo();

private:
    Ui::MainWindow *ui;
    QStringList caminhosAnexos; // lista de caminhos de arquivos 
};
#endif 