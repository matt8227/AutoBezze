#include "mostraclienti.h"

void MostraClienti::AddBackButton(QVBoxLayout* mainLayout)
{
    QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
    QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
    toolbar->setMovable(false);
    QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SIGNAL(goToHomeSignal()));
}

void MostraClienti::aggiornaTable()
{
	u_int rows=presenter->getClienti().getSize();
    table->setRowCount(rows);

    u_int r=rows-1;
    QTableWidgetItem* item;

	for(auto i= presenter->getClienti().begin(); i!=presenter->getClienti().end(); i++,r--)
    {

        vett<std::string> dati=(*i)->getVettoreDati();
        std::string nome=dati[0];
        std::string cognome=dati[1];
        std::string CF=dati[2];
        std::string NTelefono=dati[3];
        std::string ContribuzioneGuadagno=dati[4];
        std::string ProbabilitaRitenzioneAnno=dati[5];
        std::string NomeAzienda="NULL";
        std::string PIVA="NULL";
        std::string sconto="NULL";
        if(dati.getSize()>6){
            NomeAzienda=dati[6];
            PIVA=dati[7];
            sconto=dati[8]+" %";
        }
        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(nome));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,0,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(cognome));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,1,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(CF));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,2,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(NTelefono));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,3,item);

        item=new QTableWidgetItem();
		item->setText(QString::fromStdString(ContribuzioneGuadagno + " €"));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,4,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(ProbabilitaRitenzioneAnno));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,5,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(NomeAzienda));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,6,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(PIVA));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,7,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(sconto));
        item->setTextAlignment(Qt::AlignCenter);
		table->setItem(r,8,item);
    }

    QHeaderView* header=table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

}

void MostraClienti::addTable(QVBoxLayout* mainLayout)
{
    table= new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(9);

    QStringList attributi;
    attributi<<"Cognome"<<"Nome"<<"Cod. Fiscale"<<"Num. Telefono"<<"CG"<<"PRA"<<"Nome azienda"<<"P. IVA"<<"Sconto azienda";
    table->setHorizontalHeaderLabels(attributi);

    mainLayout->addWidget(table);
}

void MostraClienti::AddButtons(QVBoxLayout* mainLayout)
{
    QHBoxLayout* buttonsLayout=new QHBoxLayout();
    QPushButton* Cancella=new QPushButton("CANCELLA RIGA");
    Cancella->setFont(QFont(Cancella->text(), 13, -1, false));
    Cancella->setMinimumSize(300,50);
    connect(Cancella,SIGNAL(clicked()), this, SLOT(CancellaButtonClickedSlot()));
    buttonsLayout->addWidget(Cancella, Qt::AlignCenter, Qt::AlignHCenter);


    QPushButton* Aggiorna=new QPushButton("Aggiorna CG e PRA clienti");
    Aggiorna->setFont(QFont(Aggiorna->text(), 13, -1, false));
    Aggiorna->setMinimumSize(300,50);
    connect(Aggiorna,SIGNAL(clicked()), this, SLOT(AggiornaCgPrSlot()));
    buttonsLayout->addWidget(Aggiorna, Qt::AlignCenter, Qt::AlignHCenter);


    mainLayout->addLayout(buttonsLayout);
}

void MostraClienti::aggiornaCgPr()
{
	presenter->CalcolaCgPr();
}

MostraClienti::MostraClienti(QWidget* parent):QWidget(parent)
{
    QVBoxLayout* mainLayout= new QVBoxLayout;
    mainLayout->setContentsMargins(10,5,10,10);
    AddBackButton(mainLayout);
    addTable(mainLayout);
    AddButtons(mainLayout);
    setLayout(mainLayout);
}

void MostraClienti::setPresenter(Presenter *c)
{
	presenter=c;
}

void MostraClienti::showEliminaCliente()
{
    if(table->rowCount()>0){
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setMinimumSize(250,110);
        dialog->setIcon(QMessageBox::Warning);
        dialog->setText("Sei sicuro di voler eliminare il cliente della riga: "+QString::number(table->currentRow()+1)+" ?");
        QPushButton* SiButton=new QPushButton("Si");
        QPushButton* NoButton=new QPushButton("No");
        dialog->addButton(SiButton,QMessageBox::YesRole);
        connect(SiButton,SIGNAL(pressed()),this,SLOT(CancellaClienteSlot()));
        dialog->addButton(NoButton,QMessageBox::NoRole);

        dialog->show();
    }
    else
    {
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setIcon(QMessageBox::Information);
        dialog->setText("Nessun cliente da eliminare");

        dialog->show();
    }
}

void MostraClienti::CancellaButtonClickedSlot()
{
    showEliminaCliente();
}

void MostraClienti::CancellaClienteSlot()
{
    QTableWidgetItem* item=table->item(table->currentRow(),2);
	presenter->EliminaCliente(item->text());
    aggiornaTable();
}

void MostraClienti::showAggiornamentoCgPr()
{
    QMessageBox* dialog= new QMessageBox();
    dialog->setText("Le statistiche relative a:\n•Contribuzione guadagno \n•Probabilità ritenzione annua\n sono state aggiornate");
    dialog->setIcon(QMessageBox::Information);

    dialog->show();
}

void MostraClienti::AggiornaCgPrSlot()
{
    aggiornaCgPr();
    showAggiornamentoCgPr();
    aggiornaTable();
}

void MostraClienti::aggiornaTableSlot()
{
    aggiornaTable();
}
