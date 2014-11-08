#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "mainwindow.h"
//not use the dnamtic libs
//#include "QtSerialPort/QSerialPort"
//#include "QtSerialPort/QSerialPortInfo"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setUI();

    //init.....
    //createConnection(); //no use ,i think the software should be little ,so don't use the database
    readConfig();
    setPort();
    //process = new QProcess(this);//move to the detectChip detect...
    //process->start("avrdude");

    //signals and slots .......

    connect(this->flashPathBtn,SIGNAL(clicked()),this,SLOT(showOpenFlashDialog()));
    connect(this->eepromPathBtn,SIGNAL(clicked()),this,SLOT(showOpenEEPDialog()));

    connect(this->outputText,SIGNAL(cursorPositionChanged()),this,SLOT(autoScroll()));
    connect(this->programmerCB,SIGNAL(activated(int)),this,SLOT(showData(int))); //this is for test the programmerCB no use
    //connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(showData()));//move to the detectChip slot.
    connect(this->chipDetectBtn,SIGNAL(clicked()),this,SLOT(detectChip()));



}

void MainWindow::setPort()
{
    this->port =new QSerialPort(this);// to-do: not used....
    this->portCB->clear();
    foreach(QSerialPortInfo info,QSerialPortInfo::availablePorts())
    {
        QStringList sl;
        sl<<info.systemLocation()<<info.description()<<info.manufacturer();
        this->portCB->addItem(info.portName(),QVariant(sl));
        //qDebug()<<info.systemLocation();
    }
}


//this is not used since the same name function below is the one we wanted...
void MainWindow::showData(int index)
{
    QVariant v;
    //this->outputText->append(QString("This is %1.").arg(index));
    v=this->programmerCB->itemData(index);
    PROGDEV p=v.value<PROGDEV>();
    this->outputText->append(QString("ID:%1.\nDESC:%2.\nTYPE:%3.\n").arg(p.sID,p.sDesc,p.sType));
}
/*
void MainWindow::showData()
{
    //QProcess *pro = (QProcess *)sender();
    QString out= process->readAllStandardOutput();
    qDebug()<<endl;
    qDebug()<<"start the readStandardOutput.....";
    qDebug()<<out;
    //this->outputText->setText("The text is:\n");
    //this->outputText->append(out);
    //this->outputText->append();
}
*/

void MainWindow::autoScroll()
{
    QTextCursor cursor =outputText->textCursor();
    cursor.movePosition(QTextCursor::End);
    outputText->setTextCursor(cursor);
}

void MainWindow::detectChip()
{
    //QProcess *avrdude = new QProcess() ;
    //outputText->append("ko");
    //QString program = "avrdude";
    //QStringList argList;
    //argList<<"-c arduino"<<"-p m644p"<<"-P /dev/ttyUSB0"<<"-b 115200";
    //process->start(program,argList);
    process = new QProcess();
    //connect(this->process,SIGNAL(readyReadStandardOutput()),this,SLOT(showData()));
    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(slotReadStandardOutError()));
    process->start(tr("/usr/local/avr/bin/avrdude -c arduino -p m644p -P /dev/ttyUSB0 -b 115200"));
    if(process->waitForStarted())
    {
        qDebug()<<"upload is overed.";
    }
    else
    {
        qDebug()<<"upload start failed...";
    }
    //process->waitForReadyRead();
    //process->st
    //process->waitForStarted();
    //QProcess::execute("/usr/local/avr/bin/avrdude");

}


MainWindow::~MainWindow()
{

}

