#include "inseriscicliente.h"

void InserisciCliente::setPresenter(Presenter *c)
{
	presenter=c;
}

void InserisciCliente::AddClientePrivatoFields(QVBoxLayout* mainLayout)
{

		//NOME
		QVBoxLayout* NomeLayout=new QVBoxLayout;
        NomeLayout->setContentsMargins(0,0,0,30);
            QLabel* FieldNome=new QLabel("Nome:");
            FieldNome->setFont(QFont(FieldNome->text(), 20, -1 , false));
            NomeLayout->addWidget(FieldNome);

			InsertNome=new QLineEdit();
            InsertNome->setMinimumHeight(40);
            InsertNome->setFont(QFont(InsertNome->text(), 15, -1, false));
            InsertNome->setMaximumWidth(680);
			InsertNome->setClearButtonEnabled(true);
            NomeLayout->addWidget(InsertNome);

		//COGNOME
        QVBoxLayout* CognomeLayout=new QVBoxLayout;
        CognomeLayout->setContentsMargins(0,0,0,30);
			QLabel* FieldCognome=new QLabel("Cognome:");
            FieldCognome->setFont(QFont(FieldCognome->text(), 20, -1 , false));
			CognomeLayout->addWidget(FieldCognome);

			InsertCognome=new QLineEdit;
            InsertCognome->setMinimumHeight(40);
            InsertCognome->setFont(QFont(InsertCognome->text(), 15, -1, false));
            InsertCognome->setMaximumWidth(680);
			InsertCognome->setClearButtonEnabled(true);
			CognomeLayout->addWidget(InsertCognome);

		//CF
		QVBoxLayout* CFLayout=new QVBoxLayout;
        CFLayout->setContentsMargins(0,0,0,30);

			QLabel* FieldCF=new QLabel("Codice fiscale:");
            FieldCF->setFont(QFont(FieldCF->text(), 20, -1 , false));
			CFLayout->addWidget(FieldCF);

			InsertCF=new LineEdit;
            InsertCF->setMinimumHeight(40);
            InsertCF->setFont(QFont(InsertCF->text(), 15, -1, false));
            InsertCF->setMaximumWidth(680);
			InsertCF->setClearButtonEnabled(true);
            InsertCF->setMaxLength(16);
            InsertCF->setInputMask(">AAAAAA99A99A999A");
			CFLayout->addWidget(InsertCF);

		//Numero TELEFONO
		QVBoxLayout* NTelefonoLayout=new QVBoxLayout;
        NTelefonoLayout->setContentsMargins(0,0,0,30);

			QLabel* NTelefonoField=new QLabel("Numero di telefono:");
            NTelefonoField->setFont(QFont(NTelefonoField->text(), 20, -1 , false));
			NTelefonoLayout->addWidget(NTelefonoField);

			InsertNTelefono=new LineEdit;
            InsertNTelefono->setMinimumHeight(40);
            InsertNTelefono->setFont(QFont(InsertNTelefono->text(), 15, -1, false));
            InsertNTelefono->setMaximumWidth(680);
            InsertNTelefono->setText("+39 ");
            InsertNTelefono->setInputMask("+99 999 999 9999");
			InsertNTelefono->setMaxLength(14);
			InsertNTelefono->setDefaultCursorPosition(4);
			InsertNTelefono->setClearButtonEnabled(true);
			NTelefonoLayout->addWidget(InsertNTelefono);

		//PRIVATO-RAPPRESENTANTE
		QVBoxLayout* TipoClienteLayout=new QVBoxLayout;
        TipoClienteLayout->setContentsMargins(0,0,0,30);

		QLabel* TipoCliente= new QLabel("Tipo cliente:");
        TipoCliente->setFont(QFont(TipoCliente->text(), 20, -1 , false));
        TipoClienteLayout->addWidget(TipoCliente, Qt::AlignHCenter, Qt::AlignHCenter);

		QHBoxLayout* PrivatoRappresentanteLayout=new QHBoxLayout;
		TipoClienteLayout->addLayout(PrivatoRappresentanteLayout);



			PrivatoButton=new QRadioButton("Privato");
            PrivatoButton->setFont(QFont(PrivatoButton->text(), 15, -1 , false));
			PrivatoButton->setChecked(true);
			PrivatoRappresentanteLayout->addWidget(PrivatoButton, Qt::AlignCenter, Qt::AlignCenter);

			RappresentanteButton=new QRadioButton("Rappresentante");
            RappresentanteButton->setFont(QFont(RappresentanteButton->text(), 15, -1 , false));
			PrivatoRappresentanteLayout->addWidget(RappresentanteButton, Qt::AlignCenter, Qt::AlignCenter);

            QGridLayout* ClientePrivatoFieldsLayout = new QGridLayout();
            ClientePrivatoFieldsLayout->addLayout(NomeLayout, 0, 0);
            ClientePrivatoFieldsLayout->addLayout(CognomeLayout, 0, 1);
            ClientePrivatoFieldsLayout->addLayout(CFLayout, 1,0, 1, 1);
            ClientePrivatoFieldsLayout->addLayout(NTelefonoLayout,2,0, 1, 1);
            ClientePrivatoFieldsLayout->addLayout(TipoClienteLayout,1,1,2,1);

            mainLayout->addLayout(ClientePrivatoFieldsLayout);

            connect(RappresentanteButton,SIGNAL(pressed()),this,SLOT(enableRappresentanteFieldsSlot()));
            connect(PrivatoButton,SIGNAL(pressed()),this,SLOT(disableRappresentanteFieldsSlot()));
}

