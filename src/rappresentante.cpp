#include "rappresentante.h"

Rappresentante::Rappresentante(std::string n, std::string c, std::string cf, std::string nt, unsigned int scont, std::string piv,  std::string nom_az, double cg, double pra):
	Cliente(n, c, cf, nt,cg,pra), sconto(scont), PIVA(piv), nome_azienda(nom_az)
{

}

double Rappresentante::costo_stipulazione_contratto = 200;

Rappresentante *Rappresentante::clone() const
{
	return new Rappresentante(*this);
}

void Rappresentante::stampaDati() const
{
	Persona::stampaDati();
	std::cout<<sconto<<std::endl;
	std::cout<<PIVA<<std::endl;
	std::cout<<nome_azienda<<std::endl;
}

unsigned int Rappresentante::getSconto() const
{
	return sconto;
}

std::string Rappresentante::getPIVA() const
{
	return PIVA;
}

std::string Rappresentante::getNome_Azienda() const
{
	return nome_azienda;
}


//Maggior probabilità per via del "contratto"
void Rappresentante::calcolaProbabilitaRitenzioneAnno(int numero_visite, int visite_ultimo_anno)
{
	setProbabilitaRitenzioneAnno(std::tanh(numero_visite/2.5)*std::tanh(visite_ultimo_anno/2.0));
}

double Rappresentante::calcolaContribuzioneGuadagno(double spesa, double margine)
{
	setContribuzioneGuadagno(Cliente::calcolaContribuzioneGuadagno(spesa,margine) + Rappresentante::costo_stipulazione_contratto);
	return getContribuzioneGuadagno();
}


std::string Rappresentante::serialize() const
{
	return	Cliente::serialize() + "\n" +
			"sconto:" + std::to_string(sconto) + "\n" +
			"PIVA:" + PIVA + "\n" +
			"nome_azienda:" + nome_azienda;
}

vett<std::string> Rappresentante::getVettoreDati() const
{
	vett<std::string> tmp;
	std::stringstream s;
	s.str("");
	s.clear();

	tmp.push_back(getCognome());
	tmp.push_back(getNome());
	tmp.push_back(getCF());
	tmp.push_back(getNumero_telefono());


	s.precision(2);
	s<<std::fixed<<getContribuzioneGuadagno();
	tmp.push_back(s.str());
	s.str("");
	s.clear();

	s<<std::fixed<<getProbabilitaRitenzioneAnno();
	tmp.push_back(s.str());

	tmp.push_back(nome_azienda);
	tmp.push_back(PIVA);
	tmp.push_back(std::to_string(sconto));
	return tmp;
}
