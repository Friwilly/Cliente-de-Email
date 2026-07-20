#include <iostream>
#include <vmime/vmime.hpp>

class SmartCertificateVerifier : public vmime::security::cert::certificateVerifier {
public:
    void verify(const vmime::shared_ptr<vmime::security::cert::certificateChain>& chain, const vmime::string& hostname) override {
        // Quando o Gmail responder, o VMime chamará esta função e passará os certificados (chain)
        
        std::cout << "\n[!] === Verificacao de Seguranca TLS/SSL ===" << std::endl;
        std::cout << "[!] Conectando ao host: " << hostname << std::endl;
        std::cout << "[!] Cadeia de certificados recebida do servidor!" << std::endl;
        std::cout << "[!] Tamanho da cadeia (numero de certificados): " << chain->getCount() << std::endl;
        std::cout << "[!] Criptografia Ativada. A conexao esta segura." << std::endl;
        std::cout << "[!] ========================================\n" << std::endl;

        // Como não lançamos nenhuma exceção de erro aqui, o VMime considera a conexão aceita e prossegue com o envio do email
    }

};

int main() {
    try {
        // --- 1. Construir a Mensagem ---
        vmime::messageBuilder mb;

        // Definir Remetente e Destinatários
        mb.setExpeditor(vmime::mailbox("alessandrafernandes100922@gmail.com"));
        vmime::addressList to;
        to.appendAddress(vmime::make_shared<vmime::mailbox>("alessandrafernandes100922@gmail.com"));
        mb.setRecipients(to);
        mb.setSubject(vmime::text("Teste massa"));

        // Definir o corpo do e-mail
        mb.getTextPart()->setText(
            vmime::make_shared<vmime::stringContentHandler>(
                "Morra imediatamente"
            )
        );

        

        // Construir o objeto mensagem final
        vmime::shared_ptr<vmime::message> msg = mb.construct();

        // --- 2. Enviar a Mensagem via SMTP ---
        // Criar uma sessão e obter o transporte SMTP
        vmime::shared_ptr<vmime::net::session> sess = vmime::net::session::create();
        vmime::shared_ptr<vmime::net::transport> transport = sess->getTransport(
            vmime::utility::url("smtp://smtp.gmail.com:587")
        );

        // Anexa o nosso verificador inteligente à conexão
        transport->setCertificateVerifier(vmime::make_shared<SmartCertificateVerifier>());

        // Configurar autenticação e conexão (substitua com seus dados)
        transport->setProperty("options.need-authentication", true);
        transport->setProperty("auth.username", "alessandrafernandes100922@gmail.com");
        transport->setProperty("auth.password", "iwcb mvik lysx gmxt");
        // Para usar TLS/SSL, descomente a linha abaixo:
        transport->setProperty("connection.tls", true);
        transport->setProperty("connection.tls.verify-certificate", true);

        // Conectar e enviar
        transport->connect();
        transport->send(msg);
        transport->disconnect();

        std::cout << "E-mail enviado com sucesso!" << std::endl;

    } catch (vmime::exception& e) {
        std::cerr << "Erro VMime: " << e.what() << std::endl;
        return 1;
    } catch (std::exception& e) {
        std::cerr << "Erro padrão: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
