#ifndef IOUTILITY_H
#define IOUTILITY_H

#include <QString>
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>

#include <string>

#include "privato.h"
#include "rappresentante.h"
#include "meccanico.h"
#include "DeepPtr.h"
#include "vett.h"
#include "cliente.h"

class IOUtility
{
	private:
		QString pathJsonClienti;
		QString pathJsonMeccanici;
		QString pathJsonManutenzioni;

	public:
		/**
		 * @brief IOUtility carica con QSettings i campi dati da disco
		 */
		IOUtility();

		/**
		 * @brief ~IOUtility Salva con QSettings i campi dati su disco
		 */
		~IOUtility();

		/**
		 * @brief setPaths imposta i campi dati
		 * @param pjc	path json cliente
		 * @param pjme	path json meccanici
		 * @param pjma	path json manutenzioni
		 */
		void setPaths(QString pjc, QString pjme, QString pjma);
		QString getPathJsonClienti() const;
		QString getPathJsonMeccanici() const;
		QString getPathJsonManutenzioni() const;

		/**
		 * @brief controlloFile controlla, in ordine, che il file presente in path sia: esistente, writeable, readable
		 * @param path	locazione del file
		 * @return una QString con il primo degli errori riscontrati
		 */
		QString controlloFile(QString path) const;

		/**
		 * @brief ClienteToQtJsonObject	serializza cliente a JSon
		 * @return QJsonObject con il cliente serializzato a Json
		 */
		static QJsonObject ClienteToQtJsonObject(Cliente*);
		/**
		 * @brief MeccanicoToQtJsonObject	serializza meccanico a JSon
		 * @return QJsonObject con il meccanico serializzato a Json
		 */
		static QJsonObject MeccanicoToQtJsonObject(Meccanico*);
		/**
		 * @brief ManutenzioneToQtJsonObject	serializza manutenzione a JSon
		 * @return QJsonObject con la manutenzione serializzata a Json
		 */
		static QJsonObject ManutenzioneToQtJsonObject(Manutenzione*);

		/**
		 * @brief QJsonValueToCliente
		 * @param c QJsonValue rappresentante un cliente in json
		 * @return un puntatore a un cliente nello heap;
		 */
		static Cliente* QJsonValueToCliente(const QJsonValue& c);

		/**
		 * @brief QJsonValueToMeccanico
		 * @param m QJsonValue rappresentante un meccanico in json
		 * @return un puntatore a un meccanico nello heap
		 */
		static Meccanico* QJsonValueToMeccanico(const QJsonValue& m);

		/**
		 * @brief QJsonValueToManutenzione
		 * @param m QJsonValue rappresentante una manutenzione in json
		 * @return un puntatore a una manutenzione nello heap
		 */
		static Manutenzione* QJsonValueToManutenzione(const QJsonValue& m);

		//Salvataggio su disco dei vettori tramite i metodi di serializzazione
		void salvaClientiSuDisco(const vett<DeepPtr<Cliente>>&) const;
		void salvaMeccaniciSuDisco(const vett<DeepPtr<Meccanico>>&) const;
		void salvaManutenzioniSuDisco(const vett<DeepPtr<Manutenzione>>&) const;

		//Caricamento da disco sui vettori tramite i metodi di deserializzazione
		void caricaClientiDaDisco(vett<DeepPtr<Cliente>>&);
		void caricaMeccaniciDaDisco(vett<DeepPtr<Meccanico>>&);
		void caricaManutenzioniDaDisco(vett<DeepPtr<Manutenzione>>&);

};

#endif // IOUTILITY_H
