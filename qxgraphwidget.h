#ifndef QXGRAPHWIDGET_H
#define QXGRAPHWIDGET_H

// 2013-10-04

#include <QWidget>
#include <QtCore>

//*******************************************************************
//
//*******************************************************************

// QT数据类型要哪个线程申请，哪个线程释放，跨线程释放可能引起莫名其妙的问题

enum  QxGraphChannelType {
    TypeAnalog,
    TypeSwitch,
};

enum QxGraphChannelPointStyle {
    PointStyleNone,

    PointStyleSolidCircle, // o
    PointStyleCross, // x
    PointStyleStar, // *

    PointStyleSolidSqurare,
    PointStyleSolidTriangleUpward,
    PointStyleSolidTriangleDownward,
    PointStyleSolidTriangleLeftward,
    PointStyleSolidTriangleRightward,

    PointStyleHollowSquare,
    PointStyleHollowTriangleUpward,
    PointStyleHollowTriangleDownward,
    PointStyleHollowTriangleLeftward,
    PointStyleHollowTriangleRightward,
};

class QxGraphChannelInfo
{
public:
    QxGraphChannel();

    // 1. 通道名
    // 2. 类型: 布尔，浮点
    // 3. 仅浮点类型有效:
    //    1. Y 轴默认上下限
    //    2. 数据单位
    QString name;
    QxGraphChannelType type;
    QxGraphAnalogData upper_bound;
    QxGraphAnalogData lower_bound;
    QString unit;
};

#define QxGraphChannelId                int
#define QX_GRAPH_CHANNEL_ID_INVALID     -1      // 无效通道 ID

#define QxGraphAnalogData               float
#define QxGraphSwitchData               float
#define QX_GRAPH_ANALOG_DATA_INVALID FLT_MAX
#define QX_GRAPH_SWITCH_DATA_TRUE QxGraphSwitchData(1)
#define QX_GRAPH_SWITCH_DATA_FALSE QxGraphSwitchData(0)
#define QX_GRAPH_SWITCH_DATA_INVALID QxGraphSwitchData(-1)

// TODO: 其他定义：
// 1. 布尔通道高度
// 2. 曲线绘画像素间隔宽度
// 3. 是否开启日志
// 4. Y 轴纵向，等分 10 份，宏定义
// 5. X 轴横向，等分 15 份，宏定义

class QxGraphBatchData
{
public:
    // 1. 起始时间
    // 2. 间隔 (单位：秒)
    // 3. 数据类型
    // 4. 数据队列
    QTime startTime;
    int interval; // by second
    QxGraphChannelType dataType;
    QVector<float> data; // TODO: 好假
};

class QxGraphScaleLevel {
    QString name;
    int interval; // by second
};

typedef float (*calcProxy)( float *pData, int size );
float calcMeanProxy( float *pData, int size );

//*******************************************************************
//
//*******************************************************************
class QxGraphWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QxGraphWidget( QWidget *parent = 0 );

