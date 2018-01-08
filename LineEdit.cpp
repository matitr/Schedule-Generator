#include "LineEdit.h"

#include <QObject>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QScrollbar>
#include <QStringListModel>

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent), c(0) {
	listData = nullptr;
}


LineEdit::~LineEdit() {

}

void LineEdit::setCompleter(QCompleter *comp) {
//	if (c)
//		disconnect(c, 0, this, 0);
	c = comp;

	if (!c)
		return;

	c->setWidget(this);
	c->setCompletionMode(QCompleter::PopupCompletion);
	c->setCaseSensitivity(Qt::CaseInsensitive);
	QObject::connect(c, SIGNAL(activated(QString)),
		this, SLOT(insertCompletion(QString)));
}

void LineEdit::setList(QStringList *l) {
	listData = l;
	listData->count();
}

QCompleter *LineEdit::completer() const {
	return c;
}

void LineEdit::insertCompletion(const QString& completion)
{
	if (c->widget() != this)
		return;

	int extraLetters = completion.length() - c->completionPrefix().length();


	QString textLine = text();
	std::string l1 = textLine.toStdString();
	int pos = cursorPosition();
	textLine.insert(pos, completion);
	std::string l2 = textLine.toStdString();
	textLine.remove(pos - c->completionPrefix().length(), c->completionPrefix().length());
	std::string l3 = textLine.toStdString();
	setText(textLine);


}

QString LineEdit::textUnderCursor() const {
//	QTextCursor tc = textCursor();
//	tc.select(QTextCursor::WordUnderCursor);
	int pos = cursorPosition();
	QString fieldText = text();
	int i = 0, commaBefore = -1, commaAfter = -1;

	for (QString::iterator it = fieldText.begin(); it != fieldText.end(); it++, i++) {
		std::string j = fieldText.toStdString();
		if (*it == ',' && i < pos)
			commaBefore = i;

		if (*it == ',' && commaAfter == -1 && i >= pos)
			commaAfter = i;
	}

	if (commaAfter != -1)
		fieldText.chop(fieldText.count() - commaAfter);

	if (commaBefore != -1)
		fieldText.remove(0, commaBefore + 1);

	std::string j = fieldText.toStdString();
	return fieldText;
}

void LineEdit::focusInEvent(QFocusEvent *e) {
//	if (c)
//		c->setWidget(this);
	QLineEdit::focusInEvent(e);
}

void LineEdit::keyPressEvent(QKeyEvent *e) {
	if (c && c->popup()->isVisible()) {
		
		switch (e->key()) {
		case Qt::Key_Enter:
		case Qt::Key_Return:
		case Qt::Key_Escape:
		case Qt::Key_Tab:
		case Qt::Key_Backtab:
			e->ignore();
			return;
		default:
			break;
		}
	}
	
	if (c->model())
		delete c->model();

	c->setModel(new QStringListModel(*listData, c));

	bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E);
	if (!c || !isShortcut)
		QLineEdit::keyPressEvent(e);
	
	const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
	if (!c || (ctrlOrShift && e->text().isEmpty()))
		return;

	QString completionPrefix = textUnderCursor();

	if (completionPrefix.length() < 1)
		return;

	if (completionPrefix != c->completionPrefix()) {
		c->setCompletionPrefix(completionPrefix);
		c->completionModel()->index(0, 0);
		c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
	}
	
	c->complete();
}







