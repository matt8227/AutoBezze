#include "lineedit.h"

void LineEdit::mousePressEvent(QMouseEvent* event)
{
	QLineEdit::mousePressEvent(event);
	setCursorPosition(defaultCursorPosition);
}

void LineEdit::setDefaultCursorPosition(int a)
{
	defaultCursorPosition = a;
}
