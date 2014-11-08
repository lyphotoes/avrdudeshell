avrdudeshell
============

A GUI for avrdude by QT.
###编写软件的初衷
以前在windows下进行AVR开发用惯了GUI,虽然命令行的avrdude很好用,但是有时候命令行敲的手疼,so,why not avrdudess? 的确不可否认在windows下的avrdudess无可挑剔,但是自从用了ubuntu后,这个能用mono运行的exe程序很是难看,所以,模仿avrdudess的界面开始开发了这个叫做avrdudeshell的程序.
###软件实现
- 完全用QT编写,利用QProcess调用avrdude作后台.
- 考虑到功能更完善,打算用sqlite数据库保存avrdude.conf的数据.

