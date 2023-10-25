#ifndef MANUTENZIONE_H
#define MANUTENZIONE_H

#include "vett.h"
#include "data.h"
#include <string>
#include <iostream>
#include <cmath>
#include <sstream>

class Manutenzione
{
	private:
		double costo;
		u_int id;
		std::string targa;
		std::string CF_cliente;
		std::string CF_meccanico;
		std::string descrizione;
		Data data;
	public:
		/**
		 * @brief Manutenzione
		 * @param c costo della manutenzione
		 * @param i id della manutenzione
		 * @param t targa del veicolo su cui è stata effettuata
		 * @param cfc codice fiscale del cliente
		 * @param cfm codice fiscale del meccanico
		 * @param desc descrizione della manutenzione
		 * @param dat data in cui è stata svolta la manutenzione (default = odierna)
		 */
		Manutenzione(double c, u_int i, std::string t, std::string cfc, std::string cfm, std::string desc, Data dat);
		/**
		 * @brief clone clona l'oggetto di invocazione
		 * @return pointer a oggetto clonato nello heap
		 */
		Manutenzione* clone() const;

		void stampaDati() const;
		double getCosto() const;
		u_int getId() const;
		std::string getTarga() const;
		std::string getCF_cliente() const;
		std::string getCF_meccanico() const;
		Data getData() const;
		std::string getDescrizione() const;

		vett<std::string> getVettoreDati() const;
};

#endif // MANUTENZIONE_H
