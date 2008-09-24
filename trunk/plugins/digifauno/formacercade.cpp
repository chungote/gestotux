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


#include "formacercade.h"

FormAcercaDe::FormAcercaDe(QWidget* parent)
: EVentana( parent ), Ui::FormAcercaDe()
{
	setupUi(this);
	connect( PBCerrar, SIGNAL( clicked() ), this, SLOT( close() ) );
	LImagen->setPixmap( QPixmap( ":/imagenes/icono.png" ) );

	label_2->setText(  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:13pt; font-weight:600;\">DigiFauno</span></p></body></html>" );
        label_4->setText( "Version 0.4" );
        label_3->setText( "DigiFauno es un programa desarrollado especificamente para Digifauno.\nRealizado bajo licencia GPL, completamente desarrollado con Software Libre.\nBasado en las librerias Qt.\n\nProgramador y Analista:\nEsteban Zeller <tranfuga_25s@hotmail.com>\n\nDocumentacion y Pruebas:\nDaniel Sequeria <daniels591@hotmail.com>" );
        PBCerrar->setText( "Cerrar" );

        nombre_ventana = "formacercaede";
        setNombreVentana( "Acerca de... " );
}

FormAcercaDe::~FormAcercaDe()
{
}

