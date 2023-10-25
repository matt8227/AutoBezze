#include "ioutility.h"

IOUtility::IOUtility()
{
	QSettings impostazioni("B&B, Inc.","AutoBezzeG");
	impostazioni.beginGroup("paths");
	pathJsonClienti = impostazioni.value("pathJsonClienti","./clienti.json").toString();
	pathJsonMeccanici = impostazioni.value("pathJsonMeccanici","./meccanici.json").toString();
	pathJsonManutenzioni = impostazioni.value("pathJsonManutenzioni","./manutenzioni.json").toString();
	impostazioni.endGroup();
}

IOUtility::~IOUtility()
{
	QSettings impostazioni("B&B, Inc.","AutoBezzeG");
	impostazioni.beginGroup("paths");
	impostazioni.setValue("pathJsonClienti",pathJsonClienti);
	impostazioni.setValue("pathJsonMeccanici",pathJsonMeccanici);
	impostazioni.setValue("pathJsonManutenzioni",pathJsonManutenzioni);
	impostazioni.endGroup();
}

void IOUtility::setPaths(QString pjc, QString pjme, QString pjma)
{
	pathJsonClienti = pjc;
	pathJsonMeccanici = pjme;
	pathJsonManutenzioni = pjma;
}

QString IOUtility::getPathJsonClienti() const
{
	return pathJsonClienti;
}

QString IOUtility::getPathJsonMeccanici() const
{
	return pathJsonMeccanici;
}

QString IOUtility::getPathJsonManutenzioni() const
{
	return pathJsonManutenzioni;
}

QString IOUtility::controlloFile(QString path) const
{
	QFile t(path);
	if(!(t.exists()))
		return QString("Il file " + path + " non esiste.");

	t.open(QIODevice::Append); //NON WRITEONLY O SOVRASCRIVE

	if(!(t.isWritable()))
		return QString("Impossibile scrivere su "+path);
	t.close();

	t.open(QIODevice::ReadOnly);
	if(!(t.isReadable()))
		return QString("Impossibile leggere da "+path);

	return QString("");
}



void IOUtility::salvaClientiSuDisco(const vett<DeepPtr<Cliente>>& clienti) const
{
	QJsonArray arr;
	QFile jsonFile(pathJsonClienti);
	if(!jsonFile.open(QFile::WriteOnly))
	{
		throw std::runtime_error("Errore apertura file clienti in scrittura");
	}

	for(auto& i : clienti)
	{
		arr.push_back(ClienteToQtJsonObject(i.getPointer()));
	}
	jsonFile.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
	jsonFile.close();
}

void IOUtility::salvaMeccaniciSuDisco(const vett<DeepPtr<Meccanico>>& meccanici) const
{
	QJsonArray arr;
	QFile jsonFile(pathJsonMeccanici);
	if(!jsonFile.open(QFile::WriteOnly))
	{
		throw std::runtime_error("Errore apertura file meccanici in scrittura");
	}
	for(auto& i : meccanici)
	{
		arr.push_back(MeccanicoToQtJsonObject(i.getPointer()));
	}
	jsonFile.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
	jsonFile.close();
}
void IOUtility::salvaManutenzioniSuDisco(const vett<DeepPtr<Manutenzione>>& manutenzioni) const
{
	QJsonArray arr;
	QFile jsonFile(pathJsonManutenzioni);

	if(!jsonFile.open(QFile::WriteOnly))
	{
		throw std::runtime_error("Errore apertura file manutenzioni in scrittura");
	}
	for(auto& i : manutenzioni)
	{
		arr.push_back(ManutenzioneToQtJsonObject(i.getPointer()));
	}
	jsonFile.write(QJsonDocument(arr).toJson(QJsonDocument::Indented));
	jsonFile.close();
}



