#pragma once

#include <QLineEdit>
#include <qcompleter.h>
#include <QCompleter>

class LineEdit : public QLineEdit {
	Q_OBJECT

public:
	LineEdit(QWidget *parent = 0);
	~LineEdit();

	void setCompleter(QCompleter *comp);
	void setList(QStringList *l);
	QCompleter *completer() const;

protected:
	void keyPressEvent(QKeyEvent *e) override;
	void focusInEvent(QFocusEvent *e) override;

private slots:
	void insertCompletion(const QString &completion);

private:
	QString textUnderCursor() const;

private:
	QCompleter *c;
	QStringList *listData;






};

