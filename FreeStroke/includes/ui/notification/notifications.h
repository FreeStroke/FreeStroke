#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QtGui/QWidget>
#include <QtGui/QPainter>

#include "notification.h"

class Notifications : public QWidget
{
	Q_OBJECT
public:
    Notifications(QWidget * w = 0);
	static Notifications * address();
	static Notification * add(Notification::Action t, const QString & m, int ms = 0);
	QList<Notification *> * notificationList();
	void organize();
protected:
	void paintEvent(QPaintEvent * e);
private:
	static Notifications * mAdress;
	QList<Notification *> * mNotificationList;
};

#endif