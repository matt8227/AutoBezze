#include "presenter.h"
#include <QFile>
Presenter::Presenter(QObject *parent): QObject(parent){

}


void Presenter::setModel(Model *m)
{
    model=m;
}

void Presenter::setView(Handler *v)
{
    view=v;
}

void Presenter::ModificaPaths(QString clienteP, QString meccanicoP, QString manutenzioneP)
{
	io.setPaths(clienteP, meccanicoP, manutenzioneP);
}

QString Presenter::AggiornaPathClienti() const
{
	return io.getPathJsonClienti();
}

QString Presenter::AggiornaPathMeccanici() const
{
	return io.getPathJsonMeccanici();
}

QString Presenter::AggiornaPathManutenzioni() const
{
	return io.getPathJsonManutenzioni();
}

bool Presenter::InserisciClienteRappresentante(QString nome, QString cognome, QString CF, QString NTelefono, QString NomeAzienda, QString PIVA, unsigned int sconto)
{
    if(!model->ridondanzaCFClienti(CF.toStdString())){
        model->aggiungiCliente(DeepPtr<Cliente>(new Rappresentante(nome.toStdString(),
                                                                   cognome.toStdString(),
                                                                   CF.toStdString(),
                                                                   NTelefono.toStdString(),
                                                                   sconto,
                                                                   PIVA.toStdString(),
                                                                   NomeAzienda.toStdString())));
    return true;
    }else return false;
}

bool Presenter::InserisciClientePrivato(QString nome, QString cognome, QString CF, QString NTelefono)
{
    if(!model->ridondanzaCFClienti(CF.toStdString())){
        model->aggiungiCliente(DeepPtr<Cliente>(new Privato(nome.toStdString(),
                                                            cognome.toStdString(),
                                                            CF.toStdString(),
                                                            NTelefono.toStdString())));
        return true;
    }else return false;
}

void Presenter::EliminaCliente(QString CF)
{
    model->rimuoviCliente(CF.toStdString());
}

void Presenter::CalcolaCgPr()
{
    model->aggiornaContribuzioneGuadagno();
    model->aggiornaProbabilitaRitenzioneAnno();
}

bool Presenter::InserisciMeccanico(QString nome, QString cognome, QString CF, QString NTelefono, double stipendio)
{
    if(!model->ridondanzaCFMeccanici(CF.toStdString())){
        model->aggiungiMeccanico(DeepPtr<Meccanico>(new Meccanico(nome.toStdString(),
                                                                  cognome.toStdString(),
                                                                  CF.toStdString(),
                                                                  NTelefono.toStdString(),
                                                                  stipendio)));
        return true;
    }else return false;
}

void Presenter::EliminaMeccanico(QString CF)
{
    model->rimuoviMeccanico(CF.toStdString());
}

u_int Presenter::InserisciManutenzione(QString CFCliente, QString CFMeccanico, QString targa, double costo, QDate data, QString descrizione)
{
    QString date=data.toString(Qt::DateFormat(Qt::ISODate));
    std::string tmp=CFCliente.toStdString();
    std::string CFc=tmp.substr(0,16);
    tmp=CFMeccanico.toStdString();
    std::string CFm=tmp.substr(0,16);
    u_int sconto=model->getScontoRappresentante(CFc);
    costo=round((costo-(costo*(double(sconto)/100)))*1000)/1000;

    model->aggiungiManutenzione(DeepPtr<Manutenzione>(new Manutenzione(costo,
                                                                       model->generaIDManutenzione(),
                                                                       targa.toStdString(),
                                                                       CFc,
                                                                       CFm,
                                                                       descrizione.toStdString(),
                                                                       date.toStdString())));
    return sconto;
}

void Presenter::EliminaManutenzioe(QString id)
{
    model->rimuoviManutenzione(id.toUInt());
}

QString Presenter::controllaPath(QString path) const
{
    return io.controlloFile(path);
}

const vett<DeepPtr<Cliente> > &Presenter::getClienti() const
{
    return model->getClienti();
}

const vett<DeepPtr<Meccanico> > &Presenter::getMeccanici() const
{
    return model->getMeccanici();
}

const vett<DeepPtr<Manutenzione> > &Presenter::getManutenzioni() const
{
    return model->getManutenzioni();
}

QString Presenter::getCognomeNomeCliente(std::string CF) const
{
    return QString::fromStdString(model->getCognomeNomeCliente(CF));
}

QString Presenter::getCognomeNomeMeccanico(std::string CF) const
{
    return QString::fromStdString(model->getCognomeNomeMeccanico(CF));
}

void Presenter::salvaSuDisco() const
{
    io.salvaClientiSuDisco(model->getClienti());
    io.salvaMeccaniciSuDisco(model->getMeccanici());
    io.salvaManutenzioniSuDisco(model->getManutenzioni());
}

void Presenter::caricaDaDisco()
{
	connect(this, SIGNAL(ErroreNeiFileSignal()), view, SIGNAL(presenterSignal()));
    if(io.controlloFile(io.getPathJsonClienti()).size()>0 || io.controlloFile(io.getPathJsonMeccanici()).size()>0 || io.controlloFile(io.getPathJsonManutenzioni())>0)
        emit ErroreNeiFileSignal();

    else{
        caricaClientiDaDisco();
        caricaMeccaniciDaDisco();
        caricaManutenzioniDaDisco();
    }
}

void Presenter::caricaClientiDaDisco()
{
	model->getClienti().clear();
    io.caricaClientiDaDisco(model->getClienti());
}

void Presenter::caricaMeccaniciDaDisco()
{
	model->getMeccanici().clear();
    io.caricaMeccaniciDaDisco(model->getMeccanici());
}

void Presenter::caricaManutenzioniDaDisco()
{
	model->getManutenzioni().clear();
    io.caricaManutenzioniDaDisco(model->getManutenzioni());
}

