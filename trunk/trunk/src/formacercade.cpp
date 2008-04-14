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
#include "gestotux.h"
#include "einfoprogramainterface.h"

FormAcercaDe::FormAcercaDe(QWidget* parent)
: EVentana( parent ), Ui::FormAcercaDe()
{
 	this->setAttribute( Qt::WA_DeleteOnClose );
	setupUi(this);
	connect( PBCerrar, SIGNAL( clicked() ), this, SLOT( close() ) );
	LImagen->setPixmap( gestotux::pluginInfo()->iconoPrograma().pixmap( 100, 100 ) );

	label_2->setText(  "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\np, li { white-space: pre-wrap; }\n</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:13pt; font-weight:600;\">" + gestotux::pluginInfo()->nombrePrograma() + "</span></p></body></html>" );
        label_4->setText( QString( "Version %1" ).arg( gestotux::pluginInfo()->version() ) );
        label_3->setText( gestotux::pluginInfo()->nombrePrograma() + " es un programa desarrollado especificamente para " + gestotux::pluginInfo()->empresa() + ".\nRealizado bajo licencia GPL, completamente desarrollado con Software Libre.\nBasado en las librerias Qt.\n\nProgramador y Analista:\nEsteban Zeller <tranfuga_25s@hotmail.com>" );
        PBCerrar->setText( "Cerrar" );

        nombre_ventana = "formacercaede";
        setNombreVentana( "Acerca de... " );
}

FormAcercaDe::~FormAcercaDe()
{
}

