#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QtGui/QWidget>
#include <QtGui/QLabel>
#include <QtGui/QMovie>
#include <QtCore/QTimer>

class Notification : public QWidget
{
	Q_OBJECT
public:
	enum Action {
		Settings,
		Download,
		User,
		Progress,
		Error,
		Success,
		Wait
	};
    Notification(Notification::Action t, const  QString & m, int ms = 0, QWidget * w = 0);
	bool isLast();
	void setLast(bool s);
	QString & message();
public slots:
	void destroy();
protected:
	void mousePressEvent(QMouseEvent * e);
	void mouseReleaseEvent(QMouseEvent * e);
	void paintEvent(QPaintEvent * e);
private:
	Notification::Action mAction;
	QString mMessage;
	int mTime;
	bool mLast;
	bool mIsClosable;
};

#endif