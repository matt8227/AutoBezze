#include "privato.h"
#include <iostream>
#include <sstream>

Privato::Privato(std::string n, std::string c, std::string cf, std::string nt , double cg, double pra):
	Cliente(n,c,cf,nt,cg,pra)
{

}

Privato* Privato::clone() const
{
	return new Privato(*this);
}

void Privato::stampaDati() const
{
	Cliente::stampaDati();
}

std::string Privato::serialize() const
{
	return Cliente::serialize();
}

vett<std::string> Privato::getVettoreDati() const
{
	std::stringstream s;
	s.precision(2);
	s.str("");
	s.clear();

	vett<std::string> tmp;
	tmp.push_back(getCognome());
	tmp.push_back(getNome());
	tmp.push_back(getCF());
	tmp.push_back(getNumero_telefono());

	s<<std::fixed<<getContribuzioneGuadagno();
	tmp.push_back(s.str());
	s.str("");
	s.clear();

	s<<std::fixed<<getProbabilitaRitenzioneAnno();
	tmp.push_back(s.str());
	return tmp;
}


