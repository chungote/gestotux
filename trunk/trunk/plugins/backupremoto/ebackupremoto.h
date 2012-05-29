/***************************************************************************
 *   Copyright (C) 2006 by Esteban Zeller & Daniel Sequeira		   *
 *   juiraze@yahoo.com.ar  - daniels@hotmail.com			   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef EBACKUP_H
#define EBACKUP_H

#include "eventana.h"
#include "ui_formBackupRemoto.h"

class QAction;
class QNetworkAccessManager;
class QNetworkReply;

/**
 *	\brief Clase de Copias de Seguridad
 *
 *	Genera, comprime y restaura a su estado original elementos del programa. Además permite enviar los datos a un servidor en internet.
 *
 *	@author Esteban Zeller <juiraze@yahoo.com.ar>
 */
class EBackupRemoto : public EVentana , private Ui_FormBackupRemotoBase
{
Q_OBJECT
public:
    EBackupRemoto( QWidget* parent = 0 );
    ~EBackupRemoto();
    void generarBackup();
    void restaurarBackup();

public slots:
    void iniciar();
    void detener();

signals:
    void cambiarDetener( bool estado );

protected slots:
    void respuesta( QNetworkReply * );

private:
       /*!
        * Variable para saber si se desea cortar el trabajo
        */
        bool _continuar;
       /*!
        * Accion para iniciar el backup
        */
        QAction *ActIniciar;
       /*!
        * Accion para cerrar la ventana
        */
        QAction *ActCerrar;
       /*!
        * Accion para la barra, de detener
        */
        QAction *ActDetener;

       /*!
        *
        */
        QNetworkAccessManager *manager;

       /*!
        *
        */
        QList<QNetworkReply *> lista;
    bool generar_db( bool estructura );
    bool ejecutarColas( QStringList colas );
};

#endif
