#ifndef PRESENTER_H
#define PRESENTER_H

#include "model.h"
#include "handler.h"
#include "ioutility.h"


class Presenter : public QObject
{
    Q_OBJECT

private:
    Handler* view;
    Model* model;
	IOUtility io;

public:
	explicit Presenter(QObject *parent = nullptr);

	//setta il model a cui fa riferimento il presenter
    void setModel(Model* m);

	//setta la view a cui fa riferimento il presenter
    void setView(Handler* v);

    //Setta nell'oggetto IOUtility le 3 paths per i file dati: clienti, meccanici e manutenzioni
    void ModificaPaths(QString clienteP, QString meccanicoP, QString manutenzioneP);

    //Restituisce la path del file dati dei clienti
    QString AggiornaPathClienti() const;

    //Restituisce la path del file dati dei meccanici
    QString AggiornaPathMeccanici() const;

    //Restituisce la path del file dati delle manutenzioni
    QString AggiornaPathManutenzioni() const;

    /*Dati i parametri di un cliente rappresentante lo crea e lo inserisce nel vettore clienti. Restituisce true sse
     *   non c'è gia un cliente con lo stesso CF(Codice Fiscale) dentro il vettore clienti (del model).
     *   Quindi: se true => nuovo cliente rappresentante registrato, se false => nuovo cliente rappresentante non registrato  */
    bool InserisciClienteRappresentante(QString nome,QString cognome, QString CF, QString NTelefono, QString NomeAzienda, QString PIVA, unsigned int sconto );

    /*Dati i parametri di un cliente privato lo crea e lo inserisce nel vettore clienti. Restituisce true sse
     *   non c'è gia un cliente con lo stesso CF(Codice Fiscale) dentro il vettore clienti (del model).
     *   Quindi: se true => nuovo cliente privato registrato, se false => nuovo cliente privato non registrato  */
    bool InserisciClientePrivato(QString nome, QString cognome, QString CF, QString NTelefono);

    /*Dati i parametri di un meccanico lo crea e lo inserisce nel vettore meccanici. Restituisce true sse
     *   non c'è gia un meccanico con lo stesso CF(Codice Fiscale) dentro il vettore meccanici (del model).
     *   Quindi: se true => nuovo meccanico registrato, se false => nuovo meccanico non registrato  */
    bool InserisciMeccanico(QString nome, QString cognome, QString CF, QString NTelefono, double stipendio);

    /*Dati i parametri di una manutenzione la crea e la inserisce nel vettore manutenzioni del model.
     *  Restituisce un int_u che corrisponde alla percentuale di sconto applicata a tale manutenzione  */
    u_int InserisciManutenzione(QString CFCliente, QString CFMeccanico, QString targa, double costo, QDate data, QString descrizione);

    //Dato un CF(Codice Fiscale), viene eliminato il cliente con CF uguale dal vettore clienti in model
    void EliminaCliente(QString CF);

    //Dato un id, viene eliminata la manutenzione con id uguale dal vettore manutenzioni in model
    void EliminaManutenzioe(QString id);

    //Dato un CF(Codice Fiscale), viene eliminato il meccanico con CF uguale dal vettore meccanici in model
    void EliminaMeccanico(QString CF);

    //Aggiorna i campi: Contribuzione guadagno e probabilita ritenzione anno di ogni cliente
    void CalcolaCgPr();

    //Restituisce il vettore clienti del model
    const vett<DeepPtr<Cliente>>& getClienti() const;

    //Restitusce il vettore meccanici del model
    const vett<DeepPtr<Meccanico>>& getMeccanici() const;

    //Restituisce il vettore manutenzioni del model
    const vett<DeepPtr<Manutenzione>>& getManutenzioni() const;

    //Dato un CF (Codice Fiscale), restituisce una QString con cognome e nome del cliente con CF uguale presente nel vettore clienti del model
    QString getCognomeNomeCliente(std::string CF) const;

    //Dato un CF (Codice Fiscale), restituisce una QString con cognome e nome del meccanico con CF uguale presente nel vettore meccanico del model
    QString getCognomeNomeMeccanico(std::string CF) const;

    /*Data una path controlla se il file presente a quella path:
     * Non esiste => restituisce la QString "Il file non esiste"
     * Esiste ma è solo di scrittura => restituisce la QString "Impossibile leggere file"
     * Esiste ma è solo solo di lettura => restituisce la QString "Impossibile scrivere file"
     * Esiste ed è di scrittura e lettura => restituisce una QString vuota ("")   */
    QString controllaPath(QString path) const;

    //Salva i dati contenuti dei vettori: clienti,  meccanici e manutenzioni del model nei corrispettivi file .json
    void salvaSuDisco() const;

    //Carica nel vettore clienti del model i dati contenuti nel file .json relativo ai clienti. Prima di farlo svuota il vettore clienti.
    void caricaClientiDaDisco();

    //Carica nel vettore meccanici del model i dati contenuti nel file .json relativo ai meccanici. Prima di farlo svuota il vettore meccanici.
    void caricaMeccaniciDaDisco();

    //Carica nel vettore manutenzioni del model i dati contenuti nel file .json relativo alle manutenzioni. Prima di farlo svuota il vettore manutenzioni.
    void caricaManutenzioniDaDisco();

    //Carica nei vettori clienti, meccanici e manutenzioni del model i dati contenuti nei relativi file .json. Prima di farlo li svuota.
    void caricaDaDisco();

signals:
    void ErroreNeiFileSignal();
};

#endif // PRESENTER_H
