#ifndef MODEL_H
#define MODEL_H
#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>

#include <string>
//#include <iostream>

#include "privato.h"
#include "rappresentante.h"
#include "meccanico.h"
#include "DeepPtr.h"
#include "vett.h"
#include "cliente.h"

typedef unsigned int u_int;

class Model
{

private:
	vett<DeepPtr<Cliente>> clienti;
	vett<DeepPtr<Meccanico>> meccanici;
	vett<DeepPtr<Manutenzione>> manutenzioni;
	u_int margine = 25;
public:
	Model();

	const vett<DeepPtr<Cliente>>& getClienti() const;
	const vett<DeepPtr<Meccanico>>& getMeccanici() const;
	const vett<DeepPtr<Manutenzione>>& getManutenzioni() const;
	vett<DeepPtr<Cliente>>& getClienti();
	vett<DeepPtr<Meccanico>>& getMeccanici();
	vett<DeepPtr<Manutenzione>>& getManutenzioni();

	//aggiungono un * al vettore corrispondente tramite pushback
	void aggiungiCliente(DeepPtr<Cliente>);
	void aggiungiMeccanico(DeepPtr<Meccanico>);
	void aggiungiManutenzione(DeepPtr<Manutenzione>);

	//rimuovono il * identificato dal parametro dal vettore corrispondente
    void rimuoviCliente(std::string CF);
    void rimuoviMeccanico(std::string CF);
	void rimuoviManutenzione(u_int id);

	//TRUE se è già presente un cf uguale a CF
	bool ridondanzaCFClienti(std::string CF) const;
	bool ridondanzaCFMeccanici(std::string CF) const;

	/**
	 * @brief contaManutenzioniCliente ritorna il numero di manutenzioni effettuate in totale dal cliente
	 * @param CF il codice fiscale del cliente
	 * @return il numero di manutenzioni effettuate in totale dal cliente
	 */
	u_int contaManutenzioniCliente(std::string CF) const;

	/**
	 * @brief aggiornaProbabilitaRitenzioneAnno	aggiorna la ProbabilitaRitenzioneAnno per tutti i clienti del vettore
	 */
	void aggiornaProbabilitaRitenzioneAnno();
	/**
	 * @brief getManutenzioniCliente restituisce un vettore con tutte le manutenzioni del cliente
	 * @param CF il codice fiscale del cliente interessato
	 * @return vett<DeepPtr<Manutenzione>>  con tutte le manutenzioni del cliente
	 */
	vett<DeepPtr<Manutenzione>> getManutenzioniCliente(std::string CF) const;

	/**
	 * @brief calcolaSpesaTotaleCliente	calcola la spesa totale (entrate) del cliente
	 * @param CF il codice fiscale del cliente interessato
	 * @return double rappresentate le entrare del cliente
	 */
	double calcolaSpesaTotaleCliente(std::string CF) const;

	/**
	 * @brief aggiornaContribuzioneGuadagno aggiorna la contribuzioneGuadagno per tutti i clienti nel vettore
	 */
	void aggiornaContribuzioneGuadagno();

	/**
	 * @brief	generaIDManutenzione crea un valore ID u_int da assegnare a manutenzione secondo l'idea
	 * @return	1 se non vi sono manutenzioni, n = max(id fra manutenzioni)+1 se ve ne sono
	 */
	u_int generaIDManutenzione() const;

	/**
	 * @brief getScontoRappresentante
	 * @param CF codice fiscale del rappresentante di cui serve ottenere lo sconto
	 * @return u_int con sconto del rappresentante
	 */
	u_int getScontoRappresentante(std::string CF) const;

	//restituiscono una string "cognome nome" del * con CF indicato
	std::string getCognomeNomeCliente(std::string CF) const;
	std::string getCognomeNomeMeccanico(std::string CF) const;

};

#endif // MODEL_H
