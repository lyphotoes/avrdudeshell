//the programmer groupbox 
QGroupBox *programmerGroup = new QGroupBox(tr("Programmer(-c)"));
programmerCB = new QComboBox();
QLabel *portLabel = new QLabel(tr("Port (-P)"));
QLabel *baudRateLabel = new QLabel(tr("Baud rate (-b)"));
QLabel *bitClockLabel = new QLabel(tr("Bit clock (-B)"));
portCB = new QComboBox();
baudRateEdit = new QLineEdit();
bitClockCB = new QComboBox();
QGridLayout *programmerLayout = new QGridLayout();
programmerLayout->addWidget(programmerCB,0,0,3,1);
programmerLayout->addWidget(portLabel,1,0,1,1);
programmerLayout->addWidget(baudRateLabel,1,1,1,1);
programmerLayout->addWidget(bitClcokLabel,1,2,1,1);
programmerLayout->addWidget(portCB,2,0,1,1);
programmerLayout->addWidget(baudRateEdit,2,1,1,1);
programmerLayout->addWidget(bitClockCB,2,2,1,1);
programmerGroup->setLayout(programmerLayout);


//the MCU groupbox
QGroupBox *MCUGroup = new QGroupBox(tr("MCU (-p)"));
chipCB = new QComboBox();
chipDetectBtn = new QPushButton(tr("Detect"));
QVBoxLayout *MCULayout = new QVBoxLayout();
MCULayout->addWidget(chipCB);
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
flashGoBtn = new QRadioButton(tr("Go"));
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
optionForce = new QCheckBox(tr("Force(-F)"));
optionDisVerify = new QCheckBox(tr("Disable verify (-V)"));
optionDisEraseFlash = new QCheckBox(tr("Disable flash erase (-D)"));
optionErase = new QCheckBox(tr("Erase flash and EEPROM (-e)"));
optionNWrite = new QCheckBox(tr("Do not Write (-n)"));
QLabel *optionVerbosityLabel = QLabel(tr("Verbosity"));
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
QGroupBox *fuseGroup = new QGroupBox(tr("Fuses & lock bits"));
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
lockBitWriteBtn = new QPushButton(tr("Write));
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
QHBoxLayout *additionLayout = new QHBoxLayout;
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
actionBtnLayout->addWidget(aboutBtn,1,Qt::AlignRight);
actionBtnLayout->addWidget(optionBtn,1,Qt::AlignRight);
QVBoxLayout *actionGroupLayout = new QVBoxLayout;
actionGroupLayout->addLayout(actionBtnLayout);
actionGroupLayout->addWidget(commandEdit);

//the output Group
outputText = new QTextBrowser();
outputText->setMinimumHeight(300);
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
mainLayout->addWidget(additonSetGroup,4,2,1,1);
mainLayout->addWidget(outputGroup,5,0,1,3);

QWidget *mainWidget = new QWidget;
this->setCentralWidget(mainWidget);
mainWidget->setLayout(mainLayout);
this->setWindowTitle(tr("AVRDUDE Shell -- A GUI for avrdude"));