void InserisciCliente::AddClienteRappresentanteFields(QVBoxLayout* mainLayout)
{
    QGridLayout* ClienteRappresentanteFieldsLayout= new QGridLayout();
	mainLayout->addLayout(ClienteRappresentanteFieldsLayout);

	//Nome azienda
	QVBoxLayout* NomeAziendaLayout=new QVBoxLayout;
    NomeAziendaLayout->setContentsMargins(0,0,0,30);

		QLabel* NomeAziendaField=new QLabel("Nome azienda:");
        NomeAziendaField->setFont(QFont(NomeAziendaField->text(), 20, -1 , false));
		NomeAziendaLayout->addWidget(NomeAziendaField);

		InsertNomeAzienda=new QLineEdit;
        InsertNomeAzienda->setMinimumHeight(40);
        InsertNomeAzienda->setFont(QFont(InsertNomeAzienda->text(), 15, -1, false));
        InsertNomeAzienda->setMaximumWidth(680);
		InsertNomeAzienda->setClearButtonEnabled(true);
		NomeAziendaLayout->addWidget(InsertNomeAzienda);

	//Partita IVA
	QVBoxLayout* PIVALayout=new QVBoxLayout;
    PIVALayout->setContentsMargins(0,0,0,30);

		QLabel* PIVAField=new QLabel("P. IVA:");
        PIVAField->setFont(QFont(PIVAField->text(), 20, -1 , false));
		PIVALayout->addWidget(PIVAField);

		InsertPIVA=new LineEdit;
        InsertPIVA->setMinimumHeight(40);
        InsertPIVA->setFont(QFont(InsertPIVA->text(), 15, -1, false));
        InsertPIVA->setMaximumWidth(680);
		InsertPIVA->setClearButtonEnabled(true);
        InsertPIVA->setInputMask("99999999999");
		PIVALayout->addWidget(InsertPIVA);

	//Sconto %
	QHBoxLayout* ScontoLayout=new QHBoxLayout;
    ScontoLayout->setContentsMargins(0,30,0,20);

		QLabel* ScontoField=new QLabel("Sconto %:");
        ScontoField->setFont(QFont(ScontoField->text(), 20, -1 , false));
		ScontoLayout->addWidget(ScontoField, Qt::AlignCenter, Qt::AlignCenter);

		InsertSconto=new QSpinBox();
        InsertSconto->setMinimumSize(40,40);
        InsertSconto->setFont(QFont(InsertSconto->text(), 15, -1, false));
		InsertSconto->setSingleStep(5);
		InsertSconto->setMaximum(30);
		ScontoLayout->addWidget(InsertSconto, Qt::AlignCenter, Qt::AlignCenter);


		//Rappresentante field disabilitati
		InsertNomeAzienda->setEnabled(false);
		InsertPIVA->setEnabled(false);
		InsertSconto->setEnabled(false);


    ClienteRappresentanteFieldsLayout->addLayout(NomeAziendaLayout, 0, 0);
    ClienteRappresentanteFieldsLayout->addLayout(PIVALayout, 1, 0);
    ClienteRappresentanteFieldsLayout->addLayout(ScontoLayout, 0, 1, 2, 1, Qt::AlignCenter);
}

