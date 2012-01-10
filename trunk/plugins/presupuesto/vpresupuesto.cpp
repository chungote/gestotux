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
#include "vpresupuesto.h"
#include "mvpresupuestos.h"
#include <QTableView>
#include "formagregarpresupuesto.h"
#include "EReporte.h"
#include <QModelIndex>
#include <QModelIndexList>
#include <QMessageBox>

VPresupuesto::VPresupuesto(QWidget *parent)
 : EVLista(parent)
{
 setObjectName( "visorPresupuestos" );
 setWindowTitle( "Presupuestos Anteriores" );
 setWindowIcon( QIcon( ":/imagenes/anteriores.png" ) );
 modelo = new MVPresupuestos( this );
 vista->setModel( modelo );
 vista->hideColumn( 0 );
 vista->hideColumn( 5 );
 modelo->select();

 addAction( ActAgregar );
 addAction( ActModificar );
 addAction( ActEliminar );
 addAction( ActImprimir );
 addAction( ActPdf );
 addAction( ActCerrar );
}

void VPresupuesto::agregar()
{
 emit agregarVentana( new FormAgregarPresupuesto() );
 this->close();
}

void VPresupuesto::antes_de_insertar(int /*row*/, QSqlRecord& /*record*/)
{
}

void VPresupuesto::cerrar()
{
    EVLista::cerrar();
}

#include "mclientes.h"
void VPresupuesto::imprimir()
{
  // Veo que ID quiere reimprimir.
  QModelIndexList lista = vista->selectionModel()->selectedRows();
  if( lista.isEmpty() ) {
      QMessageBox::information( this, "Error", "Por favor, seleccione uno o mas presupuestos para reimprimir", QMessageBox::Ok );
      return;
  }
  EReporte *rep = new EReporte( 0 );
  rep->presupuesto();
  ParameterList *parametros = new ParameterList();
  foreach( QModelIndex idx, lista ) {
      parametros->clear();
      parametros->append( Parameter( "id_presupuesto", modelo->data( modelo->index( idx.row(), 0 ), Qt::EditRole ).toInt() ) );
      int id_cliente = modelo->data( modelo->index( idx.row(), 0 ), Qt::EditRole ).toInt();
      if( id_cliente < 0 ) {
          parametros->append( Parameter( "cliente_existe", false ) );
          //lista.append( Parameter( "direccion", LEDireccion->text() ) );
      } else if( id_cliente >= 0 ){
          parametros->append( Parameter( "cliente_existe", true ) );
          //lista.append( Parameter( "direccion", LEDireccion->text() ) );
          if( id_cliente > 0 )
              parametros->append( Parameter( "direccion", MClientes::direccionEntera( id_cliente ) ) );
      }
      if( !rep->hacer( *parametros ) ) {
          qDebug( "Error la intentar imprimir el reporte" );
      }
  }
  delete parametros;
  parametros = 0;
  delete rep;
  rep = 0;
}

void VPresupuesto::aPdf()
{
    // Veo que ID quiere reimprimir.
    QModelIndexList lista = vista->selectionModel()->selectedRows();
    if( lista.isEmpty() ) {
        QMessageBox::information( this, "Error", "Por favor, seleccione uno o mas presupuestos para reimprimir", QMessageBox::Ok );
        return;
    }
    EReporte *rep = new EReporte( 0 );
    rep->presupuesto();
    ParameterList *parametros = new ParameterList();
    foreach( QModelIndex idx, lista ) {
        parametros->clear();
        int id_presupuesto = modelo->data( modelo->index( idx.row(), 0 ), Qt::EditRole ).toInt() ;
        parametros->append( Parameter( "id_presupuesto", id_presupuesto ) );
        int id_cliente = modelo->data( modelo->index( idx.row(), 0 ), Qt::EditRole ).toInt();
        if( id_cliente < 0 ) {
            parametros->append( Parameter( "cliente_existe", false ) );
            //lista.append( Parameter( "direccion", LEDireccion->text() ) );
        } else if( id_cliente >= 0 ){
            parametros->append( Parameter( "cliente_existe", true ) );
            //lista.append( Parameter( "direccion", LEDireccion->text() ) );
            if( id_cliente > 0 )
                parametros->append( Parameter( "direccion", MClientes::direccionEntera( id_cliente ) ) );
        }
        if( !rep->hacerPDF( *parametros, QString( "Presupuesto #%1" ).arg( id_presupuesto ) ) ) {
            qDebug( "Error la intentar imprimir el reporte" );
        }
    }
    delete parametros;
    parametros = 0;
    delete rep;
    rep = 0;
}
