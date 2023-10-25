#ifndef RAPPRESENTANTE_H
#define RAPPRESENTANTE_H

#include <iostream>
#include <sstream>
#include "cliente.h"

class Rappresentante : public Cliente
{
	private:
		unsigned int sconto;
		std::string PIVA;
		std::string nome_azienda;
		static double costo_stipulazione_contratto;
	public:
		/**
		 * @brief Rappresentante Costruttore
		 * @param n nome
		 * @param c cognome
		 * @param cf codice fiscale
		 * @param nt numero telefono
		 * @param scont sconto
		 * @param piv PIVA aka Partita IVA
		 * @param nom_az nome azienda
		 * @param cg contribuzione guadagno
		 * @param pra probabilità ritenzione anno
		 */
		Rappresentante(std::string n, std::string c, std::string cf, std::string nt, unsigned int scont, std::string piv, std::string nom_az, double cg=0, double pra=0);
		/**
		 * @brief clone clona l'oggetto
		 * @return puntatore al nuovo oggetto creato sull'heap tramite copy constructor
		 */
		virtual Rappresentante* clone() const override;

		virtual void stampaDati() const override;

		unsigned int getSconto() const;
		std::string getPIVA() const;
		std::string getNome_Azienda() const;

		/**
		 * @brief calcolaProbabilitaRitenzioneAnno	sulla base del numero di visite e del numero di queste effettuate
		 *											l'ultimo anno, calcola un valore compreso fra 0 e 1 (escluso) che indica
		 *											la probabilità che il clienti si ripresenti nel prossimo anno.
		 * @param numero_visite			numero di visite effettuate in totale
		 * @param visite_ultimo_anno	visite effettuate dal cliente nell'ultimo anno
		 */
		void virtual calcolaProbabilitaRitenzioneAnno(int numero_visite, int visite_ultimo_anno) override;

		/**
		 * @brief calcolaContribuzioneGuadagno	sulla base della spesa fornita (le entrate) di quel cliente e del margine calcola
		 *										quanto guadagno ha portato quel cliente all'azienda e lo assegna a contribuzioneGuadagno
		 * @param spesa		le entrate (somma di "quanto ha pagato il cliente", detto brutalmente) che ha portato il cliente
		 * @param margine	il margine di guadagno sulla spesa (entrate). Default = 25.0
		 * @return il valore calcolato
		 */
		double virtual calcolaContribuzioneGuadagno(double spesa, double margine = 25.0) override;

		virtual std::string serialize() const override;

		virtual vett<std::string> getVettoreDati() const override;
};

#endif // RAPPRESENTANTE_H
