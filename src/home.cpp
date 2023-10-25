#include "home.h"

void home::AddButtons(QVBoxLayout* layout)
{

    QPushButton * nuovoClienteButton = new QPushButton("Inserisci un nuovo cliente");
    nuovoClienteButton->setFont(QFont(nuovoClienteButton->text(), 15, -1 , true));
	QPushButton * mostraClientiButton = new QPushButton("Mostra clienti");
    mostraClientiButton->setFont(QFont(mostraClientiButton->text(), 15, -1 , true));

	QPushButton * nuovaManutenzioneButton = new QPushButton("Inserisci nuova manutenzione");
    nuovaManutenzioneButton->setFont(QFont(nuovaManutenzioneButton->text(), 15, -1 , true));

    QPushButton * mostraManutenzioniButton = new QPushButton("Mostra manutenzioni");
    mostraManutenzioniButton->setFont(QFont(mostraManutenzioniButton->text(), 15, -1 , true));

	QPushButton * nuovoMeccanicoButton = new QPushButton("Inserisci un nuovo meccanico");
    nuovoMeccanicoButton->setFont(QFont(nuovoMeccanicoButton->text(), 15, -1 , true));
	QPushButton * mostraMeccaniciButton = new QPushButton("Mostra meccanici");
    mostraMeccaniciButton->setFont(QFont(mostraMeccaniciButton->text(), 15, -1 , true));

    nuovoClienteButton->setMinimumSize(250,100);
    mostraClientiButton->setMinimumSize(250,100);
    nuovaManutenzioneButton->setMinimumSize(250,100);
    mostraManutenzioniButton->setMinimumSize(250,100);
    nuovoMeccanicoButton->setMinimumSize(250,100);
    mostraMeccaniciButton->setMinimumSize(250,100);

    QGridLayout* buttonsLayout=new QGridLayout();
    QLabel * titolo = new QLabel("AutoBezze");
    QFont font = titolo->font();
    font.setPointSize(80);
    font.setBold(true);
    titolo->setFont(font);

    buttonsLayout->addWidget(titolo,0,0,1,2, Qt::AlignHCenter);
    buttonsLayout->setHorizontalSpacing(40);
    buttonsLayout->setVerticalSpacing(50);
    buttonsLayout->addWidget(nuovoClienteButton,1,0);
    buttonsLayout->addWidget(mostraClientiButton,1,1);
    buttonsLayout->addWidget(nuovoMeccanicoButton,2,0);
    buttonsLayout->addWidget(mostraMeccaniciButton,2,1);
    buttonsLayout->addWidget(nuovaManutenzioneButton,3,0);
    buttonsLayout->addWidget(mostraManutenzioniButton,3,1);

    layout->addLayout(buttonsLayout);

    connect(nuovoClienteButton, SIGNAL (clicked()), this, SIGNAL (InserisciClienteButtonSignal()));
	connect(nuovoMeccanicoButton, SIGNAL(clicked()), this, SIGNAL (InserisciMeccanicoButtonSignal()));
    connect(nuovaManutenzioneButton,SIGNAL(clicked()), this, SIGNAL(InserisciManutenzioneButtonSignal()));
    connect(mostraClientiButton, SIGNAL(clicked()), this, SIGNAL(MostraClientiButtonSignal()));
    connect(mostraMeccaniciButton, SIGNAL(clicked()), this, SIGNAL(MostraMeccaniciButtonSignal()));
    connect(mostraManutenzioniButton, SIGNAL(clicked()), this, SIGNAL(MostraManutenzioniButtonSignal()));


}

void home::AddOptionsBar(QVBoxLayout* mainlayout)
{
    QMenuBar* menuBar=new QMenuBar(this);
    QMenu* impostazioni= new QMenu("Impostazioni", menuBar);
    menuBar->addMenu(impostazioni);
    impostazioni->addAction(new QAction("Carica dati da disco", impostazioni));
    connect(impostazioni->actions()[0], SIGNAL(triggered()), this, SLOT(changePathsSlot()));
    impostazioni->addAction(new QAction("Salva dati su disco", impostazioni));
    connect(impostazioni->actions()[1], SIGNAL(triggered()), this, SLOT(salvaDatiSuDiscoClicked()));
    impostazioni->addAction(new QAction("Chiudi applicazione", impostazioni));
    connect(impostazioni->actions()[2],SIGNAL(triggered()),parent(),SLOT(close()));


    mainlayout->setMenuBar(menuBar);
}

