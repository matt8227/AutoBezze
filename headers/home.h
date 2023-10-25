#ifndef HOME_H
#define HOME_H

#include <QMenuBar>
#include <QLineEdit>
#include <QFileDialog>

#include "presenter.h"
class home : public QWidget {
	Q_OBJECT
 private:

	Presenter* presenter;

    QLineEdit* ClienteP;
    QLineEdit* MeccanicoP;
    QLineEdit* ManutenzioneP;

    QString vPathClienti;
    QString vPathMeccanici;
    QString vPathManutenzioni;

    void AddButtons(QVBoxLayout* layout);

    void AddOptionsBar(QVBoxLayout* layout);

    void showChangePaths();

    QString showChoosePath();

    void aggiornaPath(QLineEdit* line, QString text);
    void showErrorePath(QString errore);

    void showErrorMessage(const char* e);

    void aggiornaPaths();

    void showDatiSalvati();

    void showErroreNeiFileCaricati();


public:
	explicit home(QWidget *parent = nullptr, Presenter* c=nullptr);

    void setHandler(Handler* h);

	void setPresenter(Presenter* c);

signals:
    void InserisciClienteButtonSignal () const;
	void InserisciMeccanicoButtonSignal() const;
    void InserisciManutenzioneButtonSignal() const;
    void MostraClientiButtonSignal() const;
    void MostraMeccaniciButtonSignal() const;
    void MostraManutenzioniButtonSignal() const;
    void SalvaSuDiscoSignal();
    void chiudiSignal();

public slots:
    void ErroreNeiFileCaricatiSlot();

private slots:
    void changePathsSlot();
    void changeClientiPathClicked();
    void changeMeccaniciPathClicked();
    void changeManutenzioniPathClicked();
    void accettaModificheSlot();
    void salvaDatiSuDiscoClicked();
};

#endif // HOME_H
