#ifndef MECCANICO_H
#define MECCANICO_H

#include "persona.h"
#include <sstream>
#include <iomanip>

class Meccanico : public Persona
{
private:
	double stipendio;

public:
	/**
	 * @brief Meccanico Costruttore
	 * @param n nome
	 * @param c cognome
	 * @param cf codice fiscale
	 * @param nt numero telefono
	 * @param stip stipendio
	 */
	Meccanico(std::string n, std::string c, std::string cf, std::string nt, double stip=1500);
	/**
	 * @brief clone clona l'oggetto di invocazione usando il costruttore di copia
	 * @return puntatore all'oggetto creato sull'heap
	 */
	virtual Meccanico* clone() const;
	virtual void stampaDati() const;

	virtual std::string serialize() const override;

	double getStipendio() const;

	virtual vett<std::string> getVettoreDati() const override;

};

#endif // MECCANICO_H
