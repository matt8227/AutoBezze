#ifndef LINEEDIT_H
#define LINEEDIT_H
#include <QLineEdit>

class LineEdit: public QLineEdit
{
private:
	int defaultCursorPosition = 0;
protected:
	void mousePressEvent(QMouseEvent *event);
public:
	/**
	 * @brief setDefaultCursorPosition imposta il valore di default del cursore quando si interagisce con la LineEdit
	 * @param a valore >0 indicante la posizione
	 */
	void setDefaultCursorPosition(int a);
};

#endif // LINEEDIT_H
