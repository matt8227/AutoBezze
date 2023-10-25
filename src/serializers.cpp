#include "Serializers.h"

QJsonObject Serializers::ClienteToQtJsonObject(Cliente * c)
{
	QJsonObject jo;
	jo["nome"] = QString::fromStdString(c->getNome());
	jo["cognome"] = QString::fromStdString(c->getCognome());
	jo["CF"] = QString::fromStdString(c->getCF());
	jo["numero_telefono"] = QString::fromStdString(c->getNumero_telefono());


	if(dynamic_cast<Rappresentante*> (c)) //downcast giustificati secondo Benedetto
	{
		jo["sconto"] = QString::number(static_cast<Rappresentante*>(c)->getSconto());
		jo["PIVA"] = QString::fromStdString(static_cast<Rappresentante*>(c)->getPIVA());
	}
	return jo;
}

QJsonObject Serializers::MeccanicoToQtJsonObject(Meccanico* m)
{
	QJsonObject jo;
	jo["nome"] = QString::fromStdString(m->getNome());
	jo["cognome"] = QString::fromStdString(m->getCognome());
	jo["CF"] = QString::fromStdString(m->getCF());
	jo["numero_telefono"] = QString::fromStdString(m->getNumero_telefono());
	jo["stipendio"] = QString::number(m->getStipendio());
	return jo;
}

QJsonObject Serializers::ManutenzioneToQtJsonObject(Manutenzione* m)
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
