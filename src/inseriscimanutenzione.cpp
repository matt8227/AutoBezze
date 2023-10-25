#include "inseriscimanutenzione.h"

void InserisciManutenzione::addFields(QVBoxLayout* mainLayout)
{

    QGridLayout* fieldLayout= new QGridLayout();
    fieldLayout->setVerticalSpacing(30);


    QLabel* MeccanicoLabel=new QLabel("Meccanico: ");
    MeccanicoLabel->setFont(QFont(MeccanicoLabel->text(), 20, -1, false));
    MeccanicoCombo= new QComboBox();
    MeccanicoCombo->setMinimumHeight(40);
    MeccanicoCombo->setFont(QFont(MeccanicoCombo->currentText(), 15, -1, false));
    MeccanicoCombo->setMinimumWidth(600);
    QLabel* ClienteLabel= new QLabel("Cliente: ");
    ClienteLabel->setFont(QFont(ClienteLabel->text(), 20, -1, false));
    ClienteCombo=new QComboBox();
    ClienteCombo->setMinimumHeight(40);
    ClienteCombo->setMinimumWidth(600);
    ClienteCombo->setFont(QFont(ClienteCombo->currentText(), 15, -1, false));

    QLabel* TargaLabel=new QLabel("Targa macchina: ");
    TargaLabel->setFont(QFont(TargaLabel->text(), 20, -1, false));
	targa=new LineEdit();
    targa->setMinimumHeight(40);
    targa->setFont(QFont(targa->text(), 15, -1, false));
    targa->setMinimumWidth(200);
    targa->setMaximumWidth(200);
    targa->setInputMask(">AA999AA");
    targa->setClearButtonEnabled(true);
    QLabel* costoLabel=new QLabel("Costo manutenzione:  €");
    costoLabel->setFont(QFont(costoLabel->text(), 20, -1, false));
    costo= new QLineEdit();
    costo->setMinimumHeight(40);
    costo->setFont(QFont(costo->text(), 15, -1, false));

    QDoubleValidator* v=new QDoubleValidator(0.00,999999.99,2);
    v->setNotation(QDoubleValidator::StandardNotation);
    v->setDecimals(2);
    costo->setValidator(v);
    costo->setClearButtonEnabled(true);
    costo->setMinimumWidth(200);
    costo->setMaximumWidth(200);
    costo->setClearButtonEnabled(true);

    QLabel* dataLabel=new QLabel("Data: ");
    dataLabel->setFont(QFont(dataLabel->text(), 20, -1, false));
    data=new QDateEdit();
    data->setMinimumHeight(40);
    data->setFont(QFont(data->text(), 15, -1, false));
    data->setMinimumWidth(200);
    data->setMaximumWidth(200);

    QLabel* DescrizioneLabel= new QLabel("Descrizione del lavoro effettuato: ");
    DescrizioneLabel->setFont(QFont(DescrizioneLabel->text(), 20, -1, false));
    descrizione=new QTextEdit();
    descrizione->setMinimumWidth(1200);
    descrizione->setMinimumHeight(200);
	descrizione->setFont(QFont(descrizione->toPlainText(), 20, -1, false));


    fieldLayout->addWidget(ClienteLabel,0,0, Qt::AlignLeft);
    fieldLayout->addWidget(ClienteCombo,0,1, Qt::AlignLeft);
    fieldLayout->addWidget(MeccanicoLabel,1,0, Qt::AlignLeft);
    fieldLayout->addWidget(MeccanicoCombo,1,1, Qt::AlignLeft);
    fieldLayout->addWidget(TargaLabel,2,0, Qt::AlignLeft);
    fieldLayout->addWidget(targa,2,1, Qt::AlignLeft);
    fieldLayout->addWidget(costoLabel,3,0, Qt::AlignLeft);
    fieldLayout->addWidget(costo, 3,1, Qt::AlignLeft);
    fieldLayout->addWidget(dataLabel,4,0, Qt::AlignLeft);
    fieldLayout->addWidget(data,4,1, Qt::AlignLeft);
    fieldLayout->setHorizontalSpacing(0);
    fieldLayout->setColumnStretch(1,2);
    mainLayout->addLayout(fieldLayout);
    fieldLayout->addWidget(DescrizioneLabel,5,0,1,2, Qt::AlignHCenter);
    fieldLayout->addWidget(descrizione,6,0,1,2, Qt::AlignHCenter);

}

void InserisciManutenzione::addConfermaButton(QVBoxLayout* mainLayout)
{
    QPushButton* confermaButton=new QPushButton("Registra");
    confermaButton->setMinimumSize(500,60);
    confermaButton->setFont(QFont(confermaButton->text(), 15, -1, false));
    mainLayout->addWidget(confermaButton, Qt::AlignHCenter, Qt::AlignHCenter);
    connect(confermaButton, SIGNAL(pressed()), this, SLOT(RegistrazioneManutenzioneSlot()));
}

bool InserisciManutenzione::FieldsAreNotEmpty() const
{
    if(!targa->text().isEmpty() &&
            !costo->text().isEmpty() &&
            !descrizione->toPlainText().isEmpty() &&
			presenter->getClienti().getSize()>0 &&
			presenter->getMeccanici().getSize()>0)
        return true;
    else
        return false;
}

bool InserisciManutenzione::FieldsAreEmpty() const
{
	if(presenter->getClienti().getSize()>0 && ClienteCombo->currentText() != ClienteCombo->itemText(0))
        return false;
	if(presenter->getMeccanici().getSize()>0 && MeccanicoCombo->currentText() != MeccanicoCombo->itemText(0))
        return false;
    if(targa->text().isEmpty() &&
            costo->text().isEmpty() &&
            data->date()==QDate::currentDate() &&
            descrizione->toPlainText().isEmpty())
        return true;
    else
        return false;
}

