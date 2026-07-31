#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "EnviadorEmail.hpp"
#include <QMessageBox> // Para mostrar janelas de alerta popups
#include <QFileDialog> // Para abrir a janela de seleção
#include <QInputDialog> // para renomear
#include <QFileInfo> // Para extrair o nome do arquivo
#include <QMenu>
#include <QAction>
#include <thread>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Inicializa o handler do Vmime para Windows uma unica vez ao abrir o app
    vmime::platform::setHandler<vmime::platforms::windows::windowsHandler>();

    // configura a lista para aceitar menu de contexto customizado
    ui->lista_anexos->setContextMenuPolicy(Qt::CustomContextMenu);

    // Conecta o evento de clique direito à nossa função
    connect(ui->lista_anexos, &QListWidget::customContextMenuRequested, this, &MainWindow::mostrarMenuContextoLista);
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

    // Limpa a lista visual antes de preencher
    ui->lista_anexos->clear();

    // Extrair apenas os nomes dos arquivos e adicionar
    for(const QString& caminho : caminhosAnexos) {
        QFileInfo info(caminho);
        ui->lista_anexos->addItem(info.fileName());
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

    std::vector<std::pair<std::string, std::string>> listaAnexos;
    //Percorre a lista visual e a lista oculta de caminhos ao mesmo tempo
    for(int i = 0; i < ui->lista_anexos->count(); ++i) {
        std::string caminhoReal = caminhosAnexos[i].toStdString();
        std::string nomeNaTela = ui->lista_anexos->item(i)->text().toStdString();

        listaAnexos.push_back({caminhoReal, nomeNaTela});
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
                    ui->lista_anexos->clear(); // esvaziar a lista de anexos atual

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

// função de criar e exibir o menu quando o usuario clicar com o botão direito
void MainWindow::mostrarMenuContextoLista(const QPoint &pos) {
    // Verifica se o clique foi em cima de um item válido e não no espaço vazio
    QListWidgetItem *item = ui->lista_anexos->itemAt(pos);
    if(!item) return;

    // Cria o menu
    QMenu menu(this);
    QAction *acaoRenomear = menu.addAction("Renomear");
    QAction *acaoRemover = menu.addAction("Remover");

    connect(acaoRenomear, &QAction::triggered, this, &MainWindow::renomearAnexo);
    connect(acaoRemover, &QAction::triggered, this, &MainWindow::removerAnexo);

    //Exibe o menu na exata posição do mouse na tela
    menu.exec(ui->lista_anexos->mapToGlobal(pos));
}

void MainWindow::renomearAnexo() {
    QListWidgetItem *item = ui->lista_anexos->currentItem();
    if(!item) return;

    bool ok;
    // Abre uma janelinha pop-up pedindo para o usuario digitar o novo
    QString novoNome = QInputDialog::getText(this, "Renomear Anexo", "Digite o novo nome do arquivo (com a extensão)", QLineEdit::Normal, item->text(), &ok);

    if(ok && !novoNome.isEmpty()) {
        item->setText(novoNome);
    }

}

// esta função efetivamente deleta o anexo
void MainWindow::removerAnexo() {
    int linhaSelecionada = ui->lista_anexos->currentRow();

    if(linhaSelecionada >= 0) {
        // remove visualmente da lista
        delete ui->lista_anexos->takeItem(linhaSelecionada);
        //remove o caminho corresbondete da variavel
        caminhosAnexos.removeAt(linhaSelecionada);
    }
}
