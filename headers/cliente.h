#ifndef CLIENTE_H
#define CLIENTE_H
#include "persona.h"

class Cliente : public Persona
{
	private:
		double contribuzioneGuadagno;
		double probabilitaRitenzioneAnno;
	protected:
		/**
		 * @brief setContribuzioneGuadagno	assegna il valore di cg a contribuzioneGuadagno
		 * @param cg
		 */
		void setContribuzioneGuadagno(double cg);

		/**
		 * @brief setProbabilitaRitenzioneAnno assegna il valore di pra a probabilitaRitenzioneAnno
		 * @param pra
		 */
		void setProbabilitaRitenzioneAnno(double pra);
	public:
		/**
		 * @brief Cliente
		 * @param n nome
		 * @param c cognome
		 * @param cf codice fiscale
		 * @param nt numero telefono
		 * @param cg contribuzione guadagno
		 * @param pra probabilità ritenzione anno
		 */
		Cliente(std::string n, std::string c, std::string cf, std::string nt, double cg=0, double pra=0);
		virtual ~Cliente() = default;
		/**
		 * @brief stampaDati	stampa a stdout tutti i dati dell'oggetto
		 */
		virtual void stampaDati() const = 0;
		/**
		 * @brief clone	clona l'oggetto
		 * @return un pointer a un clone dell'oggetto
		 */
		virtual Cliente* clone() const = 0;

		/**
		 * @brief calcolaContribuzioneGuadagno	sulla base della spesa fornita (le entrate) di quel cliente e del margine calcola
		 *										quanto guadagno ha portato quel cliente all'azienda e lo assegna a contribuzioneGuadagno
		 * @param spesa		le entrate (somma di "quanto ha pagato il cliente", detto brutalmente) che ha portato il cliente
		 * @param margine	il margine di guadagno sulla spesa (entrate). Default = 25.0
		 * @return il valore calcolato
		 */
		virtual double calcolaContribuzioneGuadagno(double spesa, double margine = 25.0);

		/**
		 * @brief calcolaProbabilitaRitenzioneAnno	sulla base del numero di visite e del numero di queste effettuate
		 *											l'ultimo anno, calcola un valore compreso fra 0 e 1 (escluso) che indica
		 *											la probabilità che il clienti si ripresenti nel prossimo anno.
		 * @param numero_visite			numero di visite effettuate in totale
		 * @param visite_ultimo_anno	visite effettuate dal cliente nell'ultimo anno
		 */
		virtual void calcolaProbabilitaRitenzioneAnno(int numero_visite, int visite_ultimo_anno); //Fra un anno, quanto probabile è che sia ancora qui il cliente?

		std::string virtual serialize() const override = 0;



		double getContribuzioneGuadagno() const;
		double getProbabilitaRitenzioneAnno() const;

		vett<std::string> getVettoreDati() const override = 0;

};

#endif // CLIENTE_H
