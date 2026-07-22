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
    // Usamos getOpenFileNames para permitir seleção múltipla
    QStringList arquivosSelecionados = QFileDialog::getOpenFileNames(this, "Selecionar Anexos", "", "Todos os arquivos (*.*)");

    // Se o usuário selecionou arquivos, subtituímos a lista atual
    if(!arquivosSelecionados.isEmpty()) {
        caminhosAnexos = arquivosSelecionados;

        // Criar uma lista apenas com os nomes dos arquivos
        QStringList nomesArquivos;
        for(const QString& caminho : caminhosAnexos) {
            QFileInfo info(caminho);
            nomesArquivos.append(info.fileName());
        }

        QString textoParaLabel = "Anexos: " + nomesArquivos.join(", ");
        //ativa a quebra de linha automatica
        ui->label_anexo->setWordWrap(true);
        ui->label_anexo->setText(textoParaLabel);
        ui->label_anexo->adjustSize();
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

        // Converte a lista do Qt para lista do C++
        std::vector<std::string> listaAnexosCpf;
        for(const QString& caminho : caminhosAnexos) {
            listaAnexosCpf.push_back(caminho.toStdString());
        }

        if(EnviadorEmail::enviar(remetente, senha, destinatario, assunto, corpo, listaAnexosCpf)) {
            QMessageBox::information(this, "Sucesso", "Email enviado com sucesso!");
            
            // Limpa o anexo após o envio
            caminhosAnexos.clear();
            ui->label_anexo->setText("Nenhum arquivo");
        }
    } catch (const std::string& erro) {
        QMessageBox::critical(this, "Erro de Envio", QString::fromStdString("Falha: " + erro));
    }

    // Restaura o botão
    ui->bntEnviar->setEnabled(true);
    ui->bntEnviar->setText("Enviar");
}