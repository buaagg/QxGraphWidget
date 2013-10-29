#include "qxgraphwidget.h"
#include <QPaintEvent>
#include <QPainter>

#pragma warning(disable: 4100)
#pragma warning(disable: 4716)

QxGraphWidget::QxGraphWidget(QWidget *parent) :
    QWidget(parent)
{
}

void QxGraphWidget::setScaleLevel(const QVector<QxGraphScaleLevel> &)
{

}

QxGraphScaleLevel QxGraphWidget::getCurrentScaleLevel() const
{
}

QxGraphChannelId QxGraphWidget::createChannel(QxGraphChannelType c, short priority, calcProxy proxy)
{
}

void QxGraphWidget::deleteChannel(QxGraphChannelId)
{

}

void QxGraphWidget::clearChannel()
{

}

bool QxGraphWidget::containsChannel(QxGraphChannelId) const
{

}

int QxGraphWidget::getChannelCount() const
{

}

int QxGraphWidget::getChannelDataCount(QxGraphChannelId) const
{

}

QxGraphChannelInfo QxGraphWidget::getChannelInfo(const QxGraphChannelId) const
{

}

bool QxGraphWidget::addBatchData(QxGraphChannelId, const QxGraphBatchData *pData)
{

}

bool QxGraphWidget::addAnalogData(QxGraphChannelId, const QTime &t, const QxGraphAnalogData &d)
{

}

bool QxGraphWidget::addSwitchData(QxGraphChannelId, const QTime &t, const QxGraphSwitchData &d)
{

}

float QxGraphWidget::getProgress(const QxGraphChannelId) const
{

}

float QxGraphWidget::getProgress() const
{

}

QxGraphAnalogData QxGraphWidget::getAnalogDataByTime(const QxGraphChannelId, const QTime &t)
{

}

QxGraphSwitchData QxGraphWidget::getSwitchDataByTime(const QxGraphChannelId, const QTime &t)
{

}

std::pair<QxGraphAnalogData, QxGraphAnalogData> QxGraphWidget::getDataRange(QxGraphChannelId) const
{

}

void QxGraphWidget::clearData(QxGraphChannelId)
{

}

void QxGraphWidget::clearAllData()
{

}

void QxGraphWidget::hideChannel(QxGraphChannelId)
{

}

void QxGraphWidget::showChannel(QxGraphChannelId)
{

}

bool QxGraphWidget::getVisible(const QxGraphChannelId) const
{

}

void QxGraphWidget::setFocusChannel(const QxGraphChannelId, bool existence) const
{

}

bool QxGraphWidget::hasFocusChannel() const
{

}

QVector<QxGraphChannelId> QxGraphWidget::getFocusChannels() const
{

}

void QxGraphWidget::clearFocusChannel()
{

}

void QxGraphWidget::modifyChannelRange(const QxGraphChannelId, QxGraphAnalogData lower_bound, QxGraphAnalogData upper_bound)
{

}

void QxGraphWidget::setBackGroundColor(const QColor &c)
{

}

QColor QxGraphWidget::getBackGroundColor() const
{

}

void QxGraphWidget::setGridColor(const QColor &c)
{

}

QColor QxGraphWidget::getGridColor() const
{

}

void QxGraphWidget::setLineStyle(const QxGraphChannelId, const QPen &)
{

}

QPen QxGraphWidget::getLineStyle(const QxGraphChannelId) const
{

}

void QxGraphWidget::setChannelColor(const QxGraphChannelId, const QColor &c)
{

}

QColor QxGraphWidget::getChannelColor(const QxGraphChannelId)
{

}

void QxGraphWidget::setTimeAxisStyle(const QPen &)
{

}

QPen QxGraphWidget::getTimeAxisStyle() const
{

}

void QxGraphWidget::setFocusAxisStyle(const QPen &)
{

}

QPen QxGraphWidget::getFocusAxisStyle() const
{

}

void QxGraphWidget::setAllowMouseDrag(bool)
{

}

bool QxGraphWidget::getAllowMouseDrag() const
{

}

void QxGraphWidget::setAllowScale(bool)
{

}

bool QxGraphWidget::getAllowScale() const
{

}

void QxGraphWidget::setTimeAxis(const QTime &, bool autoMove)
{

}

QTime QxGraphWidget::getTimeAxis()
{

}

void QxGraphWidget::showTimeAxis()
{

}

void QxGraphWidget::hideTimeAxis()
{

}

bool QxGraphWidget::isTimeAxisVisible() const
{

}

bool QxGraphWidget::isAutoMove() const
{

}

void QxGraphWidget::setFocusAxis(const QTime &)
{

}

QTime QxGraphWidget::getFocusAxis()
{

}

bool QxGraphWidget::isBufferFull(const QxGraphChannelId) const
{

}

void QxGraphWidget::setChannelPointStyle(const QxGraphChannelId, QxGraphChannelPointStyle)
{

}

QxGraphChannelPointStyle QxGraphWidget::getChannelPointStyle(const QxGraphChannelId)
{

}


float calcMeanProxy(float *pData, int size)
{

}

void QxGraphWidget::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();/*
    qDebug() << "Width = " << rect.width();
    qDebug() << "Height = " << rect.height();*/
    int w = rect.width();
    int h = rect.height();

    QPainter painter;
    painter.begin( this );
    painter.setRenderHint( QPainter::Antialiasing );
    painter.setPen( QPen(Qt::black, 1) );
    painter.drawLine( QPoint(0, 0), QPoint( w, h ) );
    painter.drawLine( QPoint(0, h), QPoint( w, 0 ) );

    painter.end();

}
