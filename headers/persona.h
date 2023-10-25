#ifndef PERSONA_H
#define PERSONA_H
#include <iostream>
#include <manutenzione.h>
#include <vett.h>
#include <string>

class Persona
{

	private:
		std::string nome;
		std::string cognome;
		std::string CF;
		std::string numero_telefono;
	public:
		/**
		 * @brief Persona Costruttore
		 * @param n nome
		 * @param c cognome
		 * @param cf codice fiscale
		 * @param nt numero telefono
		 */
		Persona(std::string n, std::string c, std::string cf, std::string nt);
		virtual ~Persona() = default;

		std::string getNome() const;
		std::string getCognome() const;
		std::string getCF() const;
		std::string getNumero_telefono() const;

		/**
		 * @brief serialize	serializzazione molto semplice in std::string
		 * @return std::string con il risultato della serializzazione
		 */
		virtual std::string serialize() const = 0;

		/**
		 * @brief clone clona l'oggetto di invocazione
		 * @return puntatore alla Persona creata sull'heap
		 */
		virtual Persona* clone() const = 0;
		virtual void stampaDati() const = 0;
		virtual vett<std::string> getVettoreDati() const =0;


};

#endif // PERSONA_H
