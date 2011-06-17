#ifndef MYQLINEEDIT_H
#define MYQLINEEDIT_H


 #include <QLineEdit>
  #include <QKeyEvent>
 class myQLineEdit  : public QLineEdit
{
Q_OBJECT
public:
	myQLineEdit ( QWidget * parent  ) :  QLineEdit(parent) {}

		
	virtual void keyPressEvent ( QKeyEvent * event ) 
	{
		QString key_code;
		int key_val;
		 key_val =  event->key() ;
		key_code = event->text() ;
		if( (key_code != QString("1")) && (key_code != QString("2")) && (key_code != QString("3")) && (key_code != QString("4")) && (key_code != QString("5")) && (key_code != QString("6")) && (key_code != QString("7")) && (key_code != QString("8")) && (key_code != QString("9")) && (key_code != QString("0")) && (key_val != 16777219))
			event->ignore();
		else
			QLineEdit::keyPressEvent ( event );
	}
 };

#endif