void InserisciManutenzione::showRegistrazioneIncompleta()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setMinimumSize(280,110);
    dialog->setIcon(QMessageBox::Warning);
    dialog->setText("Manutenzione ancora non registrata!");
    dialog->setInformativeText("Sei sicuro di voler uscire?");
    QPushButton* SiButton=new QPushButton("Si");
    QPushButton* NoButton=new QPushButton("No");
    dialog->addButton(SiButton,QMessageBox::YesRole);
    connect(SiButton,SIGNAL(pressed()),this,SIGNAL(goToHomeSignal()));
    connect(SiButton,SIGNAL(pressed()), this, SLOT(clearFieldsSlot()));
    dialog->addButton(NoButton,QMessageBox::NoRole);


    dialog->show();
}

void InserisciManutenzione::showRegistrazioneManutenzione()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registrazione manutenzione effetuata");
    QPushButton* okButton=new QPushButton("OK");
    dialog->addButton(okButton,QMessageBox::AcceptRole);
    connect(okButton,SIGNAL(pressed()),this,SLOT(clearFieldsSlot()));

    dialog->show();
}

void InserisciManutenzione::clearFields()
{
    costo->clear();
    descrizione->clear();
    targa->clear();
    ClienteCombo->setCurrentIndex(0);
    MeccanicoCombo->setCurrentIndex(0);
    data->setDate(QDate::currentDate());
}

void InserisciManutenzione::showErroreInserimento(QString text)
{
    QMessageBox* dialog=new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registazione della manutenzione non effettuata!");
    dialog->setInformativeText(text);

    dialog->show();
}

void InserisciManutenzione::aggiornaCombo()
{
    ClienteCombo->clear();
    MeccanicoCombo->clear();
	for(auto i= presenter->getClienti().begin(); i!=presenter->getClienti().end(); i++)
    {
        QString CF=QString::fromStdString((*i)->getCF());
        QString nome=QString::fromStdString((*i)->getNome());
        QString cognome=QString::fromStdString((*i)->getCognome());
        ClienteCombo->addItem(CF+ " | " + nome + " " + cognome);
    }

	for(auto i= presenter->getMeccanici().begin(); i!=presenter->getMeccanici().end(); i++)
    {
        QString CF=QString::fromStdString((*i)->getCF());
        QString nome=QString::fromStdString((*i)->getNome());
        QString cognome=QString::fromStdString((*i)->getCognome());
        MeccanicoCombo->addItem(CF+ " | " + nome + " " + cognome);
    }
}

InserisciManutenzione::InserisciManutenzione(QWidget *parent):QWidget(parent)
{

    QVBoxLayout* mainLayout=new QVBoxLayout;
    mainLayout->setContentsMargins(10,20,10,20);
    addBackButton(mainLayout);

    addFields(mainLayout);

    addConfermaButton(mainLayout);

    setLayout(mainLayout);
}

void InserisciManutenzione::setPresenter(Presenter *c)
{
	presenter=c;
}

void InserisciManutenzione::aggiornaPaginaSlot()
{
    aggiornaCombo();
    data->setDate(QDate::currentDate());
}

void InserisciManutenzione::clearFieldsSlot()
{
    clearFields();
}

void InserisciManutenzione::WarningRegistrazioneIncompletaSlot()
{
    if(!FieldsAreEmpty())
        showRegistrazioneIncompleta();
    else
        emit goToHomeSignal();
}

void InserisciManutenzione::showManutenzioneScontata(u_int sconto, double costom)
{
    QMessageBox* dialog=new QMessageBox();
    dialog->setMinimumSize(260,130);
    dialog->setText("Registazione manutenzione effettuata.");
    costom=costom-costom*(double(sconto)/100);
    dialog->setInformativeText("Il cliente ha uno sconto del "+QString::number(sconto) +" %\n"
                               "Nuovo costo della manutenzione: "+QString::number(costom,'f',2)+" €");
    QPushButton* okButton=new QPushButton("OK");
    dialog->addButton(okButton,QMessageBox::AcceptRole);
    connect(okButton,SIGNAL(pressed()),this,SLOT(clearFieldsSlot()));

    dialog->show();
}

void InserisciManutenzione::RegistrazioneManutenzioneSlot()
{
    if(!FieldsAreNotEmpty()) showErroreInserimento("Completa tutti i campi del form.");
    else
    {
        if(!targa->hasAcceptableInput()) showErroreInserimento("La targa deve avere esattamente 7 simboli.");
        else
        {

            if(!costo->hasAcceptableInput()) showErroreInserimento("Errore nell'inserimento del campo 'costo' \n esempio testo accettabile: 12000,00");
            else
            {
				QLocale italian(QLocale::Italian);
				double costom=italian.toDouble(costo->text().replace(".",","));
				u_int sconto=presenter->InserisciManutenzione(ClienteCombo->currentText(),
                                                               MeccanicoCombo->currentText(),
                                                               targa->text(),
                                                               costom,
                                                               data->date(),
                                                               descrizione->toPlainText());
                if(sconto>0)
                    showManutenzioneScontata(sconto, costom);
                else
                    showRegistrazioneManutenzione();
            }
        }
    }
}

void InserisciManutenzione::addBackButton(QVBoxLayout *mainLayout)
{
    QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
    QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
    toolbar->setMovable(false);
    QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SLOT(WarningRegistrazioneIncompletaSlot()));
}
