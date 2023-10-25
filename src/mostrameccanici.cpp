#include "mostrameccanici.h"

MostraMeccanici::MostraMeccanici(QWidget *parent):QWidget(parent)
{
    QVBoxLayout* mainLayout= new QVBoxLayout;
    mainLayout->setContentsMargins(10,5,10,10);
    addBackButton(mainLayout);
    addTable(mainLayout);
    AddCancellaButton(mainLayout);
    setLayout(mainLayout);
}

void MostraMeccanici::setPresenter(Presenter *c)
{
	presenter=c;
}


void MostraMeccanici::addBackButton(QVBoxLayout *mainLayout)
{
    QToolBar* toolbar = new QToolBar;
    mainLayout->setMenuBar(toolbar);
    QIcon tornaIndietro = QApplication::style()->standardIcon(QStyle::SP_ArrowLeft);
    toolbar->setMovable(false);
    QAction* back = toolbar->addAction(tornaIndietro, "home");
    connect(back, SIGNAL(triggered()), this, SIGNAL(goToHomeSignal()));
}

void MostraMeccanici::addTable(QVBoxLayout *mainLayout)
{
    table= new QTableWidget();
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setColumnCount(5);

    QStringList attributi;
    attributi<<"Cognome"<<"Nome"<<"Cod. Fiscale"<<"Num. Telefono"<<"Stipendio mensile";
    table->setHorizontalHeaderLabels(attributi);

    mainLayout->addWidget(table);
}

void MostraMeccanici::AddCancellaButton(QVBoxLayout *mainLayout)
{
    QPushButton* Cancella=new QPushButton("CANCELLA RIGA");
    Cancella->setFont(QFont(Cancella->text(), 13, -1, false));
    Cancella->setMinimumSize(350,50);
    mainLayout->addWidget(Cancella, Qt::AlignCenter, Qt::AlignHCenter);
    connect(Cancella,SIGNAL(clicked()), this, SLOT(CancellaButtonClickedSlot()));
}

void MostraMeccanici::aggiornaTable()
{
	for(int i = 0 ; i< table->rowCount(); i++)
	{
		delete table->item(i,0);
		delete table->item(i,1);
		delete table->item(i,2);
		delete table->item(i,3);
		delete table->item(i,4);
	}

	u_int rows=presenter->getMeccanici().getSize();
    table->setRowCount(rows);

    u_int r=rows-1;
    QTableWidgetItem* item;

	for(auto i= presenter->getMeccanici().begin(); i!=presenter->getMeccanici().end(); i++,r--)
    {

        vett<std::string> dati=(*i)->getVettoreDati();

        std::string nome=dati[0];
        std::string cognome=dati[1];
        std::string CF=dati[2];
        std::string NTelefono=dati[3];
        std::string stipendio=dati[4];

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
        item->setText(QString::fromStdString(stipendio+" €"));
        item->setTextAlignment(Qt::AlignCenter);
        table->setItem(r,4,item);

    }
    QHeaderView* header=table->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

}

void MostraMeccanici::showEliminaMeccanico()
{
    if(table->rowCount()>0){
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setMinimumSize(250,110);
        dialog->setIcon(QMessageBox::Warning);
        dialog->setText("Sei sicuro di voler eliminare il meccanico della riga: "+QString::number(table->currentRow()+1)+" ?");
        QPushButton* SiButton=new QPushButton("Si");
        QPushButton* NoButton=new QPushButton("No");
        dialog->addButton(SiButton,QMessageBox::YesRole);
        connect(SiButton,SIGNAL(pressed()),this,SLOT(cancellaMeccanicoSlot()));
        dialog->addButton(NoButton,QMessageBox::NoRole);

        dialog->show();
    }
    else
    {
        QMessageBox* dialog= new QMessageBox(this);
        dialog->setIcon(QMessageBox::Information);
        dialog->setText("Nessun meccanico da eliminare");

        dialog->show();
    }
}

void MostraMeccanici::aggiornaTableSlot()
{
    aggiornaTable();
}

void MostraMeccanici::CancellaButtonClickedSlot()
{
    showEliminaMeccanico();
}

void MostraMeccanici::cancellaMeccanicoSlot()
{
    QTableWidgetItem* item=table->item(table->currentRow(),2);
	presenter->EliminaMeccanico(item->text());
    aggiornaTable();
}

