#include "inseriscimeccanico.h"

void InserisciMeccanico::AddBackButton(QVBoxLayout *mainLayout)
{
	QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
	QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
	toolbar->setMovable(false);
	QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SLOT(WarningRegistrazioneIncompletaSlot()));
}


void InserisciMeccanico::AddFields(QVBoxLayout* mainLayout)
{
    QGridLayout* MeccanicoFieldsLayout= new QGridLayout;

		//NOME
        QVBoxLayout* NomeLayout=new QVBoxLayout;
        NomeLayout->setContentsMargins(0,0,0,15);

			QLabel* FieldNome=new QLabel("Nome:");
            FieldNome->setFont(QFont(FieldNome->text(), 20, -1, false));
			NomeLayout->addWidget(FieldNome);

			InsertNome=new QLineEdit();
            InsertNome->setMinimumHeight(40);
            InsertNome->setFont(QFont(InsertNome->text(), 15, -1, false));
			InsertNome->setClearButtonEnabled(true);
            NomeLayout->addWidget(InsertNome);

		//COGNOME
		QVBoxLayout* CognomeLayout=new QVBoxLayout;
        CognomeLayout->setContentsMargins(0,0,0,15);

            QLabel* FieldCognome=new QLabel("Cognome:");
            FieldCognome->setFont(QFont(FieldCognome->text(), 20, -1, false));
            CognomeLayout->addWidget(FieldCognome);

			InsertCognome=new QLineEdit;
            InsertCognome->setMinimumHeight(40);
            InsertCognome->setFont(QFont(InsertCognome->text(), 15, -1, false));
			InsertCognome->setClearButtonEnabled(true);
			CognomeLayout->addWidget(InsertCognome);

		//CF
		QVBoxLayout* CFLayout=new QVBoxLayout;
		CFLayout->setContentsMargins(0,0,0,15);

			QLabel* FieldCF=new QLabel("Codice fiscale:");
            FieldCF->setFont(QFont(FieldCF->text(), 20, -1, false));
			CFLayout->addWidget(FieldCF);

			InsertCF=new LineEdit;
            InsertCF->setMinimumHeight(40);
            InsertCF->setFont(QFont(InsertCF->text(), 15, -1, false));
			InsertCF->setClearButtonEnabled(true);
            InsertCF->setInputMask(">AAAAAA99A99A999A");
			CFLayout->addWidget(InsertCF);

		//Numero TELEFONO
		QVBoxLayout* NTelefonoLayout=new QVBoxLayout;
		NTelefonoLayout->setContentsMargins(0,0,0,15);

            QLabel* NTelefonoField=new QLabel("Numero di telefono:");
            NTelefonoField->setFont(QFont(NTelefonoField->text(), 20, -1, false));
			NTelefonoLayout->addWidget(NTelefonoField);

			InsertNTelefono=new LineEdit;
            InsertNTelefono->setMinimumHeight(40);
            InsertNTelefono->setFont(QFont(InsertNTelefono->text(), 15, -1, false));
            InsertNTelefono->setText("+39 ");
            InsertNTelefono->setInputMask("+99 999 999 9999");
			InsertNTelefono->setDefaultCursorPosition(4);
            InsertNTelefono->setClearButtonEnabled(true);
            NTelefonoLayout->addWidget(InsertNTelefono);

		//Stipendio
        QVBoxLayout* StipendioLayout=new QVBoxLayout;
        StipendioLayout->setSpacing(0);
        StipendioLayout->setContentsMargins(0,150,0,150);


            QLabel* StipendioField=new QLabel("Stipendio mensile: €");
            StipendioField->setFont(QFont(StipendioField->text(), 20, -1, false));
            StipendioLayout->addWidget(StipendioField,Qt::AlignHCenter, Qt::AlignHCenter);

			 InsertStipendio=new QLineEdit;
             InsertStipendio->setMinimumHeight(40);
             InsertStipendio->setFont(QFont(InsertStipendio->text(), 15, -1, false));
             QDoubleValidator* v=new QDoubleValidator(0.00,999999.99,2);
             v->setNotation(QDoubleValidator::StandardNotation);
             v->setDecimals(2);
             InsertStipendio->setValidator(v);
			 InsertStipendio->setClearButtonEnabled(true);
             //InsertStipendio->setMaximumWidth(150);
             StipendioLayout->addWidget(InsertStipendio,Qt::AlignHCenter, Qt::AlignHCenter);


    MeccanicoFieldsLayout->addLayout(NomeLayout,0,0);
    MeccanicoFieldsLayout->addLayout(CognomeLayout,0,1);
    MeccanicoFieldsLayout->addLayout(CFLayout,1,0);
    MeccanicoFieldsLayout->addLayout(NTelefonoLayout,2,0);
    MeccanicoFieldsLayout->addLayout(StipendioLayout,1,1,2,1, Qt::AlignHCenter);
    MeccanicoFieldsLayout->setContentsMargins(10,10,10,10);
    mainLayout->addLayout(MeccanicoFieldsLayout);
}

