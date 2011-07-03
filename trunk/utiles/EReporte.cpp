/***************************************************************************
 *   Copyright (C) 2007 by Esteban Zeller   				   *
 *   juiraze@yahoo.com.ar   						   *
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

#include "EReporte.h"
#include <QDir>
#include <QFile>
#include <QSqlDatabase>
#include <QSqlDriver>
#include "eregistroplugins.h"
#include <QApplication>
#include <QFile>
#include <QDomDocument>

EReporte::EReporte( QObject *padre )
    : QObject() {
    this->setParent( padre );
    _tipo = EReporte::Invalido;
}

EReporte::EReporte( QObject *padre, QString nombre_reporte, ParameterList parametros )
    : QObject() {
    this->setParent( padre );
    especial( nombre_reporte, parametros );
    _parametros = parametros;
}

/*!
 * \fn EReporte::hacer( ParameterList parametros, bool previsualizar )
 * Realiza el reporte configurado.
 * Si no se definieron parametros, se tomarán los parametros definidos en el objeto.
 * Se solicitará al plugin de el cliente que coloque los parametros que considere necesarios.
 * Luego se enviará a imprimir el reporte.
 * Si es un presupuesto o un recibo, se lo intentará guardar en el deposito de documentos.
 * \param parametros Objeto del tipo "ParameterList" con los parametros para el reporte
 * \returns Verdadero si se pudo imprimir. Falso si hubo un error de configuración o al imprimir.
 */
bool EReporte::hacer( ParameterList parametros, bool previsualizar ) {
    if( _rep == 0 || ( !_rep->isValid() ) || _tipo == Invalido || _nombre.isNull() ) {
        qDebug( "Error - Reporte no inicializado o erroneo" );
        return false;
    }
    // Busco las modificaciónes que se le quieran hacer a los reportes
    if( !parametros.isEmpty() ) {
        _parametros = parametros;
    }
    ERegistroPlugins::getInstancia()->pluginInfo()->reporteParametros( _tipo, _nombre, _parametros );

    _rep->setParamList( _parametros );
    // Imprimo el reporte
    /// @todo Ver si poner impresora para cada tipo
    if( !( _rep->print( 0, true, previsualizar ) ) ) {
        qDebug( "Error al intentar imprimir el reporte o se cancelo" );
        _rep->reportError( 0 );
        return false;
    }

    if( _tipo == EReporte::Presupuesto || _tipo == EReporte::Recibo ) {
        // Guardo el documento en la carpeta si corresponde
        QDir dir = QApplication::applicationDirPath();
        dir.cd( "reportes" );
        if( !dir.exists( "deposito" ) ) {
            if( !dir.mkdir( "deposito" ) ) {
                qDebug( "Error al intentar crear el directorio de deposito" );
            }
        }
        dir.cd( "deposito" );
        if( ! _rep->exportToPDF( "recibo" ) ) {
            qDebug( "Error al guardar el reporte en el directorio." );
        }
    }
    return true;

}

/*!
 * \fn EReporte::especial( const QString nombre, ParameterList parametros )
 * Realiza el reporte que es pasado como nombre, con los parametros seleccionados.
 * \param nombre Nombre del reporte a cargar.
 * \param parametros Objeto del tipo "ParameterList" con los parametros para el reporte
 * \returns Verdadero si se pudo cargar.
 */
bool EReporte::especial( const QString nombre, ParameterList parametros ) {
    if( nombre.isNull() ) {
        qDebug( "Error - nombre del reporte especial nulo." );
        return false;
    }
    _tipo = EReporte::Especial;
    // Si es especial tiene que cargarlo con el nombre indicado
    this->_parametros = parametros;
    _nombre = nombre;
    return cargar( nombre );
}

/*!
 * \fn EReporte::presupuesto()
 * Carga el reporte de presupuesto definido por el plugin de información del cliente.
 */
