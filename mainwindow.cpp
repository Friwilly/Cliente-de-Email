#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "EnviadorEmail.hpp"
#include <QMessageBox> // Para mostrar janelas de alerta popups
#include <QFileDialog> // Para abrir a janela de seleção
#include <QFileInfo> // Para extrair o nome do arquivo
#include <thread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicializa o handler do Vmime para Windows uma unica vez ao abrir o app
    vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_bntAnexo_clicked() {
    // Usamos getOpenFileNames para permitir seleção múltipla
    QStringList arquivosSelecionados = QFileDialog::getOpenFileNames(this, "Selecionar Anexos", "", "Todos os arquivos (*.*)");

    if(!arquivosSelecionados.isEmpty()) {
        caminhosAnexos = arquivosSelecionados;
    }

    if(caminhosAnexos.isEmpty()) return;

    //extrair apenas os nomes dos arquivos e adicionar um marcador (.)
    QStringList nomesArquivos;
    for(const QString& caminho : caminhosAnexos) {
        QFileInfo info(caminho);
        nomesArquivos.append(". " + info.fileName());
    }

    // Juntar os nomes usando QUEBRA DE LINHA em vez de virgula
    QString textoParaLabel = "Anexos (" + QString::number(caminhosAnexos.size()) + "):\n" + nomesArquivos.join("\n");

    ui->label_anexo->setWordWrap(true);
    ui->label_anexo->setText(textoParaLabel);
    ui->label_anexo->adjustSize(); // Recalcular o tamanho exato do label

    // Redimensiona o container pai que engloba o label e os botões
   QWidget* containerPai = ui->label_anexo->parentWidget();
   if(containerPai && containerPai != ui->centralwidget) {
        containerPai->adjustSize();
   }

   // Pegar a posição y real do container inteiro na janela
   int yContainer = containerPai ? containerPai->mapTo(this, QPoint(0,0)).y() : ui->label_anexo->mapTo(this, QPoint(0,0)).y();
   int alturaContainer = containerPai ? containerPai->height() : ui->label_anexo->height();

   int limiteInferior = yContainer + alturaContainer;
   int margemSeguranca = 30;

   int AlturaNecessaria = limiteInferior + margemSeguranca;

   if(AlturaNecessaria > this->height()) {
    this->resize(this->width(), AlturaNecessaria);
   }
}

void MainWindow::on_bntEnviar_clicked() {
    // 1. Resgata os textos da interface e converte QString para std::string
    std::string remetente = ui->txtRemetente->text().trimmed().toStdString();
    std::string senha = ui->txtSenha->text().trimmed().toStdString();
    std::string destinatario = ui->txtDestinatario->text().trimmed().toStdString();
    std::string assunto = ui->txtAssunto->text().trimmed().toStdString();

    // O QTextEit (corpo do email) usa toPlainText().trimmed() em vez de text().trimmed()
    std::string corpo = ui->txtCorpo->toPlainText().trimmed().toStdString();

    if(remetente.empty() || senha.empty() || destinatario.empty()) {
        QMessageBox::warning(this, "Erro", "Preencha remetente, senha e destinatario!");
        return;
    }

    ui->bntEnviar->setEnabled(false);
    ui->bntEnviar->setText("Enviando...");

    std::vector<std::string> listaAnexos;
    for(const QString& caminho : caminhosAnexos) {
        listaAnexos.push_back(caminho.toStdString());
    }

    std::thread([=]() {
        try {
            //essa função vai rodar em paralelo;
            if(EnviadorEmail::enviar(remetente, senha, destinatario, assunto, corpo, listaAnexos)) {
                // O Qt proíbe alterar a tela de dentro de uma thread
                // O invokeMethod devolve o controle para a janela principal
                QMetaObject::invokeMethod(this, [=]()  {
                    QMessageBox::information(this, "Sucesso", "Email enviado com sucesso!");

                    caminhosAnexos.clear();
                    ui->label_anexo->setText("Nenhum arquivo");

                    ui->bntEnviar->setEnabled(true);
                    ui->bntEnviar->setText("Enviar");
                });        
            }
        } catch (const std::string& erro) {
            //Em caso de erro tambem devolvemos o controle para a tela principal
            QMetaObject::invokeMethod(this, [=]() {
                QMessageBox::critical(this, "Erro de envio", QString::fromStdString("Falha: " + erro));

                ui->bntEnviar->setEnabled(true);
                ui->bntEnviar->setText("Enviar");
            });
        }
    }).detach(); // O .detach() avisa o sistema para deixar a Thread rodar livremente até acabar  
}