#ifndef DATA_H
#define DATA_H
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <istream>
typedef unsigned int u_int;
class Data
{
	private:
		time_t t;
	public:
		/**
		 * @brief Data Costruttore di default
		 * @param a time_t che rappresenta un secondo del giorno della data da rappresentare
		 */
		Data(time_t a = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));

		/**
		 * @brief Data	costruttore che ricava il time_t corrispondente alla string s passata
		 * @param s		stringa che deve essere formattata secondo lo stile "YYYY-MM-DD"
		 */
		Data(std::string s);

		/**
		 * @brief ritorna i secondi passati da *this.t a d.getT()
		 * @param d
		 * @return unsigned long int rappresentante la differenza in secondi
		 */
		unsigned long int diff(const Data& d) const;

		/**
		 * @brief toStdString	trasforma il time_t interno in una data seguendo il formato YYYY-MM-DD
		 * @return la data trasformata
		 */
		std::string toStdString() const;
		/**
		 * @brief getT
		 * @return la data sottoforma di time_t
		 */
		time_t getT() const;

		/**
		 * @brief operator << overloading dell'operatore di output, stampa la data "YYYY-MM-DD"
		 * @param os
		 * @param dt
		 * @return
		 */
		friend std::ostream& operator<<(std::ostream& os, const Data& dt);
};

#endif // DATA_H
