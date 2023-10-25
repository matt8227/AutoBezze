#include "handler.h"

void Handler::HomeSlot() const{stackW->setCurrentIndex(0);}
void Handler::InserisciClienteSlot() const{stackW->setCurrentIndex(1);}
void Handler::InserisciMeccanicoSlot() const{stackW->setCurrentIndex(2);}
void Handler::InserisciManutenzioneSlot() const{stackW->setCurrentIndex(3);}
void Handler::MostraClientiSlot() const{stackW->setCurrentIndex(4);}
void Handler::MostraMeccaniciSlot() const{stackW->setCurrentIndex(5);}
void Handler::MostraManutenzioniSlot() const{stackW->setCurrentIndex(6);}




void Handler::closeEvent(QCloseEvent *bar)
{
	QString Ecliente=presenter->controllaPath(presenter->AggiornaPathClienti());
	QString Emeccanico=presenter->controllaPath(presenter->AggiornaPathMeccanici());
	QString Emanutenzione=presenter->controllaPath(presenter->AggiornaPathManutenzioni());
    if(Ecliente.size()>0 || Emeccanico.size()>0 || Emanutenzione.size()>0)
    {
        QString text="Errore nel salvataggio dei seguenti file:";
        if(Ecliente.size()>0)
            text=text+"\n•"+Ecliente+"\n";
        if(Emeccanico.size()>0)
            text=text+"\n•"+Emeccanico+"\n";
        if(Emanutenzione.size()>0)
            text=text+"\n•"+Emanutenzione+"\n";
        text=text+"\n Nessuna modifica effettuata verrà salvata, vuoi uscire comunque?";
        QMessageBox::StandardButton risp = QMessageBox::critical(this,
                                                                 "Errore nel salvataggio su file", text,
                                                                 QMessageBox::Yes | QMessageBox::No);
        if(risp == QMessageBox::Yes)
            bar->accept();
        else
            bar->ignore();
    }
    else
    {
		presenter->salvaSuDisco();
        bar->accept();
    }
}


Handler::Handler(QWidget *parent): QWidget(parent), stackW(new QStackedWidget())
{
	QVBoxLayout * mainLayout = new QVBoxLayout();
    setWindowTitle("AutoBezze");
	mainLayout ->setMargin(0);
	mainLayout->setSpacing(0);

    Home = new home(this);
    inseriscicliente = new InserisciCliente(this);
    inseriscimeccanico= new InserisciMeccanico(this);
    inseriscimanutenzione= new InserisciManutenzione(this);
    mostraclienti= new MostraClienti(this);
    mostrameccanici= new MostraMeccanici(this);
    mostramanutenzioni= new MostraManutenzioni(this);

	stackW->addWidget(Home);
	stackW->addWidget(inseriscicliente);
	stackW->addWidget(inseriscimeccanico);
    stackW->addWidget(inseriscimanutenzione);
    stackW->addWidget(mostraclienti);
    stackW->addWidget(mostrameccanici);
    stackW->addWidget(mostramanutenzioni);

	//connect home to .....
    connect(Home, SIGNAL(InserisciClienteButtonSignal()), this, SLOT(InserisciClienteSlot()));
	connect(Home, SIGNAL(InserisciMeccanicoButtonSignal()),this, SLOT(InserisciMeccanicoSlot()));

    connect(Home, SIGNAL(InserisciManutenzioneButtonSignal()), this, SLOT(InserisciManutenzioneSlot()));
    connect(Home, SIGNAL(InserisciManutenzioneButtonSignal()), inseriscimanutenzione, SLOT(aggiornaPaginaSlot()));

    connect(Home, SIGNAL(MostraClientiButtonSignal()), this, SLOT(MostraClientiSlot()));
    connect(Home, SIGNAL(MostraClientiButtonSignal()), mostraclienti, SLOT(aggiornaTableSlot()));

    connect(Home, SIGNAL(MostraMeccaniciButtonSignal()), this, SLOT(MostraMeccaniciSlot()));
    connect(Home, SIGNAL(MostraMeccaniciButtonSignal()), mostrameccanici, SLOT(aggiornaTableSlot()));

    connect(Home, SIGNAL(MostraManutenzioniButtonSignal()), this, SLOT(MostraManutenzioniSlot()));
    connect(Home, SIGNAL(MostraManutenzioniButtonSignal()), mostramanutenzioni, SLOT(aggiornaTableSlot()));

	//connect presenter to view
	connect(this, SIGNAL(presenterSignal()), Home, SLOT(ErroreNeiFileCaricatiSlot()));

	//connect inseriscicliente to home
	connect(inseriscicliente, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));

    //connect inserisci meccanico to home
    connect(inseriscimeccanico, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));

    //connect inserisci manutenzione to home
    connect(inseriscimanutenzione, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));

    //connect mostra clienti to home
    connect(mostraclienti, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));

    //connect mostra meccanici to home
    connect(mostrameccanici, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));

    //connect mostra manutenzioni to home
    connect(mostramanutenzioni, SIGNAL(goToHomeSignal()), this, SLOT(HomeSlot()));
	mainLayout->addWidget(stackW);
    setLayout(mainLayout);


}

void Handler::setPresenter(Presenter *c)
{
	presenter=c;
	Home->setPresenter(c);
	inseriscicliente->setPresenter(c);
	inseriscimeccanico->setPresenter(c);
	inseriscimanutenzione->setPresenter(c);
	mostraclienti->setPresenter(c);
	mostrameccanici->setPresenter(c);
	mostramanutenzioni->setPresenter(c);
}

Handler::~Handler()
{
	delete stackW;
}

