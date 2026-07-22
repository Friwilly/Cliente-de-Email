#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "EnviadorEmail.hpp"
#include <QMessageBox> // Para mostrar janelas de alerta popups
#include <QFileDialog> // Para abrir a janela de seleção
#include <QFileInfo> // Para extrair o nome do arquivo

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicializa o handler do Vmime para Windows uma unica vez ao abrir o app
    vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_bntAnexo_clicked() {
    // Abre a janela para o usuário escolher o arquivo
    caminhoAnexo = QFileDialog::getOpenFileName(this, "Selecionar Anexo", "", "Todos os Arquivos (*.*)");

    // Se o usuário selecionou algo, mostramos o nome no label
    if(!caminhoAnexo.isEmpty()) {
        QFileInfo info(caminhoAnexo);
        ui->label_anexo->setText("Anexo: " + info.fileName());
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

    // 2. Validação simples
    if(remetente.empty() || senha.empty() || destinatario.empty()) {
        QMessageBox::warning(this, "Erro", "Preencha remetente, senha e destinatario!");
        return;
    }

    // 3. tenta enviar o email
    try {
        ui->bntEnviar->setEnabled(false); // Desativa o botão temporariamente
        ui->bntEnviar->setText("Enviando...");

        // Passamos o caminho do anexo para o EnviadorEmail
        if(EnviadorEmail::enviar(remetente, senha, destinatario, assunto, corpo, caminhoAnexo.toStdString())) {
            QMessageBox::information(this, "Sucesso", "Email enviado com sucesso!");
            
            // Limpa o anexo após o envio
            caminhoAnexo = "";
            ui->label_anexo->setText("Nenhum arquivo");
        }
    } catch (const std::string& erro) {
        QMessageBox::critical(this, "Erro de Envio", QString::fromStdString("Falha: " + erro));
    }

    // Restaura o botão
    ui->bntEnviar->setEnabled(true);
    ui->bntEnviar->setText("Enviar");
}