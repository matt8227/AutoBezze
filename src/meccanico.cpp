#include "meccanico.h"


Meccanico::Meccanico(std::string n, std::string c, std::string cf, std::string nt, double stip): Persona(n,c,cf,nt), stipendio(stip)
{

}

Meccanico *Meccanico::clone() const
{
	return new Meccanico(*this);
}

void Meccanico::stampaDati() const
{
	Persona::stampaDati(); // di sicuro deve stampare questi.
	std::cout<<stipendio<<std::endl;
}

std::string Meccanico::serialize() const
{
	return	Persona::serialize() + "\n" +
			"stipendio:" + std::to_string(stipendio);
}

double Meccanico::getStipendio() const
{
	return stipendio;
}

vett<std::string> Meccanico::getVettoreDati() const
{
	vett<std::string> tmp;
	tmp = Persona::getVettoreDati();
	std::stringstream s;
	s<<std::fixed<<std::setprecision(2)<<stipendio;
	tmp.push_back(s.str());
	return tmp;
}




