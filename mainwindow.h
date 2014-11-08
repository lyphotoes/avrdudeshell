#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QTableWidget>
#include <QtGui/QBitmap>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QFileDialog>
#include <QDebug>
#include <QtGui/QRadioButton>
#include <QProcess>
#include<QtSql>
#include<QMessageBox>


class QSerialPort;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
//    struct PROGDEV
//    {
//        QString sID;//we use this for avrdude command line -p
//        QString sDesc;
//        QString sType;
//    };
//    struct PARTDEV
//    {
//        QString sID;//we use this for avrdude command line -p
//        QString sDesc;
//        quint32 iEepromSize;
//        quint32 iFlashSize;
//        quint8 iLockSize;
//        quint8 iCalSize;
//        quint8 iFuseSize;
//        quint8 ieFuseSize;
//        quint8 ihFuseSize;
//        quint8 ilFuseSize;
//    };

    //Q_DECLARE_METATYPE(PROGDEV);
    //Q_DECLARE_METATYPE(PARTDEV);



    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QProcess *process;
    QSerialPort *port;
    QComboBox *programmerCB,*portCB,*bitClockCB,*chipCB,*flashAutoCB,*eepromAutoCB,*optionVerbosityCB,*presetCB;
	QLineEdit *baudRateEdit,*flashPathEdit,*eepromPathEdit,*fuseLEdit,*fuseHEdit,*fuseEEdit,*lockBitEdit,*additionSetEdit,*commandEdit;
	QPushButton *chipDetectBtn,*flashPathBtn,*flashGoBtn,*eepromPathBtn,*eepromGoBtn,*presetSaveBtn,*presetDeleteBtn,*fuseReadBtn,*fuseWriteBtn,*fuseSetLinkBtn,*lockBitReadBtn,*lockBitWriteBtn,*bitSelectorBtn,*programBtn,*stopBtn,*aboutBtn,*optionBtn;
	QRadioButton *flashWriteRBtn,*flashReadRBtn,*flashVerifyRBtn,*eepromWriteRBtn,*eepromReadRBtn,*eepromVerifyRBtn;
    QCheckBox *optionForce,*optionDisVerify,*optionDisEraseFlash,*optionErase,*optionNWrite,*fuseSetCheckBox,*lockBitSetCheckBox;
	QTextBrowser *outputText;
    QLabel *flashSizeText,*eepromSizeText;
    void setUI(void);
    bool createConnection(void);
	QString parse(QString sSource,QString sFront,QString sEnd,qint64 * intLoc);
    void setPort(void);
private slots:
    void showOpenFlashDialog(void);
    void showOpenEEPDialog(void);
    void readConfig(void);// may delete

    void showData(int index);
    //void showData(void);
    void autoScroll(void);// the textbrowser auto scroll...
    void detectChip(void);
    void slotReadStandardOutError(void);



};

struct PROGDEV
{
    QString sID;//we use this for avrdude command line -p
    QString sDesc;
    QString sType;
};
struct PARTDEV
{
    QString sID;//we use this for avrdude command line -p
    QString sDesc;
    quint32 iEepromSize;
    quint32 iFlashSize;
    quint8 iLockSize;
    quint8 iCalSize;
    quint8 iFuseSize;
    quint8 ieFuseSize;
    quint8 ihFuseSize;
    quint8 ilFuseSize;
};

Q_DECLARE_METATYPE(PROGDEV)//;
Q_DECLARE_METATYPE(PARTDEV)//;

/*
QT_BEGIN_NAMESPACE
template <>
struct QMetaTypeId< TYPE >
{
    enum { Defined = 1 };
    static int qt_metatype_id()
        {
            static QBasicAtomicInt metatype_id = Q_BASIC_ATOMIC_INITIALIZER(0);
            if (!metatype_id)
                metatype_id = qRegisterMetaType< TYPE >(#TYPE,
                           reinterpret_cast< TYPE *>(quintptr(-1)));
            return metatype_id;
        }
};
QT_END_NAMESPACE
*/
#endif // MAINWINDOW_H
