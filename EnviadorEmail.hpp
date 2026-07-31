#ifndef ENVIADOREMAIL_HPP
#define ENVIADOREMAIL_HPP

#include <string>
#include <vmime/vmime.hpp>
#include <vmime/platforms/windows/windowsHandler.hpp>
#include <utility>

class SmartCertificateVerifier : public vmime::security::cert::certificateVerifier {
public:
    void verify(const vmime::shared_ptr<vmime::security::cert::certificateChain>& chain, const vmime::string& hostname) override {
        //Sem std::cout na versão final para não poluir o terminal
    }
};

class EnviadorEmail {
public:
    //retorna true se enviou ou lança uma string com erro
    static bool enviar(const std::string& remetente, const std::string& senha, const std::string& destinatario, const std::string& assunto, const std::string& corpo, const std::vector<std::pair<std::string, std::string>>& Anexos) 
    {
        vmime::messageBuilder email;
        email.setExpeditor(vmime::mailbox(remetente));

        vmime::addressList to;
        to.appendAddress(vmime::make_shared<vmime::mailbox>(destinatario));
        email.setRecipients(to);

        email.setSubject(vmime::text(assunto));
        email.getTextPart()->setText(vmime::make_shared<vmime::stringContentHandler>(corpo));

        // LEMBRAR DE POR A LOGICA DO ANEXO AQUI DPS DO PRIMEIRO TESTE
        for(const auto& parAnexo : Anexos) {
            const std::string& caminhoReal = parAnexo.first;
            const std::string& nomePersonalizado = parAnexo.second;

            if(!caminhoReal.empty()) {
                // Criar o anexo lendo do caminho real, mas usando o nome personalizado
                vmime::shared_ptr<vmime::fileAttachment> anexo = vmime::make_shared<vmime::fileAttachment>(
                    caminhoReal,
                    vmime::mediaType("Application/octet-stream"),
                    vmime::text(nomePersonalizado)
                );

                anexo->getFileInfo().setFilename(nomePersonalizado);
                email.appendAttachment(anexo);
            }
        }

        vmime::shared_ptr<vmime::message> msg = email.construct();
        vmime::shared_ptr<vmime::net::session> sess = vmime::net::session::create();
        // Nova logica de identificar o servidor smtp
        std::string smtpUrl = "smtp://smtp.gmail.com:587"; // Padrão

        // Converter o remetente para minúsculas para facilitar a busca
        std::string remetenteLower = remetente;
        for(auto& c : remetenteLower) c = tolower(c);

        if(remetenteLower.find("@outlook.com") != std::string::npos ||
            remetenteLower.find("@hotmail.com") != std::string::npos) {
            smtpUrl = "smtp://smtp-mail.outlook.com:587";
        } else if (remetenteLower.find("@yahoo.com") != std::string::npos ||
                    remetenteLower.find("@yahoo.com.br") != std::string::npos) {
            smtpUrl = "smtp://smtp.mail.yahoo.com:587";
        } else if (remetenteLower.find("@office365.com") != std::string::npos) {
            smtpUrl = "smtp://smtp.office365.com:587";
        }
        vmime::shared_ptr<vmime::net::transport> transport = sess->getTransport(vmime::utility::url(smtpUrl));

        transport->setCertificateVerifier(vmime::make_shared<SmartCertificateVerifier>());
        transport->setProperty("options.need-authentication", true);
        transport->setProperty("auth.username", remetente.c_str());
        transport->setProperty("auth.password", senha.c_str());
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