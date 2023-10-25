#include "cliente.h"
#include <cmath>
#include <sstream>

void Cliente::stampaDati() const
{
	Persona::stampaDati();
	std::cout<<contribuzioneGuadagno<<std::endl;
	std::cout<<probabilitaRitenzioneAnno<<std::endl;
}


Cliente::Cliente(std::string n, std::string c, std::string cf, std::string nt, double cg, double pra):
	Persona(n,c,cf,nt), contribuzioneGuadagno(cg), probabilitaRitenzioneAnno(pra)
{

}

//Formula fornita dall'officina (nb, se 0 vuol dire che senza interventi diretti( es: pubblicità), il cliente verrà mai più)
void Cliente::calcolaProbabilitaRitenzioneAnno(int numero_visite, int visite_ultimo_anno)
{
	probabilitaRitenzioneAnno = std::tanh(numero_visite/5.0)*(std::tanh(visite_ultimo_anno/2.0));
}

void Cliente::setContribuzioneGuadagno(double cg)
{
	if(cg>=0)
		contribuzioneGuadagno = cg;
}

void Cliente::setProbabilitaRitenzioneAnno(double pra)
{
	if(pra>=0)
		probabilitaRitenzioneAnno = pra;
}

//spesa mensile = somma dei soldi che ha pagato per i lavori fatti (entrate)
//il metodo calcola il guadagno che ha portato ogni cliente all'azienda
double Cliente::calcolaContribuzioneGuadagno(double spesa, double margine)
{
	contribuzioneGuadagno = ((spesa)*100 - (spesa)* (100-margine))/100;
	return contribuzioneGuadagno;
}

std::string Cliente::serialize() const
{
	std::string tmp = Persona::serialize() + "\n" +
			"contribuzioneGuadagno:" + std::to_string(contribuzioneGuadagno) + "\n" +
			"probabilitaRitenzioneAnno:" + std::to_string(probabilitaRitenzioneAnno) + "\n";
	return tmp;
}

double Cliente::getContribuzioneGuadagno() const
{
	return contribuzioneGuadagno;
}

double Cliente::getProbabilitaRitenzioneAnno() const
{
	return probabilitaRitenzioneAnno;
}

vett<std::string> Cliente::getVettoreDati() const
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

	s<<std::fixed<<contribuzioneGuadagno;
	tmp.push_back(s.str());
	s.str("");
	s.clear();

	s<<std::fixed<<probabilitaRitenzioneAnno;
	tmp.push_back(s.str());
	return tmp;
}