void InserisciMeccanico::AddRegistraButton(QVBoxLayout* mainLayout)
{
	QHBoxLayout* buttonLayout= new QHBoxLayout;
	buttonLayout->setContentsMargins(10,10,10,10);
	mainLayout->addLayout(buttonLayout);
	QPushButton* registraButton= new QPushButton("Registra");
    registraButton->setMinimumSize(500,60);
    registraButton->setFont(QFont(registraButton->text(), 15, -1, false));
    connect(registraButton, SIGNAL(pressed()), this, SLOT(RegistrazioneMeccanicoSlot()));
    buttonLayout->addWidget(registraButton, Qt::AlignHCenter, Qt::AlignHCenter);
}


bool InserisciMeccanico::FieldsAreEmpty() const
{
	if(InsertNome->text().isEmpty() &&
			InsertCognome->text().isEmpty() &&
			InsertCF->text().isEmpty() &&
			InsertStipendio->text().isEmpty())
		return true;
	else
		return false;
}

bool InserisciMeccanico::FieldsAreNotEmpty() const
{
	if(!InsertNome->text().isEmpty() &&
			!InsertCognome->text().isEmpty() &&
			!InsertCF->text().isEmpty() &&
			!InsertStipendio->text().isEmpty())
		return true;
	else
		return false;
}



InserisciMeccanico::InserisciMeccanico(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* mainLayout = new QVBoxLayout;

	AddBackButton(mainLayout);

	AddFields(mainLayout);

	AddRegistraButton(mainLayout);

    setLayout(mainLayout);
}

void InserisciMeccanico::setPresenter(Presenter *c)
{
	presenter=c;
}

void InserisciMeccanico::showWarningRegistrazioneIncompleta()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setMinimumSize(250,110);
    dialog->setIcon(QMessageBox::Warning);
    dialog->setText("Meccanico ancora non registrato!");
    dialog->setInformativeText("Sei sicuro di voler uscire?");
    QPushButton* SiButton=new QPushButton("Si");
    QPushButton* NoButton=new QPushButton("No");
    dialog->addButton(SiButton,QMessageBox::YesRole);
    connect(SiButton,SIGNAL(pressed()),this,SIGNAL(goToHomeSignal()));
    connect(SiButton, SIGNAL(pressed()), this, SLOT(clearFieldsSlot()));
    dialog->addButton(NoButton,QMessageBox::NoRole);


    dialog->show();
}

void InserisciMeccanico::WarningRegistrazioneIncompletaSlot()
{
	if(!FieldsAreEmpty()){
        showWarningRegistrazioneIncompleta();
	}
	else
		emit goToHomeSignal();
}

void InserisciMeccanico::showErroreInserimento(QString text)
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registrazione meccanico non effettuata!");
    dialog->setInformativeText(text);

    dialog->show();
}

void InserisciMeccanico::showRegistrazioneEffettuata()
{
    QMessageBox* dialog= new QMessageBox(this);
    dialog->setIcon(QMessageBox::Information);
    dialog->setText("Registrazione meccanico effetuata");
    QPushButton* okButton=new QPushButton("OK");
    dialog->addButton(okButton,QMessageBox::AcceptRole);
    connect(okButton,SIGNAL(pressed()),this,SLOT(clearFieldsSlot()));

    dialog->show();
}

void InserisciMeccanico::showWarningInconsistenzaDati()
{
    QMessageBox* dialog = new QMessageBox(this);
    dialog->setIcon(QMessageBox::Warning);
    dialog->setText("Impossibile registrare meccanico");
    dialog->setInformativeText("Nel database è gia presente una persona con codice fiscale: "+InsertCF->text());

    dialog->show();
}

void InserisciMeccanico::RegistrazioneMeccanicoSlot()
{
    if(FieldsAreNotEmpty()){
        if(InsertCF->hasAcceptableInput()){
            if(InsertNTelefono->hasAcceptableInput()){
                if(!InsertStipendio->hasAcceptableInput()){
                    showErroreInserimento("Errore nell'inserimento del campo stipendio \n esempio testo accettabile: 12000,00");
                }
                else{
					QLocale italian(QLocale::Italian);
					double stipendio=italian.toDouble(InsertStipendio->text().replace(".",","));
					if(presenter->InserisciMeccanico(InsertNome->text(),
                                                      InsertCognome->text(),
                                                      InsertCF->text(),
                                                      InsertNTelefono->text(),
                                                      stipendio))showRegistrazioneEffettuata();
                    else showWarningInconsistenzaDati();

                }
            }else showErroreInserimento("Il numero di telefono deve essere esattamente di 10 cifre e con suffisso.");
        }else showErroreInserimento("Il codice fiscale deve essere esattamente di 16 cifre.");
    }
    else
        showErroreInserimento("Completa tutti i campi del form.");

}

void InserisciMeccanico::clearFields()
{
    InsertNome->clear();
    InsertCognome->clear();
    InsertCF->clear();
    InsertNTelefono->clear();
    InsertNTelefono->setText("+39 ");
    InsertStipendio->clear();
}

void InserisciMeccanico::clearFieldsSlot()
{
    clearFields();
}


