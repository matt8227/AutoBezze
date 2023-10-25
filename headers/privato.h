#ifndef PRIVATO_H
#define PRIVATO_H
#include "cliente.h"
#include "vett.h"

#include <string>

class Privato : public Cliente
{
	public:
		/**
		 * @brief Privato Costruttore
		 * @param n nome
		 * @param c cognome
		 * @param cf codice fiscale
		 * @param nt numero telefono
		 * @param cg contribuzione guadagno
		 * @param pra probabilita ritenzione anno
		 */
		Privato(std::string n="", std::string c="", std::string cf="", std::string nt="", double cg=0, double pra=0);
		/**
		 * @brief clone clona l'oggetto
		 * @return puntatore al nuovo oggetto creato sull'heap
		 */
		virtual Privato* clone() const override;
		virtual void stampaDati() const override;

		virtual std::string serialize() const override;

		virtual vett<std::string> getVettoreDati() const override;

};

#endif // PRIVATO_H
