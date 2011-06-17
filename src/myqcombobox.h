#ifndef MYQCOMBOBOX_H
#define MYQCOMBOBOX_H


 #include <QComboBox>
  #include <QKeyEvent>
 class myQComboBox : public QComboBox
{
Q_OBJECT
public:
	myQComboBox ( QWidget * parent  ) :  QComboBox(parent) {}

		
	virtual void keyPressEvent ( QKeyEvent * event ) 
	{
		QString key_code;
		int key_val;
		 key_val =  event->key() ;
		key_code = event->text() ;
		if( (key_code != QString("1")) && (key_code != QString("2")) && (key_code != QString("3")) && (key_code != QString("4")) && (key_code != QString("5")) && (key_code != QString("6")) && (key_code != QString("7")) && (key_code != QString("8")) && (key_code != QString("9")) && (key_code != QString("0")) && (key_val != 16777219))
			event->ignore();
		else
			QComboBox::keyPressEvent ( event );
	}
 };

#endif