void home::aggiornaPaths()
{
	ClienteP->setText(presenter->AggiornaPathClienti());
	MeccanicoP->setText(presenter->AggiornaPathMeccanici());
	ManutenzioneP->setText(presenter->AggiornaPathManutenzioni());
}

void home::showDatiSalvati()
{
    QMessageBox* dialog = new QMessageBox();
    dialog->setText("Dati salvati su disco con successo");
    dialog->setIcon(QMessageBox::Information);

    dialog->show();
}


void home::showChangePaths()
{
    QDialog* dialog= new QDialog(this);
    dialog->setWindowTitle("File in cui si salvano/caricano i dati");
    dialog->setWhatsThis("Da qui puoi cambiare i file in cui salvi/carichi i dati");
    dialog->setMinimumSize(300,180);
    QVBoxLayout* mainLayout= new QVBoxLayout;
    QGridLayout* changePathsLayout= new QGridLayout;
    mainLayout->addLayout(changePathsLayout);
        QLabel* ClientiLabel=new QLabel("File Clienti: ");
        QLabel* MeccaniciLabel=new QLabel("File meccanici: ");
        QLabel* ManutenzioniLabel=new QLabel("File manutenzioni: ");
        ClienteP=new QLineEdit;
        ClienteP->setReadOnly(true);
        MeccanicoP=new QLineEdit;
        MeccanicoP->setReadOnly(true);
        ManutenzioneP=new QLineEdit;
        ManutenzioneP->setReadOnly(true);
        QPushButton* CambiaPathClientiButton=new QPushButton("Cambia");
        QPushButton* CambiaPathMeccaniciButton=new QPushButton("Cambia");
        QPushButton* CambiaPathManutenzioniButton=new QPushButton("Cambia");

    changePathsLayout->addWidget(ClientiLabel, 0,0);
    changePathsLayout->addWidget(ClienteP, 0,1);
    changePathsLayout->addWidget(CambiaPathClientiButton,0,2);
    changePathsLayout->addWidget(MeccaniciLabel,1,0);
    changePathsLayout->addWidget(MeccanicoP,1,1);
    changePathsLayout->addWidget(CambiaPathMeccaniciButton,1,2);
    changePathsLayout->addWidget(ManutenzioniLabel,2,0);
    changePathsLayout->addWidget(ManutenzioneP, 2,1);
    changePathsLayout->addWidget(CambiaPathManutenzioniButton,2,2);
    aggiornaPaths();

    vPathClienti=ClienteP->text();
    vPathMeccanici=MeccanicoP->text();
    vPathManutenzioni=ManutenzioneP->text();

    QHBoxLayout* ButtonLayout=new QHBoxLayout;
    ButtonLayout->setContentsMargins(20,10,10,5);
    QPushButton* accettaButton=new QPushButton("Conferma");
    QPushButton* cancellaButton=new QPushButton("Annulla");
    connect(cancellaButton, SIGNAL(pressed()),dialog, SLOT(reject()));
    connect(accettaButton, SIGNAL(pressed()), this, SLOT(accettaModificheSlot()));
    connect(accettaButton, SIGNAL(pressed()), dialog, SLOT(close()));

    ButtonLayout->addWidget(accettaButton);
    ButtonLayout->addWidget(cancellaButton);
    mainLayout->addLayout(ButtonLayout);

    connect(CambiaPathClientiButton, SIGNAL(pressed()), this, SLOT(changeClientiPathClicked()));
    connect(CambiaPathMeccaniciButton, SIGNAL(pressed()), this, SLOT(changeMeccaniciPathClicked()));
    connect(CambiaPathManutenzioniButton, SIGNAL(pressed()), this, SLOT(changeManutenzioniPathClicked()));


    dialog->setLayout(mainLayout);

    dialog->show();
}

QString home::showChoosePath()
{
    QString fileName=QFileDialog::getOpenFileName(
                this, tr("Apri il file"),"/home", tr("File json (*.json)"));

    if(fileName=="")
            throw std::runtime_error("Nessun file scelto: aggiunta annullata");

    return fileName;
}

void home::aggiornaPath(QLineEdit *line, QString text)
{
    line->setText(text);
}

void home::showErrorePath(QString errore)
{
    QMessageBox* dialog= new QMessageBox;
    dialog->setText("Non puoi selezionare questo file.");
    dialog->setInformativeText(errore);
    dialog->setIcon(QMessageBox::Warning);

    dialog->show();
}

