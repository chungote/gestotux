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
#include "dproductostotales.h"
#include <QLineEdit>
#include <QRegExpValidator>
#include <QMessageBox>
#include <QCompleter>
#include <QComboBox>
#include <QSqlQuery>
#include <QSqlRecord>
#include "edsbprecio.h"
#include "../plugins/productos/mproductos.h"
#include "preferencias.h"

DProductosTotales::DProductosTotales(QWidget *parent)
 : QItemDelegate(parent)
{
 setClipping( false );
 lista = 0;
}

void DProductosTotales::setearListaProductos( QMap<int, QString> *l )
{  lista = l;  }

QWidget* DProductosTotales::createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
 switch( index.column() )
 {
        // Cantidad
        case 0:
        {
           EDSBPrecio *e = new EDSBPrecio( parent );
           e->setRange( 0.0, 99999999.999 );
           e->setPrefix("");
           if( preferencias::getInstancia()->value( "Preferencias/Productos/Stock/limitar", false ).toBool() )
           {
             e->setMaximum( MProductos::stock( index.model()->data( index.model()->index( index.row(), 0 ), Qt::EditRole ).toInt() ) );
           }
           return e;
           break;
        }
        // Producto
        case 1:
        {
                /// @todo Agregar combobox que soporte codigos aqui tambien
                QComboBox *combo = new QComboBox( parent );
                // Rellenar los items
                if( !lista ) {
                    qWarning( "Error en la lista original de productos!" );
                    abort();
                }
                QMapIterator<int, QString> i(*lista);
                while (i.hasNext()) {
                     i.next();
                     combo->addItem( i.value(), i.key() );
                }
                combo->setSizeAdjustPolicy( QComboBox::AdjustToMinimumContentsLengthWithIcon );
                combo->setEditable( true );
                combo->completer()->setCompletionMode( QCompleter::PopupCompletion );
                return combo;
                break;
        }
        // Precio Unitario
        case 2:
        {
                EDSBPrecio *e = new EDSBPrecio( parent );
                e->setPrefix( "$" );
                e->setSingleStep( 1 );
                e->setRange( 0.00, 99999999.99 );
                return e;
                break;

        }
        default:
        {
                // Los demas no deben ser editables
                return QItemDelegate::createEditor(parent, option, index);
                break;
        }
 }
 return QItemDelegate::createEditor( parent, option, index );
}

void DProductosTotales::setEditorData(QWidget* editor, const QModelIndex& index) const
{
 switch( index.column() )
 {
        // Producto
        case 1:
        {
             QComboBox *combo = qobject_cast<QComboBox *>(editor);
             combo->setCurrentIndex( combo->findData(  index.model()->data(index, Qt::EditRole ).toInt() ) );
             break;
        }
        // Precio unitario y cantidad
        case 0:
        case 2:
        {
                EDSBPrecio *e = qobject_cast<EDSBPrecio *>( editor );
                e->setValue( index.data( Qt::EditRole ).toDouble() );
                break;
        }
        default:
        {
                // Los demas no deben ser editables
                return QItemDelegate::setEditorData( editor, index);
                break;
        }
 }
}

void DProductosTotales::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const
{
  switch( index.column() )
 {
        // Producto
        case 1:
        {
                QComboBox *combo = qobject_cast<QComboBox *>(editor);
                // Veo si tiene el dato de ser un producto, sino, lo agrego
                qDebug( "Verificando existencia real del producto!");
                if( combo->itemData( combo->currentIndex() ) == QVariant::Invalid )
                {
                    // Lo agrego en el modelo para que recarge despues
                    if( combo->itemText( combo->currentIndex() ).isEmpty() ) { return; }
                    qDebug( QString( "Agregando producto no existente: %1").arg( combo->currentText() ).toLocal8Bit() );
                    // Cuando se coloca algun nuevo producto que no estaba antes, se coloca con 1 en cantidad.
                    qobject_cast<MProductosTotales *>(model)->agregarNuevoProducto( 1, combo->itemText( combo->currentIndex() ) );
                    // No hago el set data ya que se hace automaticamente
                    //model->setData( index, valor_indice_nuevo );
                } else {
                    model->setData( index, combo->itemData( combo->currentIndex() ) );
                }
                break;
        }
        // Precio Unitario
        case 2:
        // Cantidad
        case 0:
        {
                EDSBPrecio *e = qobject_cast<EDSBPrecio *>( editor );
                model->setData( index, e->value() );
                break;
        }
        default:
        {
                // Los demas no deben ser editables
                return QItemDelegate::setEditorData( editor, index);
                break;
        }
 }
}

void DProductosTotales::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    QItemDelegate::updateEditorGeometry(editor, option, index);
}

void DProductosTotales::neceistoActualizarListaSlots( MProductosTotales *m )
{ lista = m->listaProductos(); }
