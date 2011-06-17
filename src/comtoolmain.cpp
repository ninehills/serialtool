#include <QtGui/QApplication>
#include <QtCore>

#include "serialtool.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
 	QTextCodec::setCodecForTr(QTextCodec::codecForName("gb2312"));
	Q_INIT_RESOURCE(myresource);
	
	MyComTool tool;
	tool.show();
	
	return app.exec();	
}
