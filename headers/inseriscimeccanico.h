#ifndef INSERISCIMECCANICO_H
#define INSERISCIMECCANICO_H

#include <QLayout>
#include <QLabel>
#include <QApplication>

#include "meccanico.h"
#include "presenter.h"
#include "lineedit.h"

class InserisciMeccanico : public QWidget
{
	Q_OBJECT
private:

	Presenter* presenter;

	QLineEdit* InsertNome;
	QLineEdit* InsertCognome;
	LineEdit* InsertCF;
	LineEdit* InsertNTelefono;
	QLineEdit* InsertStipendio;

    //funzioni add
	void AddBackButton(QVBoxLayout* mainLayout);
    void AddFields(QVBoxLayout* mainLayout);
	void AddRegistraButton(QVBoxLayout* mainLayout);

    //funzioni ausiliarie
	bool FieldsAreEmpty() const; //returna true sse tutti field sono empty
	bool FieldsAreNotEmpty() const; //returna true sse tutti i field non sono empty
    void clearFields();

    //funzioni show messaggi
    void showWarningRegistrazioneIncompleta();
    void showErroreInserimento(QString text);
    void showRegistrazioneEffettuata();
    void showWarningInconsistenzaDati();

public:
    explicit InserisciMeccanico(QWidget *parent= nullptr);

	void setPresenter(Presenter* c);
signals:
	void goToHomeSignal();
	void goToInserisciMeccanicoSignal();

private slots:
    void WarningRegistrazioneIncompletaSlot();
    void RegistrazioneMeccanicoSlot();
    void clearFieldsSlot();
};

#endif // INSERISCIMECCANICO_H
