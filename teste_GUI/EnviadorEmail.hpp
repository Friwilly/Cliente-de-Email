#ifndef ENVIADOREMAIL_HPP
#define ENVIADOREMAIL_HPP

#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/windows/windowsHandler.hpp>

class SmartCertificateVerifier : public vmime::security::cert::certificateVerifier {
public:
    void verify(const vmime::shared_ptr<vmime::security::cert::certificateChain>& chain, const vmime::string& hostname) override {
        //Sem std::cout na versão final para não poluir o terminal
    }
};

class EnviadorEmail {
public:
    //retorna true se enviou ou lança uma string com erro
    static bool enviar(const std::string& remetente, const std::string& senha, const std::string& destinatario, const std::string& assunto, const std::string& corpo, const std::vector<std::string>& Anexos) 
    {
        vmime::messageBuilder email;
        email.setExpeditor(vmime::mailbox(remetente));

        vmime::addressList to;
        to.appendAddress(vmime::make_shared<vmime::mailbox>(destinatario));
        email.setRecipients(to);

        email.setSubject(vmime::text(assunto));
        email.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(corpo));

        // LEMBRAR DE POR A LOGICA DO ANEXO AQUI DPS DO PRIMEIRO TESTE
        for (const std::string& caminho : Anexos) {
            if(!caminho.empty()) {
                // extrai apenas o nome e extensão
                size_t pos = caminho.find_last_of("/\\");
                std::string nomeArquivo = (pos != std::string::npos) ? caminho.substr(pos + 1) : caminho;

                // 2. Cria o anexo usanto o tipo generico, mas com o nome real
                vmime::shared_ptr<vmime::fileAttachment> anexo = vmime::make_shared<vmime::fileAttachment>(
                    caminho,
                    vmime::mediaType("application/octet-stream"),
                    vmime::text(nomeArquivo)
                );

                anexo->getFileInfo().setFilename(nomeArquivo);
                email.appendAttachment(anexo);
            }
        }

        vmime::shared_ptr<vmime::message> msg = email.construct();
        vmime::shared_ptr<vmime::net::session> sess = vmime::net::session::create();
        vmime::shared_ptr<vmime::net::transport> transport = sess->getTransport(vmime::utility::url("smtp://smtp.gmail.com:587"));

        transport->setCertificateVerifier(vmime::make_shared<SmartCertificateVerifier>());
        transport->setProperty("options.need-authentication", true);
        transport->setProperty("auth.username", remetente.c_str());
        transport->setProperty("auth.password", senha.c_str());
        //transport->setProperty("connection.tls", true);
        transport->setProperty("connection.tls", true);
        transport->setProperty("connection.tls.verify-certificate", true);

        try {
            transport->connect();
            transport->send(msg);
            transport->disconnect();
            return true;
        } catch(vmime::exception& e) {
            throw std::string(e.what());
        }

    }

};

#endif