void MainWindow::readConfig()
{
    //QString fileBuf;

    //char * buf[];
    //QString filePath=QFileDialog::getOpenFileName(this,"Open Config File",".","config File(*.conf)");
    //QFile file(filePath);
    QFile file("./avrdude.conf");// to-do: change the file path.
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)) qDebug()<<" can't read the file 'avrdude.conf' !"<<endl;

    //QTextStream in(&file);
    //fileBuf=in.readAll();

    qint64 ulSize=file.size();
    char *buf=new char[ulSize+1];
    buf[ulSize]=NULL;
    file.read(buf,ulSize);

    //file.readData(buf,ulSize);
    //char * i=fileBuf;

    //i[0]=fileBuf;
    char * pos=buf;
    for(;;)
    {
        QVariant v;
        PROGDEV * p=new PROGDEV;
        //PROGDEV p;
        qint64 strLoc=0;
        QString str="\nprogrammer";
        QString sp=parse(pos,str,str,&strLoc);
        if(sp==""){delete p;break;}
        QString s1=parse(sp,"id",";",0);
        if (s1==""){delete p;break;}
        p->sID=parse(s1,"\"","\"",0);
        s1=parse(sp,"desc",";",0);
        p->sDesc=parse(s1,"\"","\"",0);
        s1=parse(sp,"type","\n",0);
        p->sType=parse(s1,"=",";",0);
        p->sType.trimmed();
        v.setValue(*p);
        this->programmerCB->addItem(p->sID,v);
        //programmerCB->setItemData(p);
        //outputText->append(sp);
        pos+=strLoc;
    }
    pos=buf;
    for(;;)
    {
        QVariant v;
        PARTDEV * p=new PARTDEV;
        qint64 strLoc=0;
        QString str="\npart";
        QString sp=parse(pos,str,str,&strLoc);
        if (sp==""){delete p;break;}

        QString s1=parse(sp,"id",";",0);
        if(s1==""){delete p; break;}
        p->sID=parse(s1,"\"","\"",0);
        s1=parse(sp,"desc",";",0);
        p->sDesc=parse(s1,"\"","\"",0);

        s1=parse(sp,"\"eeprom\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->iEepromSize=s1.toInt();

        s1=parse(sp,"\"flash\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->iFlashSize=s1.toInt();

        s1=parse(sp,"\"lock\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->iLockSize=s1.toInt();

        s1=parse(sp,"\"calibration\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->iCalSize=s1.toInt();

        s1=parse(sp,"\"fuse\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->iFuseSize=s1.toInt();

        s1=parse(sp,"\"lfuse\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->ilFuseSize=s1.toInt();

        s1=parse(sp,"\"hfuse\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->ihFuseSize=s1.toInt();

        s1=parse(sp,"\"efuse\"","memory",0);
        s1=parse(s1," size ","\n",0);
        s1=parse(s1,"=",";",0);
        s1=s1.trimmed();
        p->ieFuseSize=s1.toInt();

        v.setValue(*p);
        this->chipCB->addItem(p->sDesc,v);

        pos+=strLoc;
    }

    delete[] buf;
    //outputText->setText(file.readAll());
    //QString i=QString("The file size is %1").arg(file.size());

    //qDebug()<<i;
     //       while (!file.atEnd())
   // {
     //   QByteArray line=file.readLine();
     //   QString str(line);
     //   this->outputText->setPlainText());
        //qDebug()<<str;
    //}
}


QString MainWindow::parse(QString sSource, QString sFront, QString sEnd,qint64 * intLoc)
{
    int iL=sSource.indexOf(sFront);
    if(iL==-1) return "";
    //qDebug()<<QString("the string is :%1").arg(sSource.mid(iL,sFront.length()));
    iL+=sFront.length();
    if(intLoc)
        memcpy(intLoc,&iL,sizeof(qint64));
    int iR=sSource.indexOf(sEnd,iL);
    if(iR==-1) return sSource.mid(iL);
    //QString str=QString("The iL=%1 and iR=%2.").arg(iL).arg(iR);
    //qDebug()<<QString("The size is :%1").arg(sSource.size());
    return sSource.mid(iL,iR-iL);
}

bool MainWindow::createConnection()
{
    bool existFlag = true;
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("mydb.db");
    if(!QFile::exists("mydb.db")) // check the database file exist.
    {
        qDebug()<<QString(" database is not exist.");
        existFlag=false;
    }
    //db.setDatabaseName("mydb.db");

    if( !db.open() )
    {
        QMessageBox::critical(0,QObject::tr("Database Error!"),db.lastError().text());
        return false;
    }
    if(!existFlag)
    {
    QSqlQuery  query;
    query.exec("create table student(id int primary key,name varchar)");
    query.exec("insert into student values(1,'xiaoguang')");
    }
       return true;
    //
}

void MainWindow::setUI()
{


    //the programmer groupbox
    QGroupBox *programmerGroup = new QGroupBox(tr("Programmer (-c)"));
    programmerCB = new QComboBox();
    QLabel *portLabel = new QLabel(tr("Port (-P)"));
    QLabel *baudRateLabel = new QLabel(tr("Baud rate (-b)"));
    QLabel *bitClockLabel = new QLabel(tr("Bit clock (-B)"));
    portCB = new QComboBox();
    baudRateEdit = new QLineEdit();
    bitClockCB = new QComboBox();
    QGridLayout *programmerLayout = new QGridLayout();
    programmerLayout->addWidget(programmerCB,0,0,1,3);
    programmerLayout->addWidget(portLabel,1,0,1,1);
    programmerLayout->addWidget(baudRateLabel,1,1,1,1);
    programmerLayout->addWidget(bitClockLabel,1,2,1,1);
    programmerLayout->addWidget(portCB,2,0,1,1);
    programmerLayout->addWidget(baudRateEdit,2,1,1,1);
    programmerLayout->addWidget(bitClockCB,2,2,1,1);
    programmerGroup->setLayout(programmerLayout);


    //the MCU groupbox
    QGroupBox *MCUGroup = new QGroupBox(tr("MCU (-p)"));
    chipCB = new QComboBox();
    QLabel *flashSizeLabel = new QLabel(tr("Flash:"));
    flashSizeText=new QLabel(tr(" KB"));
    eepromSizeText = new QLabel(tr(" KB"));
    QLabel *eepSizeLabel = new QLabel(tr("EEPROM:"));
    QHBoxLayout *sizeLabelLayout = new QHBoxLayout();
    sizeLabelLayout->addWidget(flashSizeLabel);
    sizeLabelLayout->addWidget(flashSizeText);
    sizeLabelLayout->addWidget(eepSizeLabel);
    sizeLabelLayout->addWidget(eepromSizeText);
    chipDetectBtn = new QPushButton(tr("Detect"));
    QVBoxLayout *MCULayout = new QVBoxLayout();
    MCULayout->addWidget(chipCB);
    MCULayout->addLayout(sizeLabelLayout);
    MCULayout->addWidget(chipDetectBtn);
    MCUGroup->setLayout(MCULayout);

    //the Flash groupbox
    QGroupBox *flashGroup = new QGroupBox(tr("Flash"));
    flashPathEdit = new QLineEdit();
    flashPathBtn = new QPushButton(tr("..."));
    QHBoxLayout *flashPathLayout = new QHBoxLayout();
    flashPathLayout->addWidget(flashPathEdit,1);
    flashPathLayout->addWidget(flashPathBtn);
    flashWriteRBtn = new QRadioButton(tr("Write"));
    flashReadRBtn = new QRadioButton(tr("Read"));
    flashVerifyRBtn = new QRadioButton(tr("Verify"));
    flashGoBtn = new QPushButton(tr("Go"));
    QLabel *flashLabel = new QLabel(tr("Format"));
    flashAutoCB = new QComboBox();
    QHBoxLayout *flashActionLayout = new QHBoxLayout();
    flashActionLayout->addWidget(flashWriteRBtn);
    flashActionLayout->addWidget(flashReadRBtn);
    flashActionLayout->addWidget(flashVerifyRBtn);
    flashActionLayout->addWidget(flashGoBtn);
    flashActionLayout->addWidget(flashLabel);
    flashActionLayout->addWidget(flashAutoCB);
    QVBoxLayout *flashLayout = new QVBoxLayout;
    flashLayout->addLayout(flashPathLayout);
    flashLayout->addLayout(flashActionLayout);
    flashGroup->setLayout(flashLayout);

    //the EEPROM groupbox
    QGroupBox *eepromGroup = new QGroupBox(tr("EEPROM"));
    eepromPathEdit = new QLineEdit();
    eepromPathBtn = new QPushButton(tr("..."));
    QHBoxLayout *eepromPathLayout = new QHBoxLayout;
    eepromPathLayout->addWidget(eepromPathEdit,1);
    eepromPathLayout->addWidget(eepromPathBtn);
    eepromWriteRBtn = new QRadioButton(tr("Write"));
    eepromReadRBtn = new QRadioButton(tr("Read"));
    eepromVerifyRBtn = new QRadioButton(tr("Verify"));
    eepromGoBtn = new QPushButton(tr("Go"));
    QLabel *eepromLabel = new QLabel(tr("Format"));
    eepromAutoCB = new QComboBox();
    QHBoxLayout *eepromActionLayout = new QHBoxLayout;
    eepromActionLayout->addWidget(eepromWriteRBtn);
    eepromActionLayout->addWidget(eepromReadRBtn);
    eepromActionLayout->addWidget(eepromVerifyRBtn);
    eepromActionLayout->addWidget(eepromGoBtn);
    eepromActionLayout->addWidget(eepromLabel);
    eepromActionLayout->addWidget(eepromAutoCB);
    QVBoxLayout *eepromLayout = new QVBoxLayout;
    eepromLayout->addLayout(eepromPathLayout);
    eepromLayout->addLayout(eepromActionLayout);
    eepromGroup->setLayout(eepromLayout);

    //the Option groupbox
    QGroupBox *optionGroup = new QGroupBox(tr("Options"));
    optionForce = new QCheckBox(tr("Force (-F)"));
    optionDisVerify = new QCheckBox(tr("Disable verify (-V)"));
    optionDisEraseFlash = new QCheckBox(tr("Disable flash erase (-D)"));
    optionErase = new QCheckBox(tr("Erase flash and EEPROM (-e)"));
    optionNWrite = new QCheckBox(tr("Do not Write (-n)"));
    QLabel *optionVerbosityLabel  = new QLabel(tr("Verbosity"));
    optionVerbosityCB = new QComboBox();
    QHBoxLayout *verbosityLayout = new QHBoxLayout;
    verbosityLayout->addWidget(optionVerbosityLabel);
    verbosityLayout->addWidget(optionVerbosityCB);
    QGridLayout *optionLayout = new QGridLayout;
    optionLayout->addWidget(optionForce,0,0);
    optionLayout->addWidget(optionErase,0,1);
    optionLayout->addWidget(optionDisVerify,1,0);
    optionLayout->addWidget(optionNWrite,1,1);
    optionLayout->addWidget(optionDisEraseFlash,2,0);
    optionLayout->addLayout(verbosityLayout,2,1);
    optionGroup->setLayout(optionLayout);

    //the preset groupbox
    QGroupBox *presetGroup = new QGroupBox(tr("Presets"));
    presetCB  = new QComboBox();
    presetSaveBtn = new QPushButton(tr("Save"));
    presetDeleteBtn = new QPushButton(tr("Delete"));
    QHBoxLayout *presetBtnLayout = new QHBoxLayout();
    presetBtnLayout->addWidget(presetSaveBtn);
    presetBtnLayout->addWidget(presetDeleteBtn);
    QVBoxLayout *presetLayout = new QVBoxLayout;
    presetLayout->addWidget(presetCB);
    presetLayout->addLayout(presetBtnLayout);
    presetGroup->setLayout(presetLayout);

    //the fuse & lock bits groupbox
    QGroupBox *fuseGroup = new QGroupBox(tr("Fuses and lock bits"));
    QLabel *lLabel = new QLabel(tr("L"));
    QLabel *hLabel = new QLabel(tr("H"));
    QLabel *eLabel = new QLabel(tr("E"));
    QLabel *lbLabel = new QLabel(tr("LB"));
    fuseLEdit = new QLineEdit();
    fuseHEdit = new QLineEdit();
    fuseEEdit = new QLineEdit();
    lockBitEdit = new QLineEdit();
    fuseReadBtn = new QPushButton(tr("Read"));
    fuseWriteBtn = new QPushButton(tr("Write"));
    fuseSetCheckBox = new QCheckBox(tr("Set fuses"));
    fuseSetLinkBtn = new QPushButton(tr("Fuse settings help"));
    lockBitReadBtn = new QPushButton(tr("Read"));
    lockBitWriteBtn = new QPushButton(tr("Write"));
    lockBitSetCheckBox = new QCheckBox(tr("Set lock"));
    bitSelectorBtn = new QPushButton(tr("Bit selector"));
    QGridLayout  *fuseLayout = new QGridLayout;
    fuseLayout->addWidget(lLabel,0,0);
    fuseLayout->addWidget(fuseLEdit,0,1);
    fuseLayout->addWidget(fuseReadBtn,0,2);
    fuseLayout->addWidget(fuseWriteBtn,0,3);
    fuseLayout->addWidget(hLabel,1,0);
    fuseLayout->addWidget(fuseHEdit,1,1);
    fuseLayout->addWidget(fuseSetCheckBox,1,2,1,2);
    fuseLayout->addWidget(eLabel,2,0,1,1);
    fuseLayout->addWidget(fuseEEdit,2,1,1,1);
    fuseLayout->addWidget(fuseSetLinkBtn,2,2,1,2);
    fuseLayout->addWidget(lbLabel,3,0,1,1);
    fuseLayout->addWidget(lockBitEdit,3,1,1,1);
    fuseLayout->addWidget(lockBitReadBtn,3,2,1,1);
    fuseLayout->addWidget(lockBitWriteBtn,3,3,1,1);
    fuseLayout->addWidget(lockBitSetCheckBox,4,2,1,1);
    fuseLayout->addWidget(bitSelectorBtn,5,0,1,4);
    fuseGroup->setLayout(fuseLayout);

    //the additional settings group
    QGroupBox *additionSetGroup = new QGroupBox(tr("Additional settings"));
    additionSetEdit = new QLineEdit();
    QVBoxLayout *additionLayout = new QVBoxLayout;
    //additionLayout->addStretch();
    additionLayout->addWidget(additionSetEdit);
    additionSetGroup->setLayout(additionLayout);

    //the action group
    programBtn = new QPushButton(tr("Program!"));
    stopBtn = new QPushButton(tr("Stop"));
    aboutBtn = new QPushButton(tr("?"));
    commandEdit = new QLineEdit();
    optionBtn = new QPushButton(tr("Option"));
    QHBoxLayout *actionBtnLayout = new QHBoxLayout;
    actionBtnLayout->addWidget(programBtn,1);
    actionBtnLayout->addWidget(stopBtn);
    actionBtnLayout->addWidget(optionBtn,1,Qt::AlignRight);
    actionBtnLayout->addWidget(aboutBtn,1,Qt::AlignRight);

    QVBoxLayout *actionGroupLayout = new QVBoxLayout;
    actionGroupLayout->addLayout(actionBtnLayout);
    actionGroupLayout->addWidget(commandEdit);

    //the output Group
    outputText = new QTextBrowser();
    outputText->setMinimumHeight(150);
    QGroupBox *outputGroup = new QGroupBox(tr("Output"));
    QVBoxLayout *outputLayout = new QVBoxLayout;
    outputLayout->addWidget(outputText);
    outputGroup->setLayout(outputLayout);


    //the main Layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(programmerGroup,0,0,1,2);
    mainLayout->addWidget(MCUGroup,0,2,1,1);
    mainLayout->addWidget(flashGroup,1,0,1,2);
    mainLayout->addWidget(presetGroup,1,2,1,1);
    mainLayout->addWidget(eepromGroup,2,0,1,2);
    mainLayout->addWidget(optionGroup,3,0,1,2);
    mainLayout->addWidget(fuseGroup,2,2,2,1);
    mainLayout->addLayout(actionGroupLayout,4,0,1,2);
    mainLayout->addWidget(additionSetGroup,4,2,1,1);
    mainLayout->addWidget(outputGroup,5,0,1,3);

    QWidget *mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    mainWidget->setLayout(mainLayout);
    this->setWindowTitle(tr("AVRDUDE Shell -- A GUI for avrdude"));
}

void MainWindow::showOpenFlashDialog()
{
    /*QFileDialog *openDialog=new QFileDialog(this,tr("Open Flash Hex File"));
    openDialog->setFilter(tr("Intel Hex Files(*.hex)"));
    if(openDialog->exec())
    {
        this->flashPathEdit->text()=openDialog->getOpenFileName();
    }*/

    flashPathEdit->setText(QFileDialog::getOpenFileName(this,tr("Open Hex File"),"..",tr("Intel Hex File(*.hex)")));
    //qDebug()<<QFileDialog::getOpenFileName(this,tr("Open Hex File"),"..",tr("Intel Hex File(*.hex)"));
}

void MainWindow::showOpenEEPDialog(void)
{
    /*QFileDialog *openDialog=new QFileDialog(this,tr("Open EEPROM Hex File"));
    openDialog->setFilter(tr("Intel Hex Files(*.hex)"));
    if(openDialog->exec()==QFileDialog::Accepted)
    {
        this->eepromPathEdit->text()=openDialog->getOpenFileName();
    }*/
    eepromPathEdit->setText(QFileDialog::getOpenFileName(this,tr("Open Hex File"),"..",tr("Intel Hex File(*.hex)")));

}
void MainWindow::slotReadStandardOutError()
{
    QString out = process->readAllStandardError();
    QString sp;
//    qDebug()<<endl;
//    qDebug()<<"sart the readStandardOutError";
//    qDebug()<<out;
    outputText->append(out);
    sp=parse(out,"=","\n",0);
    if(sp != "")
    qDebug()<<QString("Signature id is :%1").arg(sp);

//    QVariant v;
//    //this->outputText->append(QString("This is %1.").arg(index));
//    v=this->programmerCB->itemData(index);
//    PROGDEV p=v.value<PROGDEV>();
//    this->outputText->append(QString("ID:%1.\nDESC:%2.\nTYPE:%3.\n").arg(p.sID,p.sDesc,p.sType));
}
