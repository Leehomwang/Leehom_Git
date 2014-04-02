#ifndef INFODIALOG_H
#define INFODIALOG_H

//#include <QDialog>
#include <QtGui>
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class InfoDialog : public QDialog
{
	Q_OBJECT
public:
	InfoDialog(QWidget *parent = 0);
signals:
	void findNext(const QString &str, Qt::CaseSensitivity cs);
	void findPrevious(const QString &str, Qt::CaseSensitivity cs);

	private slots:
		void findCliched();
		void enableFindButton(const QString &text);

private:
	QLabel *label;
	QLineEdit *lineEdit;
	QCheckBox *caseCheckBox;
	QCheckBox *backwardCheckBox;
	QPushButton *findButton;
	QPushButton *closeButton;
};

#endif