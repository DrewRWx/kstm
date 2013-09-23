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
#include "modifydialog.h"
#include "modifytunneldialog.h"
#include "ui_modifydialog.h"

modifyDialog::modifyDialog(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::modifyDialog)
{
    m_ui->setupUi(this);
}

modifyDialog::~modifyDialog()
{
    delete m_ui;
}

void modifyDialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void modifyDialog::accept()
{
    QString problems = "";
    if (m_ui->lineEdit_tunnel->text() == "")
    {
        problems = problems + "You have to specify a connection name.\n";
    }
    if (m_ui->lineEdit_hostname->text() == "")
    {
        problems = problems + "You have to provide a server hostname.\n";
    }
    if (m_ui->lineEdit_username->text() == "")
    {
        problems = problems + "You have to provide an user-name.\n";
    }
    if (m_ui->listWidget_tunnels->count() == 0)
    {
        problems = problems + "At least, you have to add one tunnel.\n";
    }
    if (problems == "")
    {
        done(1);
    }
    else
    {
        QMessageBox msgbox;
        msgbox.setText("Please, solve the following problems...");
        msgbox.setDetailedText(problems);
        msgbox.exec();
    }
}
void modifyDialog::loadTunnels() //Used to fill the listWidget of tunnels with modifyDialog::tunnels list
{
    m_ui->listWidget_tunnels->clear();
    for (int i = 0; i < tunnels.size(); ++i)
    {
        m_ui->listWidget_tunnels->addItem((tunnels.operator [](i)).getAlias());
    }
}
void modifyDialog::commitConnection(kstm::connection &Conn) //Remember that the parameter is a pointer.
{
    Conn.tunnels = tunnels;
    Conn.setAlias( m_ui->lineEdit_tunnel->text());
    Conn.setAllowRemote( m_ui->checkBox_remote->checkState());
    Conn.setHostname( m_ui->lineEdit_hostname->text());
    Conn.setUsername( m_ui->lineEdit_username->text());
    Conn.setPort( m_ui->spinBox_port->value());
}
void modifyDialog::loadConnection(kstm::connection &Conn)
{
    tunnels = Conn.tunnels;
    m_ui->lineEdit_hostname->setText(Conn.getHostname());
    m_ui->lineEdit_username->setText(Conn.getUsername());
    m_ui->lineEdit_tunnel->setText(Conn.getAlias());
    m_ui->checkBox_remote->setChecked(Conn.getAllowRemote());
    m_ui->spinBox_port->setValue(Conn.getPort());
    loadTunnels();
}

void modifyDialog::on_actionEdit_triggered()
{
    if (m_ui->listWidget_tunnels->currentRow() != -1) //We check if there is something selected on tunnel's list
    {
        modifyTunnelDialog dialog;
        dialog.loadTunnel(tunnels.operator [](m_ui->listWidget_tunnels->currentRow()));
        dialog.exec();
        if (dialog.result() == QDialog::Accepted) //If the dialog is accepted, then we replace the tunnel
        {
            tunnels.replace(m_ui->listWidget_tunnels->currentRow(),dialog.tunnel);
            loadTunnels(); //used to refresh the GUI list with the replaced tunnel
        }
    }
}

void modifyDialog::on_actionDelete_triggered()
{
    if (m_ui->listWidget_tunnels->currentRow() != -1) //We check if there is something selected on tunnel's list
    {
        QMessageBox msgbox;
        msgbox.setText("Are you sure do you want to delete this tunnel?");
        msgbox.setWindowTitle("Delete tunnel...");
        msgbox.addButton(QMessageBox::Yes);
        msgbox.addButton(QMessageBox::No);
        msgbox.exec();
        if (msgbox.result() == QMessageBox::Yes) //If the dialog is accepted, then we replace the tunnel
        {
            tunnels.removeAt(m_ui->listWidget_tunnels->currentRow());
            loadTunnels(); //used to refresh the GUI list with the replaced tunnel
        }
    }
}

void modifyDialog::on_actionAdd_triggered()
{
    modifyTunnelDialog dialog;
    dialog.loadTunnel(kstm::tunnel("New tunnel",8080,"localhost",80,kstm::tunnel::local));
    dialog.exec();
    if (dialog.result() == QDialog::Accepted) //If the dialog is accepted, then we replace the tunnel
    {
        tunnels.append(dialog.tunnel);
        loadTunnels(); //used to refresh the GUI list with the replaced tunnel
    }
}

void modifyDialog::on_listWidget_tunnels_currentRowChanged(int currentRow) //We update the details group, with the selected tunnel row.
{
    if (currentRow == -1)
    {
        m_ui->label_name->setText("");
        m_ui->label_type->setText("");
        m_ui->label_local->setText("");
        m_ui->label_target->setText("");
    }
    else
    {
        m_ui->label_name->setText((tunnels.operator [](currentRow)).getAlias());
        switch ((tunnels.operator [](currentRow)).getConnectionType())
        {
            case 0:
            {
                m_ui->label_type->setText("local");
                break;
            }
            case 1:
            {
                m_ui->label_type->setText("remote");
                break;
            }
            case 2:
            {
                m_ui->label_type->setText("dynamic");
                break;
            }
        }
        m_ui->label_local->setText(QString::number((tunnels.operator [](currentRow)).getPort()));
        m_ui->label_target->setText((tunnels.operator [](currentRow)).getHostname() + ":" + QString::number((tunnels.operator [](currentRow)).getToPort()));
    }
}
