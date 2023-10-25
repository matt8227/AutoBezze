#ifndef MOSTRACLIENTI_H
#define MOSTRACLIENTI_H

#include <QTableWidget>
#include <QHeaderView>

#include "presenter.h"

class MostraClienti : public QWidget
{
    Q_OBJECT
private:
	Presenter* presenter;
    QTableWidget* table;
    void AddBackButton(QVBoxLayout* mainLayout);

    void addTable(QVBoxLayout* mainLayout);

    void showEliminaCliente();

    void aggiornaTable();

    void AddButtons(QVBoxLayout* mainLayout);

    void aggiornaCgPr();

    void showAggiornamentoCgPr();

public:

    explicit MostraClienti(QWidget* parent = nullptr);

	void setPresenter(Presenter* c);

signals:
    void goToHomeSignal();

public slots:
    void aggiornaTableSlot();
private slots:
    void CancellaButtonClickedSlot();
    void CancellaClienteSlot();
    void AggiornaCgPrSlot();

};


#endif // MOSTRACLIENTI_H
