#include <QStringList>//包含了类QString和QStringList的定义。
#include <QDir>//类QDir提供了对目录结构和目录的访问方法。
#include "ui_findfileform.h"

class CFindFileForm :	public QWidget,
						public Ui_FindFileForm//类CFindFileForm以公有方式继承自Qwiget和Ui_FindFileForm。
{
	Q_OBJECT
public:
	CFindFileForm(QWidget* = 0);
	
private://声明了必需的成员函数和成员变量：
	QStringList findFiles(const QDir&, const QString&, const QString&);//实现文件的查找并返回符合条件的文件列表。
	void showFiles(const QDir&, const QStringList&);
	void tranvFolder(const QDir&, const QString& , const QString );//递归函数，实现对文件的递归查找。
	bool m_bStoped;//记录用户是否单击了“停止”按钮，如果是为true。
	bool	m_bSubfolder;//记录用户是否需要查找子文件夹中的文件，如果需要位true。
	bool	m_bSensitive;//用于查找包含特定文本信息的文件时，是否区分文本信息的大小写，如果区分位true。
	int m_nCount;
	 
private slots:
     void 	browse();//该槽函数响应用户的单击“浏览...”操作。
     void 	find();//响应用户单击“查找”操作。
	 void 	stop();//响应用户的“停止查找”操作。
	 void	doTxtChange(const QString&);//响应用户的输入“包含文本”操作。
};
#endif




