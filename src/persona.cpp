#include "persona.h"
#include <iostream>

void Persona::stampaDati() const
{
	std::cout<<nome<<std::endl;
	std::cout<<cognome<<std::endl;
	std::cout<<CF<<std::endl;
	std::cout<<numero_telefono<<std::endl;
}

Persona::Persona(std::string n, std::string c, std::string cf, std::string nt):
	nome(n), cognome(c), CF(cf), numero_telefono(nt)
{

}

std::string Persona::getNome() const
{
	return nome;
}

std::string Persona::getCognome() const
{
	return cognome;
}

std::string Persona::getCF() const
{
	return CF;
}

std::string Persona::getNumero_telefono() const
{
	return numero_telefono;
}


std::string Persona::serialize() const
{
	return	"nome:" + nome + "\n" +
			"cognome:" + cognome + "\n" +
			"CF:" + CF + "\n" +
			"numero_telefono:" + numero_telefono;
}

vett<std::string> Persona::getVettoreDati() const
{
	vett<std::string> tmp;
	tmp.push_back(cognome);
	tmp.push_back(nome);
	tmp.push_back(CF);
	tmp.push_back(numero_telefono);
	return tmp;
}
