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
#include "formnuevactacte.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlField>
#include <QSqlRelationalTableModel>

FormNuevaCtaCte::FormNuevaCtaCte ( QWidget* parent, Qt::WFlags fl )
 : QDialog( parent, fl ), Ui::FormCtaCteBase()
{
 setupUi ( this );
 this->setWindowTitle( "Agregar nueva cuenta corriente" );

 DEFechaAlta->setDate( QDate::currentDate() );

 // lleno el combo de los clientes sin cuenta corriente
 QSqlQuery cola( "SELECT id, razon_social FROM clientes WHERE id NOT IN ( SELECT id_cliente FROM ctacte )" );
 while( cola.next() )
 {
   CBCliente->insertItem( cola.record().value(0).toInt(), cola.record().value(1).toString(), cola.record().value(0) );
 }
 CBCliente->setSizeAdjustPolicy( QComboBox::AdjustToMinimumContentsLengthWithIcon );
 CBCliente->setCurrentIndex(-1);

 DEFechaBaja->setEnabled( CkBBaja->isChecked() );
 DSBLimiteMaximo->setEnabled( CkBBaja->isChecked() );
}

FormNuevaCtaCte::~FormNuevaCtaCte()
{
}

/*!
    \fn FormNuevaCtaCte::accept()
 */
void FormNuevaCtaCte::accept()
{
 //verificar los datos
 if( CBCliente->currentIndex() == -1 )
 { return; }
 if( LENumeroCuenta->text().isEmpty() )
 { return; }
 if( CkBBaja->isChecked() && DEFechaBaja->date().isValid() && DEFechaBaja->date() <= DEFechaAlta->date() )
 { return; }
 if( CkBLimiteMaximo->isChecked() && DSBLimiteMaximo->value() <= 0 )
 { return; }
 // Datos teoricamente correctos
 int id_cliente = CBCliente->itemData( CBCliente->currentIndex() ).toInt();
 qDebug( qPrintable( QString(  "id_cliente: %1" ).arg( id_cliente ) ) );
 modelo->setEditStrategy( QSqlTableModel::OnManualSubmit );
 QSqlRecord rec = modelo->record();
 for( int i = 0; i<rec.count(); i++ )
 {
  qDebug( qPrintable( QString::number( i ) + ": " + rec.field(i).name() ) );
 }
 rec.setValue( "id_cliente", id_cliente );
 rec.setValue( "numero_cuenta", LENumeroCuenta->text() );
 rec.setValue( "fecha_alta", DEFechaAlta->date() );
 if( CkBBaja->isChecked() )
 { rec.setValue( "fecha_baja", DEFechaBaja->date() );}
 else
 { rec.setNull( "fecha_baja" ); }
 if( CkBLimiteMaximo->isChecked() )
 { rec.setValue( "limite", DSBLimiteMaximo->value() ); }
 else
 { rec.setNull( "limite" ); }
 rec.setValue( "saldo", 0.0 );
 if( modelo->insertRecord( -1, rec ) )
 {
  if( modelo->submitAll() )
  {
   QMessageBox::information( this, "Listo", "Cuenta corriente agregada correctamente" );
   this->close();
   return;
  }
  else
  {
   qWarning( "Error al hacer el submit de datos" );
   qDebug( qPrintable( modelo->lastError().text() ) );
   qDebug( qPrintable( modelo->query().executedQuery() ) );
   return;
  }
 }
 else
 {
  qWarning( "Error al agregar el registro" );
  qDebug( qPrintable( modelo->lastError().text() ) );
  qDebug( qPrintable( modelo->query().executedQuery() ) );
  return;
 }
}


/*!
    \fn FormNuevaCtaCte::setModelo( QSqlRelationalTableModel *m )
 */
void FormNuevaCtaCte::setModelo( QSqlRelationalTableModel *m )
{
 if( m != 0 )
 { modelo = m; }
}
