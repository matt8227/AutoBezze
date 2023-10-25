#include "manutenzione.h"


Manutenzione::Manutenzione(double c, u_int i, std::string t, std::string cfc, std::string cfm, std::string desc, Data dat = Data()):
	costo(c), id(i), targa(t), CF_cliente(cfc), CF_meccanico(cfm), descrizione(desc), data(dat)
{

}

Manutenzione* Manutenzione::clone() const
{
	return new Manutenzione(*this);
}

double Manutenzione::getCosto() const
{
	return costo;
}

u_int Manutenzione::getId() const
{
	return id;
}

std::string Manutenzione::getTarga() const
{
	return targa;
}

std::string Manutenzione::getCF_cliente() const
{
	return CF_cliente;
}

std::string Manutenzione::getCF_meccanico() const
{
	return CF_meccanico;
}

std::string Manutenzione::getDescrizione() const
{
	return descrizione;
}

Data Manutenzione::getData() const
{
	return data;
}

vett<std::string> Manutenzione::getVettoreDati() const
{
	std::stringstream s;
	s.precision(2);

	vett<std::string> tmp;
	tmp.push_back(std::to_string(id));
	tmp.push_back(targa);
	tmp.push_back(CF_cliente);
	tmp.push_back(CF_meccanico);

	s<<std::fixed<<costo;
	tmp.push_back(s.str()); //Non dovrebbe servire, da investigare

	tmp.push_back(data.toStdString());
	tmp.push_back(descrizione);
	return tmp;
}

void Manutenzione::stampaDati() const
{
	std::cout<<id<<std::endl;
	std::cout<<targa<<std::endl;
	std::cout<<CF_cliente<<std::endl;
	std::cout<<CF_meccanico<<std::endl;
	std::cout<<costo<<std::endl;
	std::cout<<data.toStdString()<<std::endl;
	std::cout<<descrizione<<std::endl;

}
