#ifndef INSERISCIMANUTENZIONE_H
#define INSERISCIMANUTENZIONE_H

#include <QComboBox>
#include <QTextEdit>
#include <QDateEdit>

#include "lineedit.h"
#include "presenter.h"

class InserisciManutenzione: public QWidget
{
    Q_OBJECT
private:
	Presenter* presenter;

    QComboBox* ClienteCombo;
    QComboBox* MeccanicoCombo;
	LineEdit* targa;
    QTextEdit* descrizione;
    QLineEdit* costo;
    QDateEdit* data;

    void addBackButton(QVBoxLayout* mainLayout);
    void addFields(QVBoxLayout *mainLayout);

    void addConfermaButton(QVBoxLayout* mainLayout);
    bool FieldsAreNotEmpty() const;
    bool FieldsAreEmpty() const;
    void showRegistrazioneIncompleta();
    void showRegistrazioneManutenzione();
    void clearFields();
    void showErroreInserimento(QString text);

    void showManutenzioneScontata(u_int sconto, double costo);
    
public:
    InserisciManutenzione(QWidget* parent=nullptr);

	void setPresenter(Presenter* c);

    void aggiornaCombo();

signals:
    void goToHomeSignal();

public slots:
    void aggiornaPaginaSlot();

private slots:
    void clearFieldsSlot();
    void WarningRegistrazioneIncompletaSlot();
    void RegistrazioneManutenzioneSlot();
};

#endif // INSERISCIMANUTENZIONE_H
