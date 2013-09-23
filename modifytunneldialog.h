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
#ifndef MODIFYTUNNELDIALOG_H
#define MODIFYTUNNELDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>
#include "core.h"

namespace Ui {
    class modifyTunnelDialog;
}

class modifyTunnelDialog : public QDialog {
    Q_OBJECT
public:
    modifyTunnelDialog(QWidget *parent = 0);
    ~modifyTunnelDialog();
    void loadTunnel(kstm::tunnel Tunnel);
    kstm::tunnel tunnel;
protected:
    void changeEvent(QEvent *e);
    void accept();

private:
    Ui::modifyTunnelDialog *m_ui;
};

#endif // MODIFYTUNNELDIALOG_H
