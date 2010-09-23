/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   *
 *   juiraze@yahoo.com.ar   *
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
#include "eayuda.h"
#include <QHelpEngineCore>

EAyuda *EAyuda::yo = 0;

EAyuda::EAyuda(QWidget* parent, Qt::WFlags fl)
: QWidget( parent, fl ), Ui::EAyudaBase()
{
        setupUi(this);
        engine = new QHelpEngineCore( QApplication::applicationDirPath() + QDir::separator() + "docs.qch", parent );
        if( !engine->setupData() )
        {
                qWarning( QString( "Error al cargar la documentacion:  %1" ).arg( engine->error() ).toLocal8Bit().constData() );
        }
        PBCerrar->setIcon( QIcon( ":/imagenes/fileclose.png" ) );
        this->setVisible(false);
        connect( PBCerrar, SIGNAL( clicked() ), this, SLOT( hide() ) );
        this->setWindowTitle( "Ayuda" );
}

EAyuda::~EAyuda()
{
 if( engine != 0 )
 {
  delete engine;
 }
}

/*!
    \fn EAyuda::hayAyuda( QString nombreObjeto )
 */
bool EAyuda::hayAyuda( QString nombreObjeto )
{
 qWarning( QString( "Pedida documentacion para: %1" ).arg( nombreObjeto ).toLocal8Bit().constData() );
 if( engine->linksForIdentifier( nombreObjeto ).count() > 0 )
 {
        return true;
 }
 else
 {
        qWarning( qPrintable( "Documentacion no encontrada: " + nombreObjeto + ": " + QString::number( engine->linksForIdentifier( nombreObjeto ).count() ) ) );
        return false;
 }
}


/*!
    \fn EAyuda::mostrarAyuda( QString nombreObjecto )
 */
void EAyuda::mostrarAyuda( QString nombreObjecto )
{
 // Estamos seguros que hay datos para este objeto
 QByteArray helpData = engine->fileData(engine->linksForIdentifier( nombreObjecto ).constBegin().value());
 // Muestro la documentación al usuario
 if ( !helpData.isEmpty() )
 {
   textBrowser->setHtml( helpData );
   this->setVisible( true );
 }
 else
 {
   qWarning( "No se encontro documentación para este link" );
 }
 this->setVisible( true );
}


/*!
    \fn EAyuda::instancia()
 */
EAyuda* EAyuda::instancia()
{
 if( yo == 0 )
 {
  yo = new EAyuda();
 }
 return yo;
}


/*!
    \fn EAyuda::mostrarIndice()
 */
void EAyuda::mostrarIndice()
{
 if( hayAyuda( "index" ) )
 {
  mostrarAyuda( "index" );
 }
}
