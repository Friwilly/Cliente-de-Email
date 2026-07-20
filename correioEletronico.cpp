#include <iostream>
#include <vmime/vmime.hpp>
#include <memory>  // Para std::shared_ptr

class SmartCertificateVerifier : public vmime::security::cert::certificateVerifier {
public:
    // Assinatura EXATA que a classe base espera
    void verify(const std::shared_ptr<vmime::security::cert::certificateChain>& chain, const vmime::string& hostname) override {
        std::cout << "\n[!] === Verificacao de Seguranca TLS/SSL ===" << std::endl;
        std::cout << "[!] Conectando ao host: " << hostname << std::endl;
        std::cout << "[!] Cadeia de certificados recebida do servidor!" << std::endl;
        if (chain) {
            std::cout << "[!] Tamanho da cadeia: " << chain->getCount() << std::endl;
        }
        std::cout << "[!] ========================================\n" << std::endl;
        // Não lança exceção, então aceita qualquer certificado
    }
};

void correio(){
    vmime::messageBuilder email;
    
    std::cout << "Confirmado. Para prosseguir, digite o endereço de email de envio" << std::endl;
    std::string endUsuario;
    std::cin >> endUsuario;
    //verificar se o endereço é  válido
    email.setExpeditor(vmime::mailbox(endUsuario));
    
    std::cout << "Digite o endereço de envio" << std::endl;
    std::string endDestino;
    std::cin >> endDestino;
    vmime::addressList to;
    to.appendAddress(vmime::make_shared<vmime::mailbox>(endDestino));
    email.setRecipients(to);
    
    std::cout << "Digite o assunto do e-mail" << std::endl;
    std::string assunto;
    std::getline(std::cin >> std::ws, assunto);
    email.setSubject(vmime::text(assunto));
    
    std::cout << "Digite o corpo do email" << std::endl;
    std::string corpo;
    std::getline(std::cin >> std::ws, corpo);
    email.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(corpo));
    
    while(true){
      std::cout << "Caso queira anexar um arquivo, digite  1, caso contrário, digite 0" << std::endl;
      int valid;
      std::cin >> valid;
      
      if(valid == 1){
        std:: string caminho, tipo, descricao;
        
        std::cout << "Informe o caminho do arquivo (Formato: 'caminho ate a pasta'/'nome do arquivo.tipo')" << std::endl;
        std::getline(std::cin >> std::ws, caminho);
        //verificar se o caminho é  valido
        
        // pega a extensão dinamicamente procurando pelo ultimo ponto
       size_t dotPos = caminho.find_last_of('.');
       if(dotPos != std::string::npos) {
        tipo = caminho.substr(dotPos + 1);
       } else {
        tipo = "txt"; // Fallback caso não ache ponto
       }
        
        std::cout << "De uma descricao ao arquivo" << std::endl;
        std::getline(std::cin >> std::ws, descricao);

        vmime::shared_ptr<vmime::fileAttachment> anexo =
            vmime::make_shared<vmime::fileAttachment>(
                caminho,                        
                vmime::mediaType(tipo),          
                vmime::text(descricao)        
            );
            
        // Procura a ultima barra
        size_t slashPos = caminho.find_last_of("/\\");

        // Recorta apenas o que vem depois da ultima barra (nome real do arquivo)
        std::string nomeRealDoArquivo = (slashPos != std::string::npos) ? caminho.substr(slashPos + 1) : "anexo_desconhecido." + tipo;    

        anexo->getFileInfo().setFilename(nomeRealDoArquivo);     // Nome no e-mail
        email.attach(anexo);
        
      }
      else if(valid == 0){
          break;
          
      }
      else{
          std::cout << "Opção inválida\n";
          continue;
          
      }
    }
    
    vmime::shared_ptr<vmime::message> msg = email.construct();
    
    vmime::shared_ptr<vmime::net::session> sess = vmime::net::session::create();
    vmime::shared_ptr<vmime::net::transport> transport = sess->getTransport(
        vmime::utility::url("smtp://smtp.gmail.com:587")
    );

    transport->setCertificateVerifier(vmime::make_shared<SmartCertificateVerifier>());

    // Fazer entrada dos dados de autenticação
    std::cout << "Gere uma nova ou utilize senha de app anterior: https://myaccount.google.com/apppasswords" << std::endl;
    std::string senhaEntrada;
    std::getline(std::cin >> std::ws, senhaEntrada); // Le a linha inteira, mesmo com espaços

    // Remove os espaços automaticamente para o usuario não errar
    std::string senhaLimpa = "";
    for(char c : senhaEntrada) {
        if(c != ' ') senhaLimpa += c;
    }
    
    transport->setProperty("options.need-authentication", true);
    // Usando .c_str() para converter std::string em const char*
    transport->setProperty("auth.username", endUsuario.c_str());
    transport->setProperty("auth.password", senhaLimpa.c_str()); // usar a senha sem espaços
    
    transport->setProperty("connection.tls", true);
    transport->setProperty("connection.tls.verify-certificate", true);

    // colocar um try-catch para o programa não capotar se a senha estiver errada
    try {
        std::cout << "Conectando ao Gmail..." << std::endl;
        transport->connect();
        std::cout << "Enviando mensagem..." << std::endl;
        transport->send(msg);
        transport->disconnect();
        std::cout << "\n[OK] Email enviado com sucesso" << std::endl;   
    }
    catch (vmime::exceptions::authentication_error& e) {
        std::cerr << "\n[ERRO] Falha na autenticação! Verifique se seu email ou a senha estão corretos" << std::endl;
    }
    catch (vmime::exception& e) {
        std::cerr << "\n[ERRO Vmime]: " << e.what() << std::endl;
    }
    
}

void menu(){
    std::cout << "Bem vindo ao correio de Illit\n";
    std::cout << "Para prosseguir, digite 1, como numero de confirmacao\n";
    int valid;
    std::cin >> valid;
    std::cout << std::endl;
    
    if(valid == 1){
        correio();
    }
    
    std::cout << "Encerrando..." << std::endl;
}

int main()
{
    try {
    menu();
    } catch (std::exception& e) {
        std::cerr << "Erro inesperado: " << e.what() << std::endl;
    }
    return 0;
}
