#include "deserializers.h"

Cliente* deserializers::QJsonValueToCliente(const QJsonValue& qjv)
{
	std::string CF;
	std::string nome;
	std::string cognome;
	std::string numero_tel;
	double sconto;
	std::string PIVA;
	Cliente* c;

	CF = qjv.toObject().value("CF").toString().toStdString();
	nome = qjv.toObject().value("nome").toString().toStdString();
	cognome = qjv.toObject().value("cognome").toString().toStdString();
	numero_tel = qjv.toObject().value("numero_telefono").toString().toStdString();
	sconto = qjv.toObject().value("sconto").toDouble();
	PIVA = qjv.toObject().value("PIVA").toString().toStdString();
	if(PIVA.empty()) //controllo questo e non lo sconto perché in teoria potrebbe essere 0 anche per una azienda
		c = new Privato(nome,cognome,CF,numero_tel);
	else
		c = new Rappresentante(nome, cognome, CF, numero_tel, sconto, PIVA);
	return c;
}

Meccanico* deserializers::QJsonValueToMeccanico(const QJsonValue& qjv)
{
	std::string CF;
	std::string nome;
	std::string cognome;
	std::string numero_tel;
	double stipendio;

	CF = qjv.toObject().value("CF").toString().toStdString();
	nome = qjv.toObject().value("nome").toString().toStdString();
	cognome = qjv.toObject().value("cognome").toString().toStdString();
	numero_tel = qjv.toObject().value("numero_tel").toString().toStdString();
	stipendio = qjv.toObject().value("stipendio").toDouble();

	return new Meccanico(nome,cognome,CF,numero_tel,stipendio);
}

Manutenzione* deserializers::QJsonValueToManutenzione(const QJsonValue& qjv)
{
	u_int id;
	std::string targa;
	std::string CF_cliente;
	std::string CF_meccanico;
	double costo;
	std::string data;
	std::string descrizione;

	id = qjv.toObject().value("id").toInt();
	targa = qjv.toObject().value("targa").toString().toStdString();
	CF_cliente = qjv.toObject().value("CF_cliente").toString().toStdString();
	CF_meccanico = qjv.toObject().value("CF_meccanico").toString().toStdString();
	costo = qjv.toObject().value("costo").toDouble();
	data = qjv.toObject().value("data").toString().toStdString();
	descrizione = qjv.toObject().value("descrizione").toString().toStdString();

	return new Manutenzione(costo, id, targa, CF_cliente, CF_meccanico, descrizione, Data(data));

}
