/*
This file is part of KSTM.
KSTM is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
any later version.

KSTM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with KSTM.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "core.h"
#include <QtWidgets/QSystemTrayIcon>
#include <QList>
#include <QProcess>

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<kstm::connection*> connections;
private slots:
    void on_actionConnect_triggered();
    void on_listWidget_currentRowChanged(int currentRow);
    void on_actionDelete_triggered();
    void on_actionEdit_triggered();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void connectionFinished();
    void on_actionAbout_KSTM_triggered();
    void on_actionNew_triggered();
private:
    void loadConnections();
    void saveConnections();
    void readConnections();
    Ui::MainWindowClass *ui;
    QSystemTrayIcon *trayIcon;

};

#endif // MAINWINDOW_H
