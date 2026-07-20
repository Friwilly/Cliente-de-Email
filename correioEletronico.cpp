#include <iostream>
#include <vmime/vmime.hpp>
#include <vmime/vmime.hpp>
#include <memory>  // Para std::shared_ptr

class SmartCertificateVerifier : public vmime::security::cert::certificateVerifier {
public:
    // Assinatura EXATA que a classe base espera
    void verify(std::shared_ptr<vmime::security::cert::certificateChain> chain, const vmime::string& hostname) override {
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
    email.setExpeditor(vmime::mailbox("endUsuario"));
    
    std::cout << "Digite o endereço de envio" << std::endl;
    std::string endDestino;
    std::cin >> endDestino;
    vmime::addressList to;
    to.appendAddress(vmime::make_shared<vmime::mailbox>("endDestino"));
    email.setRecipients(to);
    
    std::cout << "Digite o assunto do e-mail" << std::endl;
    std::string assunto;
    std::cin >> assunto;
    email.setSubject(vmime::text(assunto));
    
    std::cout << "Digite o corpo do email" << std::endl;
    std::string corpo;
    std::cin >> corpo;
    email.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(corpo));
    
    while(true){
      std::cout << "Caso queira anexar um arquivo, digite  1, caso contrário, digite 0" << std::endl;
      int valid;
      std::cin >> valid;
      
      if(valid == 1){
        std:: string caminho, tipo, descricao;
        
        std::cout << "Informe o caminho do arquivo (Formato: 'caminho ate a pasta'/'nome do arquivo.tipo')" << std::endl;
        std::cin >> caminho;
        //verificar se o caminho é  valido
        
        tipo = caminho.substr(caminho.length() - 3, 3);
        
        std::cout << "De uma descricao ao arquivo" << std::endl;
        
        vmime::shared_ptr<vmime::fileAttachment> anexo =
            vmime::make_shared<vmime::fileAttachment>(
                caminho,                        
                vmime::mediaType(tipo),          
                vmime::text(descricao)        
            );
            
            
            
        anexo->getFileInfo().setFilename("placeholder.txt");     // Nome no e-mail
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
    transport->setProperty("options.need-authentication", true);
    transport->setProperty("auth.username", "felipe.rocoelho@gmail.com");
    transport->setProperty("auth.password", "");
    
    transport->setProperty("connection.tls", true);
    transport->setProperty("connection.tls.verify-certificate", true);

    transport->connect();
    transport->send(msg);
    transport->disconnect();

    std::cout << "E-mail enviado com sucesso!" << std::endl;
    
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
    menu();

    return 0;
}
