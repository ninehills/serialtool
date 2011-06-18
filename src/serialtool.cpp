#include <QtGui>
#include "serialtool.h"

MyComTool::MyComTool(QWidget* parent)
 :	QWidget(parent),
  	fd_com(-1),
  	sty_num(0),
  	auto_sent_count(0),
  	receive_byte_counter(0),
  	sent_byte_counter(0),
  	already_sent_times(0),
 	com_status(false),
 	cease_receive_dispaly(false),
	auto_sent(false),
	sent_hex_model(false),
	saveFileName(QDir::currentPath () + "/comdata.txt"),
 	com_all_status(""),
	com_Num("COM1"),
 	 saved("/tmp/savedata")
	
{
	setupUi(this);
	myComThread = new  ComReadThread(this);
	qApp->setStyle("GTK");
	displayPathLabel->setText(saveFileName);		
	autoSentpushButton->setEnabled (false);
	manualSentPushButton->setEnabled (false);
	saveDataPushButton->setEnabled (false);
	connect(openCloseSerialPushButton, SIGNAL(clicked()), this, SLOT(comStrat_Stop_Con()));
	connect(closeSelflPushButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(clearDisplayPushButton, SIGNAL(clicked()), this, SLOT(clearCom_Receive()));
	connect(ceaseDisplayPushButton, SIGNAL(clicked()), this, SLOT(ceaseCom_Receive()));
	connect(autoSentpushButton, SIGNAL(clicked()), this, SLOT(set_autoCom_Sent()));
	connect(helpPushButton, SIGNAL(clicked()), this, SLOT(dis_Help_txt()));
	connect(clearSentPushButton, SIGNAL(clicked()), this, SLOT(clearCom_Sent()));
	connect(manualSentPushButton, SIGNAL(clicked()), this, SLOT(manualCom_Sent()));
	connect(colorPushButton, SIGNAL(clicked()), this, SLOT(set_widget_style()	));
	connect(hexDisplaycheckBox, SIGNAL(stateChanged(int)), this, SLOT(set_Receive_Hex(int)));
	connect(hexSentcheckBox, SIGNAL(stateChanged(int)), this, SLOT(set_sent_Hex(int)));
    connect(eolCheckBox, SIGNAL(stateChanged(int)), this, SLOT(set_eol(int)));
	connect(selectPathPushButton, SIGNAL(clicked()), this, SLOT(set_Save_Path()));
	connect(clearCountPushButton, SIGNAL(clicked()), this, SLOT(clear_Rs_counter()));
	connect(sentTimesPushButton, SIGNAL(clicked()), this, SLOT(clear_Sent_times()));
	connect(selectFilePushButton, SIGNAL(clicked()), this, SLOT(open_Sent_File()));
	connect(saveDataPushButton, SIGNAL(clicked()), this, SLOT(to_Save_File()));
	connect(&auto_sent_interval, SIGNAL(timeout ()), this, SLOT(to_autoCom_Sent()));
	connect(myComThread, SIGNAL(Log(QString)),this, SLOT(Log(QString)));
	connect(myComThread, SIGNAL(Name(QString)),this, SLOT(Name(QString)));
	connect(this, SIGNAL(ClearTmpFile()),myComThread,SLOT(ClearTmpFile()));	
	
}

void MyComTool::comStrat_Stop_Con()
{
	QString com_Buad, com_Testbit, com_Databit, com_Stopbit;
	QString path;
	if(com_status == false)
	{
		com_Num = selectserialComboBox->currentText();
		com_Buad = selectBuadComboBox->currentText();
		com_Testbit = selsetTestbitComboBox->currentText();
		com_Databit = selectDatabitComboBox->currentText();
		com_Stopbit = selectStopbitComboBox->currentText();
		com_all_status = com_Num + "         " + com_Buad + "   " +  com_Testbit + "   " + com_Databit  + "   " + com_Stopbit;
		if(com_Num == "COM1")
			fd_com = open(COM1, O_RDWR);
		else 	if(com_Num == "COM2")
			fd_com = open(COM2, O_RDWR);  
		else if(com_Num == "COM3")
			fd_com = open(COM3, O_RDWR);
		else if(com_Num == "COM4")
			fd_com = open(COM4, O_RDWR);
		else if(com_Num == "COM5")
			fd_com = open(COM5, O_RDWR);
		else 	if(com_Num == "COM6")
			fd_com = open(COM6, O_RDWR);
		else
			fd_com = open(COM1, O_RDWR);
		if(fd_com != -1)
		{
			path = ":/on.jpg";
			serialstatusLabel->setPixmap(path);
			openCloseSerialPushButton->setText(tr("关闭串口"));
			com_all_status.replace(5,  8, "Used    ");
			com_status = true;
			selectserialComboBox->setEnabled (false);
		    selectBuadComboBox->setEnabled (false);		
		    selsetTestbitComboBox->setEnabled (false);	
		    selectDatabitComboBox->setEnabled (false);				
		    selectStopbitComboBox->setEnabled (false);			
		    autoSentpushButton->setEnabled (true);
			manualSentPushButton->setEnabled (true);
	  		saveDataPushButton->setEnabled (true);  	          
        	tcgetattr(fd_com,&oldtio); 
	 		bzero(&newtio,sizeof(newtio)); 
			if(com_Buad == "50")
				newtio.c_cflag = B50 | CLOCAL;
			else	if(com_Buad == "75")
				newtio.c_cflag = B75 | CLOCAL;
			else	if(com_Buad == "110")
				newtio.c_cflag = B110 | CLOCAL;
			else	if(com_Buad == "134")
				newtio.c_cflag = B134 | CLOCAL;		
			else	if(com_Buad == "150")
				newtio.c_cflag = B150 | CLOCAL;
			else	if(com_Buad == "200")
				newtio.c_cflag = B200 | CLOCAL;
			else	if(com_Buad == "300")
				newtio.c_cflag = B300 | CLOCAL;			
			else	if(com_Buad == "600")
				newtio.c_cflag = B600 | CLOCAL;
			else	if(com_Buad == "1200")
				newtio.c_cflag = B1200 | CLOCAL;
			else	if(com_Buad == "1800")
				newtio.c_cflag = B1800 | CLOCAL;		
			else	if(com_Buad == "2400")
				newtio.c_cflag = B2400 | CLOCAL;
			else	if(com_Buad == "4800")
				newtio.c_cflag = B4800 | CLOCAL;
			else	if(com_Buad == "9600")
				newtio.c_cflag = B9600 | CLOCAL;				
			else	if(com_Buad == "19200")
				newtio.c_cflag = B19200 | CLOCAL;
			else	if(com_Buad == "38400")
				newtio.c_cflag = B38400 | CLOCAL;		
			else	if(com_Buad == "57600")
				newtio.c_cflag = B57600 | CLOCAL;
			else	if(com_Buad == "115200")
				newtio.c_cflag = B115200 | CLOCAL;
			else	if(com_Buad == "230400")
				newtio.c_cflag = B230400| CLOCAL;			
			else
				newtio.c_cflag = B9600;

			if(com_Testbit == "无校验(NONE)")
			{
    			newtio.c_cflag &= ~PARENB; 
				newtio.c_iflag &= ~INPCK;
				newtio.c_iflag |= IGNBRK;				
			}
			else if(com_Testbit == "偶校验(EVEN)")
			{
				newtio.c_cflag |=  PARENB;
	  			newtio.c_cflag &= ~PARODD;
	 			newtio.c_iflag |= INPCK;
	 			newtio.c_iflag |= IGNBRK;
			}
			else if(com_Testbit == "奇校验(ODD)")
			{
				newtio.c_cflag |= (PARODD | PARENB);
				newtio.c_iflag |= INPCK; 
				newtio.c_iflag |= IGNBRK;
			}
			else if(com_Testbit == "空校验(SPACE)")
			{
    			newtio.c_cflag &= ~PARENB; 
				newtio.c_iflag &= ~INPCK;
				newtio.c_cflag &= ~CSTOPB;	
				newtio.c_iflag |= IGNBRK;			
			}
			else
			{
    			newtio.c_cflag &= ~PARENB; 
				newtio.c_iflag &= ~INPCK; 
				newtio.c_iflag |= IGNBRK;				
			}

			if(com_Databit == "5")
			{
				newtio.c_cflag&=~CSIZE;
				newtio.c_cflag |=CS5;	
			}
			else if(com_Databit == "6")
			{
				newtio.c_cflag&=~CSIZE;
				newtio.c_cflag |=CS6;	
			}	
			else if(com_Databit == "7")
			{
				newtio.c_cflag&=~CSIZE;
				newtio.c_cflag |=CS7;	
			}	
			else if(com_Databit == "8")
			{
				newtio.c_cflag&=~CSIZE;
				newtio.c_cflag |=CS8;	
			}	
			else
			{
				newtio.c_cflag&=~CSIZE;
				newtio.c_cflag |=CS8;					
			}

			if(com_Stopbit == "1")	
				newtio.c_cflag &= ~CSTOPB;
			else 	if(com_Stopbit == "2")					
				newtio.c_cflag |= CSTOPB;			
			if(com_Stopbit == "1.5")	
				newtio.c_cflag &= ~CSTOPB; 			
			else											
				newtio.c_cflag &= ~CSTOPB;		
	  		newtio.c_oflag &= ~OPOST ;
			newtio.c_lflag &= ~ICANON;
	  		newtio.c_lflag &= ~ECHO;
	  		newtio.c_cflag |= CREAD;
			newtio.c_cc[VTIME] = 0;  
	 		newtio.c_cc[VMIN]  = 1;   
	  		tcflush(fd_com, TCIFLUSH);
	  		tcsetattr(fd_com, TCSANOW, &newtio);				
	  		::close(fd_com);
	  		
		if(com_Num == "COM1")
		{
			fds = open(COM1, O_WRONLY);
			fdr = open(COM1, O_RDONLY);
		}
		else 	if(com_Num == "COM2")
		{
			fds = open(COM2, O_WRONLY);
			fdr = open(COM2, O_RDONLY);
		}
		else if(com_Num == "COM3")
		{
			fds = open(COM3, O_WRONLY);
			fdr = open(COM3, O_RDONLY);
		}
		else if(com_Num == "COM4")
		{
			fds = open(COM4, O_WRONLY);
			fdr = open(COM4, O_RDONLY);
		}
		else if(com_Num == "COM5")
		{
			fds = open(COM5, O_WRONLY);
			fdr = open(COM5, O_RDONLY);
		}	
		else 	if(com_Num == "COM6")
		{
			fds = open(COM6, O_WRONLY);
			fdr = open(COM6, O_RDONLY);
		} 
		else
		{
			fds = open(COM1, O_WRONLY);
			fdr = open(COM1, O_RDONLY);
		}
	  		myComThread->start();
		}
		else
		{
			path = ":/error.jpg";
			serialstatusLabel->setPixmap(path);
			com_all_status.clear();
			com_all_status = com_Num + " Error " ;
		}
	}
	else
	{
		::close(fdr);
		::close(fds);		
		path = ":/off.jpg";
		serialstatusLabel->setPixmap(path);
		com_all_status.replace(5, 8, "Closed  ");
		openCloseSerialPushButton->setText(tr("打开串口"));
		com_status = false;
		selectserialComboBox->setEnabled (true);
		selectBuadComboBox->setEnabled (true);		
	    selsetTestbitComboBox->setEnabled (true);	
	    selectDatabitComboBox->setEnabled (true);				
	    selectStopbitComboBox->setEnabled (true);		
	    autoSentpushButton->setEnabled (false);
		manualSentPushButton->setEnabled (false);
   		saveDataPushButton->setEnabled (false);
	}
	comStatusLabel->setText(com_all_status );
}



void  MyComTool::closeEvent ( QCloseEvent * event ) 
{
	if(com_status)
	{
		::close(fdr);
		::close(fds);	
		if(com_Num == "COM1")
			fd_com = open(COM1, O_RDWR);
		else 	if(com_Num == "COM2")
			fd_com = open(COM2, O_RDWR);
		else if(com_Num == "COM3")
			fd_com = open(COM3, O_RDWR);
		else if(com_Num == "COM4")
			fd_com = open(COM4, O_RDWR);
		else if(com_Num == "COM5")
			fd_com = open(COM5, O_RDWR);
		else 	if(com_Num == "COM6")
			fd_com = open(COM6, O_RDWR);
		else
			fd_com = open(COM1, O_RDWR);
		tcsetattr(fd_com,TCSANOW,&oldtio);
	 	::close(fd_com);
		myComThread->terminate ();
		myComThread->wait();
		myComThread->tmpSaveFile.remove();
		event->accept();
	}
}

void MyComTool::clearCom_Receive()
{
	 comReceivePlainTextEdit->clear();
}

void MyComTool::ceaseCom_Receive()
{
	bool dis_able;
	cease_receive_dispaly = !cease_receive_dispaly;
	if(cease_receive_dispaly)
	{
		dis_able = !isEnabled();
		comReceivePlainTextEdit->setEnabled (dis_able);
		ceaseDisplayPushButton->setText(tr("开始接收"));
		newtio.c_cflag &= ~CREAD;
		tcflush(fd_com, TCIFLUSH);
	  	tcsetattr(fd_com, TCSANOW, &newtio);				
		
	}
	else
	{
		dis_able = isEnabled() ;
		comReceivePlainTextEdit->setEnabled (dis_able);
		ceaseDisplayPushButton->setText(tr("停止接收"));
		newtio.c_cflag |= CREAD;
		tcflush(fd_com, TCIFLUSH);
	  	tcsetattr(fd_com, TCSANOW, &newtio);				
	}		
	
}

void MyComTool::set_autoCom_Sent()
{
	 bool disable_autosent_setup;
	 auto_sent = !auto_sent;
	 if( auto_sent)
	 {
	 	comSentTextEdit->setReadOnly(true);
	 	QString times = tr("无限");
	 	if(times ==autoSentTimesComboBox->currentText())
	 		sent_nolimited = true;
	 	else
	 	{
	 		sent_nolimited = false;	 	
 			auto_sent_count = atoi(autoSentTimesComboBox->currentText().toAscii());
		}
		auto_sent_time = atoi(sentTimeLineEdit->text().toAscii());
		manualCom_Sent();
		auto_sent_interval.start (auto_sent_time);
	 	autoSentpushButton->setText(tr("停止发送"));
 		disable_autosent_setup = !isEnabled();
 		sentTimeLineEdit->setEnabled (disable_autosent_setup);
 		autoSentTimesComboBox->setEnabled (disable_autosent_setup);
 		manualSentPushButton->setEnabled (disable_autosent_setup); 	
 	 }
 	else
 	{
 		comSentTextEdit->setReadOnly(false);
 		auto_sent_interval.stop();
 		autoSentpushButton->setText(tr("自动发送"));
 		disable_autosent_setup = isEnabled();
 		sentTimeLineEdit->setEnabled (disable_autosent_setup);
 		autoSentTimesComboBox->setEnabled (disable_autosent_setup);;	
 		manualSentPushButton->setEnabled (disable_autosent_setup); 	
	}
}

void MyComTool::to_autoCom_Sent()
{
	auto_sent_interval.stop();
	if(sent_nolimited)
	{
			manualCom_Sent();
			auto_sent_interval.start (auto_sent_time);
	}
	else
	{
		if((--auto_sent_count) > 0)
		{
			manualCom_Sent();
			auto_sent_interval.start (auto_sent_time);
		}
		else
		{
			auto_sent = !auto_sent;
			autoSentpushButton->setText(tr("自动发送"));
 			comSentTextEdit->setReadOnly(false);			
	 		sentTimeLineEdit->setEnabled (true);
	 		autoSentTimesComboBox->setEnabled (true);
	 		manualSentPushButton->setEnabled (true); 	
		}
	}
	
}

void MyComTool::dis_Help_txt()
{
	QMessageBox msgBox(this);
	QString	mymes = tr("串口调试工具 1.00.00 \n基于QT4.6&Linux 2.6的串口调试工具\nzhuhe<zhuhehz@yahoo.com.cn>\n<QQ :704227778>");
	QString pix;	
	pix = ":/thank.png";
	msgBox.setIconPixmap(pix);
	msgBox.setWindowTitle(tr("关于"));	
	msgBox.setText(tr("\n\n\n感谢使用本串口调试工具！"));
    msgBox.setDetailedText (mymes);
 	msgBox.exec();
}

void MyComTool::clearCom_Sent()
{
	comSentTextEdit->clear();
}


void MyComTool::set_widget_style()	
{
	sty_num++;
	QPalette palette = qApp->palette();	
	switch(sty_num)
	{
		case 1:
				qApp->setStyle("plastique");
				palette.setColor(QPalette::Window,QColor(255, 234, 254, 255));
				palette.setColor(QPalette::WindowText, Qt::darkGreen);
				palette.setColor(QPalette::Text, Qt::darkGreen);
				palette.setColor(QPalette::ButtonText, Qt::darkGreen);				
				qApp->setPalette(palette);	
				break;
		case 2:
				qApp->setStyle("cde");
				palette.setColor(QPalette::Window,QColor(223, 235, 220, 255));
				palette.setColor(QPalette::WindowText, Qt::darkMagenta);
				palette.setColor(QPalette::Text, Qt::darkMagenta);
				palette.setColor(QPalette::ButtonText, Qt::darkMagenta);				
				qApp->setPalette(palette);	
				break;
		case 3:
				qApp->setStyle("motif");
				palette.setColor(QPalette::Window,QColor(215, 252, 255, 255));
				palette.setColor(QPalette::WindowText, Qt::darkYellow);
				palette.setColor(QPalette::Text, Qt::darkYellow);
				palette.setColor(QPalette::ButtonText, Qt::darkYellow);				
				qApp->setPalette(palette);	
				break;
		case 4:
				qApp->setStyle("cleanlooks");
				palette.setColor(QPalette::Window,QColor(255, 241, 226, 255));
				palette.setColor(QPalette::WindowText, Qt::darkBlue);
				palette.setColor(QPalette::Text, Qt::darkBlue);
				palette.setColor(QPalette::ButtonText, Qt::darkBlue);				
				qApp->setPalette(palette);		
				break;	
		default:
				qApp->setStyle("GTK");
				palette.setColor(QPalette::Window,QColor(238, 238, 238, 255));
				palette.setColor(QPalette::WindowText, Qt::black);
				palette.setColor(QPalette::Text, Qt::black);
				qApp->setPalette(palette);	
				sty_num = 0;
	}
}

void MyComTool::set_Save_Path()
{
	saveFileName = QFileDialog::getSaveFileName (
																this,
																tr("保存文件"),
																"~/comdata.txt",
																tr("文本文件(*.txt)"));
				
	if(saveFileName.isNull())
		saveFileName = QDir::currentPath () + "/comdata.txt";
	displayPathLabel->setText(saveFileName);												
}

void MyComTool::open_Sent_File()
{
	openFileName = QFileDialog::getOpenFileName (
																this,
																tr("打开文件"),
																"/home",
																tr("文本文件(*.txt)"));
	if(openFileName.isNull())
		fileNameLabel->setText(tr("没有选择文件"));		
	else					
	{
													
			QFile sentFile(openFileName);
     		if (!sentFile.open(QIODevice::ReadOnly | QIODevice::Text))
     		{
     			fileNameLabel->setText(tr("没有选择文件"));	
     			QMessageBox fileMesBox(this);
     			QString my_pix;	
     			my_pix = ":/erroring.png";
				QPixmap img(my_pix); 		
				fileMesBox.setIconPixmap(my_pix);
				fileMesBox.setWindowTitle(tr("错误"));	
				fileMesBox.setText(tr("文件无效!"));
				fileMesBox.exec();
        	 	return;
       	 	}
			fileNameLabel->setText(openFileName);		
   	 		QTextStream inOutDisplay(&sentFile);
     		while (!inOutDisplay.atEnd())
     	 	{
         		QString myLine = inOutDisplay.readLine();
         		comSentTextEdit->insertPlainText(myLine);
         	}
	}
}

void MyComTool::set_Receive_Hex(int)	
{
	if( hexDisplaycheckBox->isChecked ())
		myComThread ->hex_displaymodel = true;
	else
		myComThread->hex_displaymodel = false;
}
void MyComTool::set_sent_Hex(int)	
{
	if( hexSentcheckBox->isChecked ())
		sent_hex_model = true;
	else
		sent_hex_model = false;
}

void MyComTool::set_eol(int)
{
    if (eolCheckBox->isChecked())
        eol_status = true;
    else
        eol_status = false;
}

void MyComTool::clear_Rs_counter()
{
	receive_byte_counter = 0;
	 sent_byte_counter = 0;
	comSentLabel->setNum(sent_byte_counter);
	comReceiveLabel->setNum(receive_byte_counter);
}

void MyComTool::clear_Sent_times()
{
	already_sent_times = 0;
	sentTimesClearLabel->setNum(already_sent_times);
}

void MyComTool::to_Save_File()
{
	bool save_sucessed;	
	QMessageBox saveMesBox(this);
	QString mypix;	
	if(QFile::exists(saveFileName))
	{
		QMessageBox replaceBox(this);
		replaceBox.setWindowTitle(tr("提示"));	
		replaceBox.setText(tr("     该文件已经存在!"));
		replaceBox.setInformativeText(tr("        确定替换码?"));
		replaceBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
		replaceBox.setDefaultButton(QMessageBox::Yes);
		int ret =  replaceBox.exec();
		switch (ret) 
  		{
  			case QMessageBox::Yes:
												QFile::remove(saveFileName);
       											break;
   			case QMessageBox::No:
												break;

   			default:
												break;
 		}
	}
	save_sucessed = saved.copy (tmp_file_name , saveFileName);  
	emit	ClearTmpFile();
   	if(save_sucessed)
	{
				
				mypix = ":/success.png";
				QPixmap img(mypix); 		
				saveMesBox.setIconPixmap(mypix);
				saveMesBox.setWindowTitle(tr("信息"));	
				saveMesBox.setText(tr("保存成功!"));
				saveMesBox.exec();
	}
	else
	{
				mypix = ":/erroring.png";
				QPixmap img(mypix); 		
				saveMesBox.setIconPixmap(mypix);
				saveMesBox.setWindowTitle(tr("信息"));	
				saveMesBox.setText(tr("保存失败!"));
				saveMesBox.exec();
	}		

}


void MyComTool::manualCom_Sent()
{
	QString user_input;
	char *to_sent;
	char sent_buf[2];
	QChar *to_sent_tmp;
	int b;
	size_t char_count;
	user_input = comSentTextEdit->toPlainText ();
    if(eol_status){
        // append \r\n
        QString eol;
        eol.sprintf("%c%c", 0x0d, 0x0a);
        user_input.append(eol);
    }
	to_sent =  user_input.toAscii().data();
	to_sent_tmp = user_input.data();
	char_count = 0;
	already_sent_times++;
	if(!sent_hex_model)
	{
		while (!to_sent_tmp->isNull())
	 	{
			++to_sent_tmp;
			 ++char_count;
		}
		sent_byte_counter  +=  write(fds,  to_sent, char_count);
		comReceiveLabel->setNum (sent_byte_counter);
	}
	else
	{
	 	while (!to_sent_tmp->isNull())
	 	{	 		     
		 	b= (int)*to_sent;
			sprintf(sent_buf, "%x", b);
			hex_to_sent[char_count] = sent_buf[0];
			hex_to_sent[char_count + 1]  = sent_buf[1];
			++to_sent_tmp;
			++to_sent;
			 ++char_count;
			 ++char_count;
			 if(char_count >= 10240)
			 {
			 	char_count = 0;
			 	QMessageBox warningBox(this);
				QString mypix;	
				mypix = ":/erroring.png";
				QPixmap img(mypix); 		
				warningBox.setIconPixmap(mypix);
				warningBox.setWindowTitle(tr("错误"));	
				warningBox.setText(tr("发送数据过长!"));
				warningBox.exec();
				break;
			 }
		 }
		sent_byte_counter  +=  write(fds,  hex_to_sent, char_count);
		comReceiveLabel->setNum (sent_byte_counter);
	}
	sentTimesClearLabel->setNum(already_sent_times);
}

void ComReadThread ::run()
{
	QString com_read_buf = "Now Begin!"; 
	QString temp_name;
	char to_receivebuf[2]; 
	size_t n;
  	mutex.lock();
   	int a;
   	bool wrop = false;
	to_receivebuf[0] = NULL;
   	to_receivebuf[1] = NULL;
	tmpSaveFile.open();
   	temp_name = tmpSaveFile.fileName();
   	emit   Name(temp_name);
	while(1)
	{
		while(!(my->cease_receive_dispaly))
		{
			n = read(my->fdr,  to_receivebuf , 1);
			if (n == 1)
			{
				if(to_receivebuf[0] == 0x0a)
					wrop = true;
				else
					wrop = false;
		        if(hex_displaymodel)
		        {
		              a= (int)to_receivebuf[0];
					sprintf(to_receivebuf, "%2x", a);
				}
				QTextStream out(&tmpSaveFile);
				out << to_receivebuf[0];
				if(wrop)
					out << endl;
				com_read_buf = QString(QLatin1String(to_receivebuf));
				to_receivebuf[1] = NULL;
				emit   Log(com_read_buf );
			}
		}
	}
    mutex.unlock();
}
