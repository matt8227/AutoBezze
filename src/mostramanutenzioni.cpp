#include "mostramanutenzioni.h"

MostraManutenzioni::MostraManutenzioni(QWidget* parent): QWidget(parent)
{
    QVBoxLayout* mainLayout= new QVBoxLayout;
    mainLayout->setContentsMargins(10,5,10,10);
    addBackButton(mainLayout);
    addTable(mainLayout);
    AddCancellaButton(mainLayout);
    setLayout(mainLayout);
}

void MostraManutenzioni::setPresenter(Presenter *c)
{
	presenter=c;
}

void MostraManutenzioni::aggiornaTableSlot()
{
    aggiornaTable();
}

void MostraManutenzioni::CancellaButtonClickedSlot()
{
    showEliminaManutenzione();
}

void MostraManutenzioni::CancellaManutenzioneSlot()
{
    QTableWidgetItem* item=table->item(table->currentRow(),0);
	presenter->EliminaManutenzioe(item->text());
    aggiornaTable();
}

void MostraManutenzioni::showDettagliManutenzione()
{
    u_int r=table->currentRow();
    QDialog* dialog= new QDialog();
    dialog->setMinimumSize(400,250);
    QVBoxLayout* mainlayout=new QVBoxLayout();
    QLabel* ClienteLabel=new QLabel("Cliente: ");
    QLineEdit* Cliente=new QLineEdit();
    Cliente->setReadOnly(true);
    Cliente->setText(table->item(r,1)->text());
    QLabel* MeccanicoLabel=new QLabel("Cliente: ");
    QLineEdit* Meccanico=new QLineEdit();
    Meccanico->setReadOnly(true);
    Meccanico->setText(table->item(r,2)->text());
    QLabel* TargaLabel= new QLabel("Targa: ");
    QLineEdit* targa=new QLineEdit();
    targa->setMaximumWidth(100);
    targa->setText(table->item(r,3)->text());
    targa->setReadOnly(true);
    QLabel* DataLabel=new QLabel("Data: ");
    QLineEdit* data= new QLineEdit();
    data->setMaximumWidth(100);
    data->setText(table->item(r,6)->text());
    data->setReadOnly(true);
    QLabel* costoLabel=new QLabel("Costo: ");
    QLineEdit* costo= new QLineEdit();
    costo->setMaximumWidth(100);
    costo->setText(table->item(r,5)->text());
    data->setReadOnly(true);
    QLabel* descrizoneLabel=new QLabel("Descrizione lavoro effettuato: ");
    QTextEdit* descrizione= new QTextEdit();
    descrizione->setText(table->item(r,4)->text());
    descrizione->setReadOnly(true);
    QGridLayout* layout=new QGridLayout();
    layout->addWidget(ClienteLabel,0,0);
    layout->addWidget(Cliente,0,1);
    layout->addWidget(MeccanicoLabel,1,0);
    layout->addWidget(Meccanico,1,1);
    layout->addWidget(TargaLabel,2,0);
    layout->addWidget(targa,2,1);
    layout->addWidget(costoLabel,3,0);
    layout->addWidget(costo,3,1);
    layout->addWidget(DataLabel,4,0);
    layout->addWidget(data,4,1);
    mainlayout->addLayout(layout);
    mainlayout->addWidget(descrizoneLabel, Qt::AlignHCenter, Qt::AlignHCenter);
    mainlayout->addWidget(descrizione);
    QPushButton* chiudiButton=new QPushButton("Chiudi");
    connect(chiudiButton, SIGNAL(pressed()),dialog, SLOT(close()));
    mainlayout->addWidget(chiudiButton, Qt::AlignRight, Qt::AlignRight);
    dialog->setLayout(mainlayout);
    dialog->show();
}

void MostraManutenzioni::VisualizzaDettagliManutenzioneSlot()
{
    showDettagliManutenzione();
}

void MostraManutenzioni::addBackButton(QVBoxLayout *mainLayout)
{
    QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
    QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
    toolbar->setMovable(false);
    QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SIGNAL(goToHomeSignal()));
}

void MostraManutenzioni::addTable(QVBoxLayout *mainLayout)
{
    table= new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(7);

    QStringList attributi;
    attributi<<"ID"<<"Cliente"<<"Meccanico"<<"Targa veicolo"<<"Descrizione"<<"Costo"<<"Data";
    table->setHorizontalHeaderLabels(attributi);
    connect(table,SIGNAL(cellDoubleClicked(int,int)), this, SLOT(VisualizzaDettagliManutenzioneSlot()));
    mainLayout->addWidget(table);
}

void MostraManutenzioni::AddCancellaButton(QVBoxLayout *mainLayout)
{
    QPushButton* Cancella=new QPushButton("CANCELLA RIGA");
    Cancella->setFont(QFont(Cancella->text(), 13, -1, false));
    Cancella->setMinimumSize(350,50);
    mainLayout->addWidget(Cancella, Qt::AlignCenter, Qt::AlignHCenter);
    connect(Cancella,SIGNAL(clicked()), this, SLOT(CancellaButtonClickedSlot()));
}

void MostraManutenzioni::aggiornaTable()
{
	u_int rows=presenter->getManutenzioni().getSize();
    table->setRowCount(rows);

    u_int r=rows-1;
    QTableWidgetItem* item;

	for(auto i= presenter->getManutenzioni().begin(); i!=presenter->getManutenzioni().end(); i++,r--)
    {
        vett<std::string> dati=(*i)->getVettoreDati();

        std::string id=dati[0];
        std::string Targa=dati[1];
        std::string CFcliente=dati[2];
		QString CognomeNomeCliente=presenter->getCognomeNomeCliente(CFcliente);
        std::string CFmeccanico=dati[3];
		QString CognomeNomeMeccanico=presenter->getCognomeNomeMeccanico(CFmeccanico);
        std::string Costo=dati[4];
        std::string data=dati[5];
        std::string descrizione=dati[6];

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(id));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,0,item);

        item=new QTableWidgetItem();
        item->setText(CognomeNomeCliente+" ["+QString::fromStdString(CFcliente)+"]");
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,1,item);

        item=new QTableWidgetItem();
        item->setText(CognomeNomeMeccanico+" ["+QString::fromStdString(CFmeccanico)+"]");
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,2,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(Targa));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,3,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(descrizione));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,4,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(Costo+" €"));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,5,item);

        item=new QTableWidgetItem();
        item->setText(QString::fromStdString(data));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,6,item);


    }
    QHeaderView* header=table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void MostraManutenzioni::showEliminaManutenzione()
{
    if(table->rowCount()>0){
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setMinimumSize(250,110);
        dialog->setIcon(QMessageBox::Warning);
        dialog->setText("Sei sicuro di voler eliminare la manutenzione della riga: "+QString::number(table->currentRow()+1)+" ?");
        QPushButton* SiButton=new QPushButton("Si");
        QPushButton* NoButton=new QPushButton("No");
        dialog->addButton(SiButton,QMessageBox::YesRole);
        connect(SiButton,SIGNAL(pressed()),this,SLOT(CancellaManutenzioneSlot()));
        dialog->addButton(NoButton,QMessageBox::NoRole);

        dialog->show();
    }
    else
    {
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setIcon(QMessageBox::Information);
        dialog->setText("Nessuna manutenzione da eliminare");

        dialog->show();
    }
}
