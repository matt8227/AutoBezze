#ifndef INSERISCICLIENTE_H
#define INSERISCICLIENTE_H

#include <QLayout>
#include <QSpinBox>
#include <QRadioButton>
#include <QPushButton>

#include "privato.h"
#include "rappresentante.h"
#include "lineedit.h"
#include "presenter.h"


class InserisciCliente: public QWidget{
	Q_OBJECT

private:

	Presenter* presenter;

	QLineEdit* InsertNome;
	QLineEdit* InsertCognome;
	LineEdit* InsertCF;
	LineEdit* InsertNTelefono;
	QRadioButton* PrivatoButton;
	QRadioButton* RappresentanteButton;
	QLineEdit* InsertNomeAzienda;
	LineEdit* InsertPIVA;
	QSpinBox* InsertSconto;

    //funzioni add
	void AddClientePrivatoFields(QVBoxLayout* mainLayout);
	void AddClienteRappresentanteFields(QVBoxLayout* mainLayout);
	void AddConfermaButton(QVBoxLayout* mainLayout);
	void AddBackButton(QVBoxLayout* mainLayout);

	//funzioni ausiliarie
	bool FieldsAreEmpty() const; //returna true sse tutti i campi sono empty
	bool PrivatoFieldsAreNotEmpty() const; //returna true sse tutti i campi Cliente Privato non sono vuoti
	bool RappresentanteFieldsAreNotEmpty() const; //returna true sse tutti i campi Cliente Rappresentante non sono vuoti
    void enableRappresentanteFields();
    void disableRappresentanteFields();
    void clearFields();

    //funzioni showmessaggi
    void showWarningRegistrazioneIncompleta();
    void showWarningInconsistenzaDati();
    void showRegistrazioneCliente();
    void showErroreInserimento(QString a);


public:
    explicit InserisciCliente(QWidget *parent= nullptr);

	void setPresenter(Presenter* c);


signals:
	void goToHomeSignal();
    void goToInserisciClienteSignal(); //?
private slots:
    void WarningRegistrazioneIncompletaSlot();
    void RegistrazioneClienteSlot();
    void enableRappresentanteFieldsSlot();
    void disableRappresentanteFieldsSlot();
    void clearFieldsSlot();
};

#endif // INSERISCICLIENTE_H