void EReporte::presupuesto() {
    _tipo = EReporte::Presupuesto;
    // Busco el tipo de presupuesto que se desea
#ifdef Q_OS_LINUX
    _nombre = ERegistroPlugins::getInstancia()->pluginInfo()->reporte( _tipo );
#else
    _nombre = "Presupuesto";
#endif
    // Cargo el reporte
    cargar( _nombre );
}

/*!
 * \fn EReporte::factura()
 * Carga el reporte de factura definido por el plugin de información del cliente.
 */
void EReporte::factura() {
    _tipo = EReporte::Factura;
    // Busco el tipo de presupuesto que se desea
#ifdef Q_OS_LINUX
    _nombre = ERegistroPlugins::getInstancia()->pluginInfo()->reporte( _tipo );
#else
    _nombre = "Factura";
#endif
    // Cargo el reporte
    cargar( _nombre );
}

/*!
 * \fn EReporte::recibo()
 * Carga el reporte de recibo definido por el plugin de información del cliente.
 */
void EReporte::recibo() {
    _tipo = EReporte::Recibo;
    // Busco el tipo de presupuesto que se desea
#ifdef Q_OS_LINUX
    _nombre = ERegistroPlugins::getInstancia()->pluginInfo()->reporte( _tipo );
#else
    _nombre = "Recibo";
#endif
    // Cargo el reporte
    cargar( _nombre );
}

/*!
 * \fn EReporte::cargar( const QString nombre )
 * Carga el reporte que es pasado como parametro.
 * Si la base de datos cargado es SQLite intentará cargarlo desde la carpeta QApplication::applicationDirPath() / reportes.
 * El nombre de archivo buscado será <nombre>.xml.
 * Si la base de datos cargada no es SQLite, se intentará cargar los reportes desde la tabla "report" dentro de las tablas.
 * El nombre del reporte deberá conincidir con el "report_name" de la tabla. Siempre se intentará cargar el numero de reporte mas alto.
 * \param nombre Nombre del reporte que se desea cargar.
 */
bool EReporte::cargar( const QString nombre ) {
    if( QSqlDatabase::database( QSqlDatabase::defaultConnection, false ).driverName() == "QSQLITE" ) {
        // Tiene que estar en un archio xml guardado en un directorio
        QDir reporte = QApplication::applicationDirPath();
        if( ! reporte.cd( "reportes" ) ) {
            qDebug( "No se pudo ingresar al directorio de reportes" );
            return false;
        }
        // busco el nombre de archivo
        QString ruta = reporte.absoluteFilePath( nombre + ".xml" );
        if( QFile::exists( ruta ) ) {
            // Cargo el archivo como dato
            qDebug( QString( "Cargando archivo %1" ).arg( ruta ).toLocal8Bit() );
            // La librería no soporta archivos como parametro
            QDomDocument *doc = new QDomDocument(_nombre);
            QFile archivo(ruta);
            if(!archivo.open(QIODevice::ReadOnly)) {
                qDebug( "Error al intentar abrir el archivo como solo lectura" );
                return false;
            }
            if( !doc->setContent( &archivo ) ) {
                archivo.close();
                qDebug( "Error al insertar el contenido del archivo en el documento DOM" );
                return false;
            }
            archivo.close();
            _rep = new orReport();
            if( !_rep->setDom( *doc ) ) {
                qDebug( "Error al setear el contenido del reporte con el documento DOM" );
                return false;
            }
        } else {
            qDebug( QString( "Error - No se pudo cargar el reporte - No existe el archivo %1" ).arg( ruta ).toLocal8Bit() );
            return false;
        }
    } else {
        // Para otros tipos de base de datos podemos accederlo en la base de datos
        _rep = new orReport( nombre );
    }
    if( (!_rep == 0) && !_rep->isValid() ) {
        qDebug( "Error - el reporte solicitado no es valido" );
        _rep->reportError( 0 );
        return false;
    }
    return true;
}


void EReporte::mostrarError( QWidget *ventana) {
    if( _rep != 0 ) {
        _rep->reportError( ventana );
    }
}
