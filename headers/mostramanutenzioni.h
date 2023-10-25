#ifndef MOSTRAMANUTENZIONI_H
#define MOSTRAMANUTENZIONI_H

#include "presenter.h"

class MostraManutenzioni : public QWidget
{
    Q_OBJECT
private:
	Presenter* presenter;

    QTableWidget* table;

    void addBackButton(QVBoxLayout* mainLayout);
    void addTable(QVBoxLayout* mainLayout);
    void AddCancellaButton(QVBoxLayout* mainLayout);
    void aggiornaTable();
    void showEliminaManutenzione();

    void showDettagliManutenzione();

public:
    MostraManutenzioni(QWidget* parent=nullptr);

	void setPresenter(Presenter* c);

signals:
    void goToHomeSignal();

public slots:
    void aggiornaTableSlot();

private slots:
    void CancellaButtonClickedSlot();
    void CancellaManutenzioneSlot();
    void VisualizzaDettagliManutenzioneSlot();

};


#endif // MOSTRAMANUTENZIONI_H
