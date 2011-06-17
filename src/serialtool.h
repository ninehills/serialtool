#ifndef _SERIALTOOL_H_
#define _SERIALTOOL_H_
#include <QStringList>
#include <QDir>
#include <QTextBrowser>
#include <QThread>
#include <QMutex>
#include <QTimer>
#include <QScrollArea>
#include <QAbstractScrollArea>
#include <QAbstractSlider>
#include <QScrollBar>
#include <QPalette>
#include <QTemporaryFile>
#include <QFile>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include "ui_serialtool.h"

#define COM1 "/dev/ttyS0"
#define COM2 "/dev/ttyS1"
#define COM3 "/dev/ttyS2"
#define COM4 "/dev/ttyS3"
#define COM5 "/dev/ttyUSB0"
#define COM6 "/dev/ttyUSB1"

class ComReadThread;
class MyComTool :	public QWidget, public Ui_serailToolForm
{
	Q_OBJECT
public:
	MyComTool(QWidget* = 0);
	friend class ComReadThread ;
	virtual void closeEvent ( QCloseEvent * event ) ;

private:
	ComReadThread* myComThread;
	int fd_com, fdr, fds,sty_num;
	unsigned int auto_sent_count;
	unsigned int auto_sent_time;
	int receive_byte_counter;
	int sent_byte_counter;
	int already_sent_times;
    bool com_status, cease_receive_dispaly, auto_sent, sent_nolimited,sent_hex_model;
    bool eol_status;
    QString saveFileName,openFileName;
    QString com_all_status;
    QString com_Num;
    QTimer auto_sent_interval;
	struct termios oldtio, newtio;
	char hex_to_sent[10240];
	QFile saved;
	QString tmp_file_name;

private slots:
	void comStrat_Stop_Con();
	void clearCom_Receive();
	void ceaseCom_Receive();
	void set_autoCom_Sent();
	void to_autoCom_Sent();
	void manualCom_Sent();
	void dis_Help_txt();
	void clearCom_Sent();
	void set_widget_style();	
	void set_Save_Path();
	void set_Receive_Hex(int)	;
	void set_sent_Hex(int)	;
    void set_eol(int);
	void clear_Rs_counter();
	void clear_Sent_times();
    void	open_Sent_File();
    void to_Save_File();
public slots:
	void Log(QString   sMessage) 
 	{
		if(!(cease_receive_dispaly))
   	    {
			comReceivePlainTextEdit->insertPlainText(sMessage);
   	 		++receive_byte_counter;
   	 		comSentLabel->setNum (receive_byte_counter);
  	 	}
   	}
   	void Name(QString temp_name)
	{
		tmp_file_name =   temp_name;
	}
signals:
	void ClearTmpFile();
};

class ComReadThread : public QThread
{
	Q_OBJECT

public:

	ComReadThread  (MyComTool* parent) : my(parent), haved_data(false) , hex_displaymodel(false), tmpSaveFile("/tmp/comdata"){}
	MyComTool * my;
	bool haved_data;
	bool hex_displaymodel;
	 QTemporaryFile tmpSaveFile;
public slots:
	void ClearTmpFile()
	{
		tmpSaveFile.resize(0);
		tmpSaveFile.close();
		tmpSaveFile.open();
	}
protected:
   QMutex mutex;
	virtual void run();
signals:   
        void Log(QString   sMessage);
        void Name(QString temp_name);
};		


#endif




