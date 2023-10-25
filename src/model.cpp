#include "model.h"

#define secondi_in_anno 31557600

Model::Model()
{

}

void Model::aggiungiCliente(DeepPtr<Cliente> c)
{
	clienti.push_back(c);
}
void Model::aggiungiMeccanico(DeepPtr<Meccanico> m)
{
	meccanici.push_back(m);
}
void Model::aggiungiManutenzione(DeepPtr<Manutenzione> m)
{
	manutenzioni.push_back(m);
}

void Model::rimuoviCliente(std::string CF)
{
	for(auto it = clienti.begin(); it != clienti.end(); ++it)
	{
        if((*it)->getCF() == CF)
		{
			clienti.erase(it);
			break;
		}
	}
}

void Model::rimuoviMeccanico(std::string CF)
{
	for(auto it = meccanici.begin(); it != meccanici.end();++it)
	{
        if((*it)->getCF() == CF)
		{
            it=meccanici.erase(it);
            break;
		}
	}
}

void Model::rimuoviManutenzione(u_int id)
{
	for(auto it = manutenzioni.begin(); it != manutenzioni.end();++it)
	{
        if((*it)->getId() == id)
		{
			manutenzioni.erase(it);
			break;
		}
	}
}

bool Model::ridondanzaCFClienti(std::string CF) const
{
	for(const auto& i : clienti)
		if(i->getCF() == CF)
			return true;
	return false;
}

bool Model::ridondanzaCFMeccanici(std::string CF) const
{
	for(const auto& i : meccanici)
		if(i->getCF() == CF)
			return true;
	return false;
}

u_int Model::contaManutenzioniCliente(std::string CF) const
{
	u_int tmp = 0;
	for(auto& i : manutenzioni)
		if(i->getCF_cliente()==CF)
			tmp++;
	return tmp;
}

vett<DeepPtr<Manutenzione>> Model::getManutenzioniCliente(std::string CF) const
{
	vett<DeepPtr<Manutenzione>> tmp;
	for(auto& i : manutenzioni)
	{
		if(i->getCF_cliente()==CF)
			tmp.push_back(i);
	}
	return tmp;
}

void Model::aggiornaProbabilitaRitenzioneAnno()
{
	int cnt;
	for(auto& i : clienti)
	{
		cnt = 0;
		vett<DeepPtr<Manutenzione>> tmp = getManutenzioniCliente(i->getCF());
		for(auto& j : tmp)
		{
			if(j->getData().diff(Data())<=secondi_in_anno)
				cnt++;
		}
		i->calcolaProbabilitaRitenzioneAnno(contaManutenzioniCliente(i->getCF()),cnt);
	}
}

double Model::calcolaSpesaTotaleCliente(std::string CF) const
{
	double tmp = 0;
	for(auto& i : manutenzioni)
	{
		if(i->getCF_cliente()==CF)
			tmp = tmp + i->getCosto();
	}
	return tmp;
}


void Model::aggiornaContribuzioneGuadagno()
{
	for(auto& i : clienti)
	{
		i->calcolaContribuzioneGuadagno(calcolaSpesaTotaleCliente(i->getCF()),margine);
	}
}



//premessa: questo metodo deve essere usato DOPO il caricamento dei vettori
u_int Model::generaIDManutenzione() const
{
	if(manutenzioni.getSize() == 0)
		return 1;

	return ((*(manutenzioni.end()-1))->getId())+1;
}

u_int Model::getScontoRappresentante(std::string CF) const
{
	for(const auto& i : clienti)
	{
		if(i->getCF()==CF)
		{
			if(dynamic_cast<Rappresentante*>(i.getPointer()))
				return dynamic_cast<Rappresentante*>(i.getPointer())->getSconto();
			else
				return 0;
		}
	}
	return 0;
}

std::string Model::getCognomeNomeCliente(std::string CF) const
{
    std::string CognomeNome;
	for(auto& i: clienti)
	{
		if(i->getCF()==CF)
		{
            CognomeNome=i->getCognome()+" "+i->getNome();
		}
	}
    return CognomeNome;
}

std::string Model::getCognomeNomeMeccanico(std::string CF) const
{
    std::string CognomeNome;
	for(auto& i: meccanici)
	{
		if(i->getCF()==CF)
		{
            CognomeNome=i->getCognome()+" "+i->getCognome();
		}
	}
    return CognomeNome;
}


const vett<DeepPtr<Cliente>>& Model::getClienti() const
{
	return clienti;
}
const vett<DeepPtr<Meccanico>>& Model::getMeccanici() const
{
	return meccanici;
}
const vett<DeepPtr<Manutenzione>>& Model::getManutenzioni() const
{
	return manutenzioni;
}

vett<DeepPtr<Cliente>>& Model::getClienti()
{
	return clienti;
}
vett<DeepPtr<Meccanico>>& Model::getMeccanici()
{
	return meccanici;
}
vett<DeepPtr<Manutenzione>>& Model::getManutenzioni()
{
	return manutenzioni;
}