void InserisciCliente::AddConfermaButton(QVBoxLayout* mainLayout)
{
	QPushButton* registraButton= new QPushButton("Registra");
    registraButton->setMinimumSize(500,60);
    registraButton->setFont(QFont(registraButton->text(), 15, -1, false));
    mainLayout->addWidget(registraButton, Qt::AlignHCenter, Qt::AlignHCenter);
    connect(registraButton, SIGNAL(pressed()), this, SLOT(RegistrazioneClienteSlot()));

}

void InserisciCliente::AddBackButton(QVBoxLayout* mainLayout)
{
	QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
	QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
	toolbar->setMovable(false);
	QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SLOT(WarningRegistrazioneIncompletaSlot()));
}

bool InserisciCliente::FieldsAreEmpty() const
{
	if(InsertNome->text().isEmpty() &&
		InsertCognome->text().isEmpty() &&
		InsertCF->text().isEmpty() &&
		InsertNomeAzienda->text().isEmpty() &&
		InsertPIVA->text().isEmpty())
		return true;
	else
		return false;
}

bool InserisciCliente::PrivatoFieldsAreNotEmpty() const
{
	if(!InsertNome->text().isEmpty() &&
		!InsertCognome->text().isEmpty() &&
        !InsertCF->text().isEmpty())
		return true;
	else
		return false;
}

bool InserisciCliente::RappresentanteFieldsAreNotEmpty() const
{
	if(!InsertNome->text().isEmpty() &&
		!InsertCognome->text().isEmpty() &&
		!InsertCF->text().isEmpty() &&
		!InsertNomeAzienda->text().isEmpty() &&
		!InsertPIVA->text().isEmpty())
		return true;
	else
		return false;

}


InserisciCliente::InserisciCliente(QWidget* parent): QWidget(parent)
{
	QVBoxLayout* mainLayout= new QVBoxLayout;
	mainLayout->setContentsMargins(20,8,20,8);

	AddBackButton(mainLayout);

	//CLIENTE PRIVATO FIEDLS LAYOUT
	AddClientePrivatoFields(mainLayout);


	//CLIENTE RAPPRESENTANTE FIELDS
	AddClienteRappresentanteFields(mainLayout);

	//Button Conferma
	AddConfermaButton(mainLayout);


	setLayout(mainLayout);
}

void InserisciCliente::showWarningRegistrazioneIncompleta()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setMinimumSize(250,110);
    dialog->setIcon(QMessageBox::Warning);
    dialog->setText("Cliente ancora non registrato!");
    dialog->setInformativeText("Sei sicuro di voler uscire?");
    QPushButton* SiButton=new QPushButton("Si");
    QPushButton* NoButton=new QPushButton("No");
    dialog->addButton(SiButton,QMessageBox::YesRole);
    connect(SiButton,SIGNAL(pressed()),this,SIGNAL(goToHomeSignal()));
    connect(SiButton,SIGNAL(pressed()), this, SLOT(clearFieldsSlot()));
    dialog->addButton(NoButton,QMessageBox::NoRole);


    dialog->show();
}

void InserisciCliente::showWarningInconsistenzaDati()
{
    QMessageBox* dialog = new QMessageBox(this);
    dialog->setIcon(QMessageBox::Warning);
    dialog->setText("Impossibile registrare cliente");
    dialog->setInformativeText("Nel database è gia presente una persona con codice fiscale: "+InsertCF->text());

    dialog->show();
}