public slots:
    // 方法一定要线程安全
    // 写日志，格式随便
    // 数据范围 10 ^ 6 级别

    //---------------------------------
    // ** 缩放比例、数据分层设置

    // 设置当前缩放尺度
    void setScaleLevel( QVector<QxGraphScaleLevel> );
        // This must be invoked before anything

    QxGraphScaleLevel currentScaleLevel() const;

    //---------------------------------
    // ** 数据、通道操作

    // 创建/删除通道 (0-8 条)
    QxGraphChannelId createChannel( const QxGraphChannel &c, short priority = 0, calcProxy = calcMeanProxy );
        //我负责释放QxGraphCalcProxy
        //对于bool值的变量，priority大的放在上面，相同的话，由我决定，
    void deleteChannel( const QxGraphChannelId );
    void clearChannel();

    // 通道是否存在
    bool containsChannel( const QxGraphChannelId ) const; // containsChannel( QXGRAPHCHANNELID_INVALID ) is false.

    // 通道数量
    int countChannel() const;

    // 通道数据数量
    int countChannelData( const QxGraphChannelId ) const; // If containsChannel( QxGraphChannelId ) is false, returns 0
    QxGraphChannelInfo getChannelInfo( const QxGraphChannelId ) const; // If containsChannel( QxGraphChannelId ) is false, the behaviour is undefined.

    // 添加数据
    //    1. 块添加
    //    2. 逐点添加
    bool addData( const QxGraphChannelId, const QxGraphBatchData *pData ); // 我负责释放QxGraphBatchData
    bool addData( const QxGraphChannelId, const QTime &t, const QxGraphAnalogData &d );
    bool addData( const QxGraphChannelId, const QTime &t, const QxGraphSwitchData &d );
        // 如果containsChannel( QxGraphChannelId )是false，则返回false
        // 或者buffer满了，则发射异常信号，并返回false
        // 如果数据类型非法，则返回false，并且什么都不做。
        // 如果时间重叠，后续重叠数据直接丢弃，并放回false
    float getProgress( const QxGraphChannelId ) const;
    float getProgress() const; // 最慢的

    // 根据时间获取数据
    QxGraphAnalogData getDataByTime( const QxGraphChannelId, const QTime& t );
    QxGraphSwitchData getDataByTime( const QxGraphChannelId, const QTime& t );
    // 约束
        // 如果containsChannel( QxGraphChannelId )是false，则返回QX_GRAPH_ANALOG_DATA_INVALID / QX_GRAPH_SWITCH_DATA_INVALID
        // 如果数据类型非法，则返回*_INVALID，并且什么都不做。
        // 返回的是rawData所对应的Data，QTime只保留到秒，其余丢弃

    // 返回某通道全部值中的最大值、最小值
    pair<QxGraphAnalogData, QxGraphAnalogData> getDataRange( const QxGraphChannelId ) const;
        // 返回第一个分量为最小值，第二个分量为最大值
        // 如果containsChannel( QxGraphChannelId )是false，则返回 make_pair(QX_GRAPH_ANALOG_DATA_INVALID,QX_GRAPH_ANALOG_DATA_INVALID)
        // 如果该Channel为空，则返回 make_pair(QX_GRAPH_ANALOG_DATA_INVALID,QX_GRAPH_ANALOG_DATA_INVALID)

    // 按通道清空数据
    // 清空所有数据
    void clearData( const QxGraphChannelId );
    void clearAllData();
        // 如果containsChannel( QxGraphChannelId )是false，则什么都不做

    // 显示、隐藏通道
    void hideChannel(const QxGraphChannelId);
    void showChannel(const QxGraphChannelId);
        // 如果containsChannel( QxGraphChannelId )是false，则什么都不做
    bool getVisualable( const QxGraphChannelId ) const;
        // 如果containsChannel( QxGraphChannelId )是false，则返回false

    // ## 焦点通道可有多条，每条焦点通道都需要显示 Y 轴
    // 设置（添加删除）焦点通道 ( Y 轴随之改变 )
    void setFocusChannel( const QxGraphChannelId, bool existence ) const;
        // 如果containsChannel( QxGraphChannelId )是false, 则什么都不干

    // 是否有焦点通道
    bool hasFocusChannel() const;
    // 获取焦点通道列表
    QVector<QxGraphChannelId> getFocusChannels() const;
    // 清空焦点通道 ( Y 轴恢复百分比模式 )
    void clearFocusChannel();

    // 修改某通道 Y 轴上下限
    void modifyChannelRange( const QxGraphChannelId, QxGraphAnalogData lower_bound, QxGraphAnalogData upper_bound );

    //---------------------------------
    // ** 样式操作

    // 设置背景色
    void setBackGroundColor( const QColor& c );
    QColor getBackGroundColor() const;
    // 设置网格色
    void setGridColor( const QColor& c );
    QColor getGridColor() const;
    // 设置通道线样式 (粗细、线样式)
    void setLineStyle( const QxGraphChannelId, const QPen& );
    QPen getLineStyle( const QxGraphChannelId ) const;
    // 设置通道颜色 (浮点、布尔都用这个设置)
    void setChannelColor( const QxGraphChannelId, const QColor& c );
    QColor getChannelColor( const QxGraphChannelId );
    // 设置时间轴，焦点轴线样式
    void setTimeAxisStyle( const QPen&  );
    QPen getTimeAxisStyle( ) const;
    void setFocusAxisStyle( const QPen&  );
    QPen getFocusAxisStyle() const;

    // 是否允许 鼠标拖拽平移操作
    void setAllowMouseDrag( bool );
    bool getAllowMouseDrag() const;
    // 是否允许 缩放
    void setAllowScale( bool );
    bool getAllowScale() const;
    // ## 缩放操作有两种：通过 X 轴菜单选取，或鼠标滚轮缩放

    //---------------------------------
    // ## X 轴有两条线
    // 1. 时间轴, 只能通过方法设置
    // 2. 焦点轴, 可通过方法设置, 用户也可通过鼠标操作, 改变时, 需要发出信号

    //---------------------------------
    // ** 时间轴操作 (滚动)

    // 设置时间轴位置
    void setTimeAxis( const QTime&, bool autoMove );
    QTime getTimeAxis();
    void showTimeAxis();
    void hideTimeAxis();
    bool isTimeAxisVisualable() const;
    bool isAutoMove() const;

    //---------------------------------
    // ** 焦点轴操作

    // 焦点轴所在时间
    void setFocusAxis( const QTime&  );
    QTime getFocusAxis();

    //---------------------------------
    // ** 状态

    // 查询缓存是否已满
    bool isBufferFull( const QxGraphChannelId  ) const;

//    void setFont ( const QFont &f )  {
//        QWidget::setFont( f );
//    }

//    void setForegroundRole ( QPalette::ColorRole role ) {
//        QWidget::setForegroundRole( role );
//    }

    void setChannelPointStyle( const QxGraphChannelId, QxGraphChannelPointStyle = PointStyleNone );
    QxGraphChannelPointStyle getChannelPointStyle( const QxGraphChannelId );

signals:
    // 异常信号
    void errorInvoked( QString );
    void warnningInvoked( QString );

    // Y 轴对话框选取信号
    void selectYAxisDialog( const QxGraphChannelId );

    // 焦点轴改变信号1
    void focusAxisChanged( QTime ); // 单击鼠标左键
    void timeAxisChanged( QTime ); // 单击鼠标右键

    // TODO: 所有涉及到修改的，改完了告诉你
    // 通道的删除修改创建

    // TODO: 批量数据处理进度信号、100% 就是处理完成信号

    void scaleLevelChanged( const QxGraphScaleLevel );
};

#endif // QXGRAPHWIDGET_H
