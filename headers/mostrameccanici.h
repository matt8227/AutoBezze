#ifndef MOSTRAMECCANICI_H
#define MOSTRAMECCANICI_H

#include <QMessageBox>
#include <QToolBar>
#include <QCloseEvent>

#include "presenter.h"

class MostraMeccanici: public QWidget
{
    Q_OBJECT
private:
	Presenter* presenter;

    QTableWidget* table;


    void addBackButton(QVBoxLayout* mainLayout);
    void addTable(QVBoxLayout* mainLayout);
    void AddCancellaButton(QVBoxLayout* mainLayout);

    void aggiornaTable();

    void showEliminaMeccanico();

public:
    explicit MostraMeccanici(QWidget* parent=nullptr);

	void setPresenter(Presenter* c);


signals:
    void goToHomeSignal();

public slots:
    void aggiornaTableSlot();
private slots:
    void CancellaButtonClickedSlot();
    void cancellaMeccanicoSlot();
};

#endif // MOSTRAMECCANICI_H