void IOUtility::caricaClientiDaDisco(vett<DeepPtr<Cliente>>& c)
{
	QFile file;
	file.setFileName(pathJsonClienti);
	if(!file.open(QIODevice::ReadOnly))
	{
		throw std::runtime_error("Errore apertura file clienti in lettura");
	}
	QString data = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonArray arr = doc.array();

	for(const auto& i : arr)
	{
		c.push_back(DeepPtr<Cliente>(QJsonValueToCliente(i)));
	}
}
void IOUtility::caricaMeccaniciDaDisco(vett<DeepPtr<Meccanico>>& m)
{
	QFile file;
	file.setFileName(pathJsonMeccanici);
	if(!file.open(QIODevice::ReadOnly))
	{
		throw std::runtime_error("Errore apertura file meccanici in lettura");
	}
	QString data = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonArray arr = doc.array();

	for(const auto& i : arr)
	{
		m.push_back(DeepPtr<Meccanico>(QJsonValueToMeccanico(i)));
	}
}
void IOUtility::caricaManutenzioniDaDisco(vett<DeepPtr<Manutenzione>>& m)
{
	QFile file;
	file.setFileName(pathJsonManutenzioni);
	if(!file.open(QIODevice::ReadOnly))
	{
		throw std::runtime_error("Errore apertura file manutenzioni in lettura");
	}
	QString data = file.readAll();
	file.close();
	QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
	QJsonArray arr = doc.array();

	for(const auto& i : arr)
	{
		m.push_back(DeepPtr<Manutenzione>(QJsonValueToManutenzione(i)));
	}
}
Cliente* IOUtility::QJsonValueToCliente(const QJsonValue& qjv)
{
	std::string CF;
	std::string nome;
	std::string cognome;
	std::string numero_tel;
	double contribuzioneGuadagno;
	double probabilitaRitenzioneAnno;
	double sconto;
	std::string PIVA;
	std::string nome_azienda;
	Cliente* c;

	CF = qjv.toObject().value("CF").toString().toStdString();
	nome = qjv.toObject().value("nome").toString().toStdString();
	cognome = qjv.toObject().value("cognome").toString().toStdString();
	numero_tel = qjv.toObject().value("numero_telefono").toString().toStdString();
	sconto = qjv.toObject().value("sconto").toString().toDouble();
	PIVA = qjv.toObject().value("PIVA").toString().toStdString();
	nome_azienda = qjv.toObject().value("nome_azienda").toString().toStdString();;
	contribuzioneGuadagno = qjv.toObject().value("contribuzioneGuadagno").toString().toDouble();
	probabilitaRitenzioneAnno = qjv.toObject().value("probabilitaRitenzioneAnno").toString().toDouble();
	if(PIVA.empty())
		c = new Privato(nome,cognome,CF,numero_tel, contribuzioneGuadagno, probabilitaRitenzioneAnno);
	else
		c = new Rappresentante(nome, cognome, CF, numero_tel, sconto, PIVA,		nome_azienda, contribuzioneGuadagno, probabilitaRitenzioneAnno);
	return c;
}

Meccanico* IOUtility::QJsonValueToMeccanico(const QJsonValue& qjv)
{
	std::string CF;
	std::string nome;
	std::string cognome;
	std::string numero_tel;
	double stipendio;

	CF = qjv.toObject().value("CF").toString().toStdString();
	nome = qjv.toObject().value("nome").toString().toStdString();
	cognome = qjv.toObject().value("cognome").toString().toStdString();
	numero_tel = qjv.toObject().value("numero_telefono").toString().toStdString();
	stipendio = qjv.toObject().value("stipendio").toString().toDouble();
	return new Meccanico(nome,cognome,CF,numero_tel,stipendio);
}

Manutenzione* IOUtility::QJsonValueToManutenzione(const QJsonValue& qjv)
{
	u_int id;
	std::string targa;
	std::string CF_cliente;
	std::string CF_meccanico;
	double costo;
	std::string data;
	std::string descrizione;

	id = qjv.toObject().value("id").toString().toUInt();
	targa = qjv.toObject().value("targa").toString().toStdString();
	CF_cliente = qjv.toObject().value("CF_cliente").toString().toStdString();
	CF_meccanico = qjv.toObject().value("CF_meccanico").toString().toStdString();
	costo = qjv.toObject().value("costo").toString().toDouble();
	data = qjv.toObject().value("data").toString().toStdString();
	descrizione = qjv.toObject().value("descrizione").toString().toStdString();

	return new Manutenzione(costo, id, targa, CF_cliente, CF_meccanico, descrizione, Data(data));

}


QJsonObject IOUtility::ClienteToQtJsonObject(Cliente * c)
{
	QJsonObject jo;
	jo["nome"] = QString::fromStdString(c->getNome());
	jo["cognome"] = QString::fromStdString(c->getCognome());
	jo["CF"] = QString::fromStdString(c->getCF());
	jo["numero_telefono"] = QString::fromStdString(c->getNumero_telefono());
	jo["contribuzioneGuadagno"] = QString::number(c->getContribuzioneGuadagno());
	jo["probabilitaRitenzioneAnno"] = QString::number(c->getProbabilitaRitenzioneAnno());

	if(dynamic_cast<Rappresentante*> (c)) //downcast giustificati secondo Benedetto
	{
		jo["sconto"] = QString::number(static_cast<Rappresentante*>(c)->getSconto());
		jo["PIVA"] = QString::fromStdString(static_cast<Rappresentante*>(c)->getPIVA());
		jo["nome_azienda"] = QString::fromStdString(static_cast<Rappresentante*>(c)->getNome_Azienda());
	}
	return jo;
}

QJsonObject IOUtility::MeccanicoToQtJsonObject(Meccanico* m)
{
	QJsonObject jo;
	jo["nome"] = QString::fromStdString(m->getNome());
	jo["cognome"] = QString::fromStdString(m->getCognome());
	jo["CF"] = QString::fromStdString(m->getCF());
	jo["numero_telefono"] = QString::fromStdString(m->getNumero_telefono());
	jo["stipendio"] = QString::number(m->getStipendio());
	return jo;
}

QJsonObject IOUtility::ManutenzioneToQtJsonObject(Manutenzione* m)
{
	QJsonObject jo;
	jo["costo"] = QString::number(m->getCosto());
	jo["id"] = QString::number(m->getId());
	jo["targa"] = QString::fromStdString(m->getTarga());
	jo["CF_cliente"] = QString::fromStdString(m->getCF_cliente());
	jo["CF_meccanico"] = QString::fromStdString(m->getCF_meccanico());
	jo["data"] = QString::fromStdString(m->getData().toStdString());
	jo["descrizione"] = QString::fromStdString(m->getDescrizione());
	return jo;
}