home::home(QWidget *parent, Presenter* c):QWidget(parent), presenter(c){

    QVBoxLayout * mainlayout= new QVBoxLayout();
    mainlayout->setContentsMargins(20,0,20,60);

    AddOptionsBar(mainlayout);

    AddButtons(mainlayout);

    setLayout(mainlayout);

    setMinimumSize(1400,800);

}

void home::setPresenter(Presenter *c)
{
	presenter=c;
}

void home::showErroreNeiFileCaricati()
{
	QString Ecliente=presenter->controllaPath(presenter->AggiornaPathClienti());
	QString Emeccanico=presenter->controllaPath(presenter->AggiornaPathMeccanici());
	QString Emanutenzione=presenter->controllaPath(presenter->AggiornaPathManutenzioni());
    QMessageBox* dialog= new QMessageBox;
    dialog->setText("Errore nel caricamento o salvataggio dei seguenti file:");

    dialog->setIcon(QMessageBox::Critical);
    QString text="";
    if(Ecliente.size()>0)
        text=text+"•"+Ecliente+"\n";
    if(Emeccanico.size()>0)
        text=text+"•"+Emeccanico+"\n";
    if(Emanutenzione.size()>0)
        text=text+"•"+Emanutenzione+"\n";
    text=text+"\n Scegli altri file o modifica i file elencati per accedere alle funzionalità di I/O";
    dialog->setInformativeText(text);
    dialog->show();
}

void home::ErroreNeiFileCaricatiSlot()
{
    showErroreNeiFileCaricati();
}

void home::changePathsSlot()
{
    showChangePaths();
}

void home::showErrorMessage(const char* e)
{
    QMessageBox* error=new QMessageBox;
    error->setText(e);
    error->setIcon(QMessageBox::Warning);
    error->show();
}

void home::changeClientiPathClicked()
{
    QString text;
    bool ok=true;
    try {
         text=showChoosePath();
	}  catch (const std::runtime_error &e) {
        ok=false;
        showErrorMessage(e.what());
    }
    if(ok){
		QString errore= presenter->controllaPath(text);
        if(errore.size()==0)
            aggiornaPath(ClienteP, text);
        else
            showErrorePath(errore);
    }


}

void home::changeMeccaniciPathClicked()
{
    QString text;
    bool ok=true;
    try {
         text=showChoosePath();
	}  catch (const std::runtime_error &e) {
        ok=false;
        showErrorMessage(e.what());
    }
    if(ok){
		 QString errore= presenter->controllaPath(text);
         if(errore.size()==0)
            aggiornaPath(MeccanicoP, text);
         else
             showErrorePath(errore);
    }
}

void home::changeManutenzioniPathClicked()
{
    QString text;
    bool ok=true;
    try {
         text=showChoosePath();
	}  catch (const std::runtime_error &e) {
        ok=false;
        showErrorMessage(e.what());
    }
    if(ok){
		 QString errore= presenter->controllaPath(text);
         if(errore.size()==0)
            aggiornaPath(ManutenzioneP, text);
         else
            showErrorePath(errore);
    }


}

void home::accettaModificheSlot()
{
	presenter->ModificaPaths(ClienteP->text(), MeccanicoP->text(), ManutenzioneP->text()); //ha le path nuove
	if(vPathClienti != presenter->AggiornaPathClienti())
    {
		vPathClienti=presenter->AggiornaPathClienti();
		presenter->caricaClientiDaDisco();
    }
	if(vPathMeccanici != presenter->AggiornaPathMeccanici())
    {
		vPathMeccanici = presenter->AggiornaPathManutenzioni();
		presenter->caricaMeccaniciDaDisco();
    }
	if(vPathManutenzioni != presenter->AggiornaPathManutenzioni())
    {
		vPathManutenzioni = presenter->AggiornaPathManutenzioni();
		presenter->caricaManutenzioniDaDisco();
    }
}

void home::salvaDatiSuDiscoClicked()
{
	QString Ecliente=presenter->controllaPath(presenter->AggiornaPathClienti());
	QString Emeccanico=presenter->controllaPath(presenter->AggiornaPathMeccanici());
	QString Emanutenzione=presenter->controllaPath(presenter->AggiornaPathManutenzioni());
    if(Ecliente.size()>0 || Emeccanico.size()>0 || Emanutenzione.size()>0)
        showErroreNeiFileCaricati();
    else
    {
        showDatiSalvati();
		presenter->salvaSuDisco();
    }
}


