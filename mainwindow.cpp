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
#include "mainwindow.h"
#include "modifydialog.h"
#include "aboutdialog.h"
#include "ui_mainwindow.h"
#include <QtWidgets/QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
    //System tray icon
    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QIcon("icons/kstm.png"));
    trayIcon->show();
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    //We add some connections for testing
    readConnections();
    loadConnections();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadConnections() //Loads the UI list
{
    ui->listWidget->clear();
    for (int i = 0; i < connections.size(); ++i)
    {
        ui->listWidget->addItem((connections.operator [](i))->getAlias());
    }
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}
void MainWindow::saveConnections()
{
    QFile file(QDir::homePath() + "/.kstm.xml");
    if (file.open(QFile::WriteOnly | QFile::Text))
    {
        kstm::configWriter writer(connections);
        writer.writeFile(&file);
    }
}
void MainWindow::readConnections()
{
    QFile file(QDir::homePath() + "/.kstm.xml");
    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        kstm::configReader reader(&connections);
        reader.readFile(&file);
    }
    loadConnections();
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason) //When systrayicon is clicked we show the main window.
{
    if(this->isHidden())
    {
        this->show();
    }
    else
    {
        this->hide();
    }
}
void MainWindow::connectionFinished()
{
    on_listWidget_currentRowChanged(ui->listWidget->currentRow());
}
void MainWindow::on_actionNew_triggered()
{
    modifyDialog dialog;
    dialog.exec();
    if (dialog.result() == modifyDialog::Accepted)
    {
        kstm::connection *tmpConnection = new kstm::connection("new");
        connect(&tmpConnection->proc, SIGNAL(readChannelFinished()), this, SLOT(connectionFinished()));
        dialog.commitConnection(*tmpConnection);
        connections.operator <<(tmpConnection);
    }
    loadConnections();
    saveConnections();
}
void MainWindow::on_actionEdit_triggered()
{
    if (ui->listWidget->currentRow() != -1) //We check if there is something selected on the list
    {
        modifyDialog dialog;
        dialog.loadConnection(*connections.operator [](ui->listWidget->currentRow()));
        dialog.exec();
        if (dialog.result() == modifyDialog::Accepted)
        {
            dialog.commitConnection(*connections.operator [](ui->listWidget->currentRow()));
        }
        loadConnections();
    }
    saveConnections();
}
void MainWindow::on_actionDelete_triggered()
{
    if (ui->listWidget->currentRow() != -1) //We check if there is something selected on the list
    {
        QMessageBox msgbox;
        msgbox.setText("Are you sure do you want to delete this connection?");
        msgbox.setWindowTitle("Delete connection...");
        msgbox.addButton(QMessageBox::Yes);
        msgbox.addButton(QMessageBox::No);
        msgbox.exec();
        if (msgbox.result() == QMessageBox::Yes) //If the dialog is accepted, then we replace the tunnel
        {
            connections.removeAt(ui->listWidget->currentRow());
            loadConnections();
        }
    }
}
void MainWindow::on_actionAbout_KSTM_triggered()
{
    aboutDialog dialog;
    dialog.exec();
}
void MainWindow::on_actionConnect_triggered()
{
    if (ui->listWidget->currentRow() != -1) //We check if there is something selected on the list
    {
        if ((connections.operator [](ui->listWidget->currentRow()))->proc.isOpen())
        {
            (connections.operator [](ui->listWidget->currentRow()))->disconnectssh(false);
        }
        else
        {
            (connections.operator [](ui->listWidget->currentRow()))->connectssh();
        }
        on_listWidget_currentRowChanged(ui->listWidget->currentRow());
    }
}
void MainWindow::on_listWidget_currentRowChanged(int currentRow) //depending on selected connection, actions are disabled or enabled
{
    if (ui->listWidget->currentRow() == -1)
    {
        ui->actionConnect->setEnabled(false);
        ui->actionDelete->setEnabled(false);
        ui->actionEdit->setEnabled(false);
        ui->label_command->setText("");
    }
    else
    {
        ui->actionConnect->setEnabled(true);
        ui->label_command->setText((connections.operator [](ui->listWidget->currentRow()))->getConnectionString());
        if ((connections.operator [](ui->listWidget->currentRow()))->proc.isOpen())
        {
            ui->actionConnect->setChecked(true);
            ui->actionEdit->setEnabled(false);
            ui->actionDelete->setEnabled(false);
        }
        else
        {
            ui->actionConnect->setChecked(false);
            ui->actionEdit->setEnabled(true);
            ui->actionDelete->setEnabled(true);
        }
    }
}