void InserisciCliente::WarningRegistrazioneIncompletaSlot()
{
	if(!FieldsAreEmpty()){
        showWarningRegistrazioneIncompleta();
	}
    else{
        clearFields();
		emit goToHomeSignal();
    }
}

void InserisciCliente::showRegistrazioneCliente()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registrazione cliente effetuata");
    QPushButton* okButton=new QPushButton("OK");
    dialog->addButton(okButton,QMessageBox::AcceptRole);
    connect(okButton,SIGNAL(pressed()),this,SLOT(clearFieldsSlot()));

    dialog->show();
}

void InserisciCliente::showErroreInserimento(QString a)
{
    QMessageBox* dialog=new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registazione cliente non effettuata!");
    dialog->setInformativeText(a);

    dialog->show();
}

void InserisciCliente::RegistrazioneClienteSlot()
{
    if(PrivatoButton->isChecked())
    {
        if(PrivatoFieldsAreNotEmpty())
        {
            if(InsertCF->hasAcceptableInput())
            {
                if(InsertNTelefono->hasAcceptableInput())
                {
					if(presenter->InserisciClientePrivato(InsertNome->text(),
                                                           InsertCognome->text(),
                                                           InsertCF->text(),
                                                           InsertNTelefono->text()))
                        showRegistrazioneCliente();
                    else
                        showWarningInconsistenzaDati();
                }else
                    showErroreInserimento("Il numero di telefono deve essere esattamente di 10 cifre e con suffisso.");
            }else
                showErroreInserimento("Il codice fiscale deve essere esattamente di 16 cifre.");
        }
        else
            showErroreInserimento("Completa tutti i campi.");
    }
    else
    {
        if(RappresentanteFieldsAreNotEmpty())
        {
            if(InsertCF->hasAcceptableInput()){
                if(InsertNTelefono->hasAcceptableInput()){

                    if(InsertPIVA->hasAcceptableInput())
                    {
						if(presenter->InserisciClienteRappresentante(InsertNome->text(),
                                                                      InsertCognome->text(),
                                                                      InsertCF->text(),
                                                                      InsertNTelefono->text(),
                                                                      InsertNomeAzienda->text(),
                                                                      InsertPIVA->text(),
                                                                      InsertSconto->value()))
                            showRegistrazioneCliente();
                        else
                            showWarningInconsistenzaDati();
                    }else
                        showErroreInserimento("La Partita IVA deve essere composta da esattamente 11 cifre.");
                }else
                    showErroreInserimento("Il numero di telefono deve essere esattamente di 10 cifre e con suffisso.");
            }else
                showErroreInserimento("Il codice fiscale deve essere esattamente di 16 cifre.");
        }else
            showErroreInserimento("Completa tutti i campi.");
    }

}

void InserisciCliente::enableRappresentanteFields()
{
    InsertNomeAzienda->setEnabled(true);
    InsertPIVA->setEnabled(true);
    InsertSconto->setEnabled(true);
}

void InserisciCliente::enableRappresentanteFieldsSlot()
{
        enableRappresentanteFields();
}

void InserisciCliente::disableRappresentanteFields()
{
    InsertNomeAzienda->clear();
    InsertPIVA->clear();
    InsertSconto->setValue(0);
    InsertNomeAzienda->setEnabled(false);
    InsertPIVA->setEnabled(false);
    InsertSconto->setEnabled(false);
}

void InserisciCliente::disableRappresentanteFieldsSlot()
{
    disableRappresentanteFields();
}

void InserisciCliente::clearFields()
{
    InsertNome->clear();
    InsertCognome->clear();
    InsertCF->clear();
    InsertNTelefono->clear();
    InsertNTelefono->setText("+39 ");
    PrivatoButton->setChecked(true);
    RappresentanteButton->setChecked(false);
    InsertNomeAzienda->clear();
    InsertPIVA->clear();
    InsertSconto->setValue(0);
    disableRappresentanteFields();
}

void InserisciCliente::clearFieldsSlot()
{
    clearFields();
}
