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
        qDebug( QString( "Cargando Documentacion desde: %1").arg(QApplication::applicationDirPath() + QDir::separator() + "documentacion.qch").toLocal8Bit());
        engine = new QHelpEngineCore( QApplication::applicationDirPath() + QDir::separator() + "documentacion.qch", parent );
        connect( engine, SIGNAL( setupStarted() ), this, SLOT( inicioConstruccion() ) );
        connect( engine, SIGNAL( setupFinished() ), this, SLOT( finConstruccion() ) );
        if( !engine->setupData() )
        {
                qWarning( QString( "Error al cargar la documentacion:  %1" ).arg( engine->error() ).toLocal8Bit().constData() );
        } else {
            qDebug( QString( "Documentacion cargada desde %1. OK!" ).arg( engine->collectionFile() ).toLocal8Bit() );
        }
        connect( engine, SIGNAL( warning( const QString & ) ), this, SLOT( errorEngine( const QString & ) ) );
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
    Devuelve verdadero si hay una entrada para el identificador pasado como parametro.
    El identificador generamente puede ser padre::hijo linkeado en la doc.
    @param nombreObjeto Identificador a buscar en la ayuda.
    @return Verdadero si se encontro.
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
    \fn EAyuda::mostrarAyuda( QString nombreObjeto )
    Abre la ventana de ayuda mostrando el contenido de la ayuda traida para el identificador pasado como parametro.
    @param nombreObjeto Objeto de referencia del cual se desea mostrar la ayuda
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
    Muestra la pagina inicial de la documentación de usuario
 */
void EAyuda::mostrarIndice()
{
 if( hayAyuda( "indice" ) )
 {
  mostrarAyuda( "indice" );
 }
}


/*!
  \fn EAyuda::errorEngine( const QString mensaje )
  Muestra el mensaje que tira el engine de la ayuda por salida normal
*/
void EAyuda::errorEngine( const QString &mensaje )
{
    qDebug( mensaje.toLocal8Bit() );
    qWarning( "Error de documentacion reportado." );
}

/*!
  \fn EAyuda::inicioConstruccion()
  Muestra el mensaje que tira el engine de la ayuda por salida normal
*/
void EAyuda::inicioConstruccion()
{ qDebug( "Inicio de construccion de la documentacion." ); }


void EAyuda::finConstruccion()
{ qDebug( "Fin de la construccion de la documentacion" ); }

