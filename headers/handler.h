#ifndef HANDLER_H
#define HANDLER_H

#include <QLayout>
#include <QStackedWidget>

class home;
class InserisciCliente;
class InserisciMeccanico;
class InserisciManutenzione;
class MostraClienti;
class MostraMeccanici;
class MostraManutenzioni;
class Presenter;
class Handler;

#include "home.h"
#include "inseriscicliente.h"
#include "inseriscimeccanico.h"
#include "inseriscimanutenzione.h"
#include "mostraclienti.h"
#include "mostrameccanici.h"
#include "mostramanutenzioni.h"
#include "presenter.h"


class Handler : public QWidget
{
	Q_OBJECT
private:
	Presenter* presenter;

	QStackedWidget *stackW;
    home * Home;
    InserisciCliente* inseriscicliente;
    InserisciMeccanico* inseriscimeccanico;
    InserisciManutenzione* inseriscimanutenzione;
    MostraClienti* mostraclienti;
    MostraMeccanici* mostrameccanici;
    MostraManutenzioni* mostramanutenzioni;
    void closeEvent(QCloseEvent* bar);


public:
    explicit Handler(QWidget *parent = nullptr);
	void setPresenter(Presenter* c);



	~Handler();
private slots:
    void HomeSlot() const;
    void InserisciClienteSlot() const;
    void InserisciMeccanicoSlot() const;
    void InserisciManutenzioneSlot() const;
    void MostraClientiSlot() const;
    void MostraMeccaniciSlot() const;
    void MostraManutenzioniSlot() const;
signals:
	void presenterSignal() const;

};

#endif // HANDLER_H
