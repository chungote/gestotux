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
#include "drecibo.h"
#include <QCheckBox>
#include <QPainter>
#include <math.h>
#include <QPolygonF>

DRecibo::DRecibo(QObject *parent)
 : QSqlRelationalDelegate(parent)
{
    starPolygon << QPointF(1.0, 0.5);
    for (int i = 1; i < 5; ++i)
        starPolygon << QPointF(0.5 + 0.5 * cos(0.8 * i * 3.14),
                               0.5 + 0.5 * sin(0.8 * i * 3.14));
    diamondPolygon << QPointF(0.4, 0.5) << QPointF(0.5, 0.4)
                   << QPointF(0.6, 0.5) << QPointF(0.5, 0.6)
                   << QPointF(0.4, 0.5);
}


DRecibo::~DRecibo()
{
}


const int PaintingScaleFactor = 20;

/*!
    \fn DRecibo::QWidget * createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
 */
QWidget * DRecibo::createEditor( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
 switch( index.column() )
 {
  case 6:
  case 7:
  {
   QCheckBox *box = new QCheckBox( parent );
   box->setTristate( false );
   if( index.column() == 6 )
   {
    box->setText( "¿Contado?" );
   }
   else
   {
    box->setText( "¿Cuenta Corriente?" );
   }
   return box;
   break;
  }
  case 2:
  {
	QComboBox *combo = new QComboBox( parent );
	combo->addItem( "Ninguno", -1 );
	QLocale locale;
	for( int i=1; i<=12; i++ )
	{
		combo->addItem( locale.monthName( i ), i );
	}
	return combo;
  }
  default:
  {
   return QSqlRelationalDelegate::createEditor( parent, option, index );
   break;
  }
 }
}


/*!
    \fn DRecibo::void setEditorData ( QWidget * editor, const QModelIndex & index ) const
 */
void DRecibo::setEditorData( QWidget * editor, const QModelIndex & index ) const
{
 switch( index.column() )
 {
  case 6:
  case 7:
  {
   QCheckBox *box = qobject_cast<QCheckBox *>(editor);
   if( index.data( Qt::DisplayRole ).toBool() )
   {
    box->setCheckState( Qt::Checked );
   }
   else
   {
    box->setCheckState( Qt::Unchecked );
   }
   break;
  }
  case 2:
  {
	QComboBox *combo = qobject_cast<QComboBox *>(editor);
	if( index.data().toInt() == -1 )
	{
		combo->setCurrentIndex( 0 );
	}
	else
	{
		combo->setCurrentIndex( index.data().toInt() );
	}
	break;
  }
  default:
  {
   QSqlRelationalDelegate::setEditorData( editor, index );
   break;
  }
 }
}


/*!
    \fn DRecibo::void setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const
 */
void DRecibo::setModelData ( QWidget * editor, QAbstractItemModel * model, const QModelIndex & index ) const
{
 switch( index.column() )
 {
  case 6:
  case 7:
  {
   QCheckBox *box = qobject_cast<QCheckBox *>(editor);
   if( box->checkState() == Qt::Checked )
   {
    model->setData( index, true );
   }
   else
   {
    model->setData( index, false );
   }
   break;
  }
  case 2:
  {
	QComboBox *combo = qobject_cast<QComboBox *>(editor);
	if( combo->currentIndex() == 0 )
	{
		model->setData( index, -1 );
	}
	else
	{
		model->setData( index, combo->itemData ( combo->currentIndex() ) );
	}
	break;
  }
  default:
  {
   QSqlRelationalDelegate::setModelData( editor, model, index );
   break;
  }
 }
}


/*!
    \fn DRecibo::paint(QPainter *painter, const QStyleOptionViewItem &option,  const QModelIndex &index) const
 */
void DRecibo::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  switch( index.column() )
 {
  case 6:
  case 7:
  {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);
    painter->setBackgroundMode( Qt::TransparentMode );

    if( option.state & QStyle::State_Selected )
    {
	painter->setBrush( option.palette.alternateBase() );
        painter->fillRect(option.rect, option.palette.highlight());
    }
    else
    {
	painter->setBrush( option.palette.highlight() );
    }
    int yOffset = ( option.rect.height() - PaintingScaleFactor ) / 2;
    int xOffset = ( option.rect.width() - PaintingScaleFactor ) / 2;
    painter->translate( option.rect.x() + xOffset, option.rect.y() + yOffset);
    painter->scale( PaintingScaleFactor, PaintingScaleFactor);

    if ( index.data(Qt::DisplayRole).toBool() ) {
            painter->drawPolygon( starPolygon, Qt::WindingFill );
        } else {
            painter->drawPolygon( diamondPolygon, Qt::WindingFill );
        }
    painter->translate(1.0, 0.0);
    painter->restore();
   break;
  }
  default:
  {
   QSqlRelationalDelegate::paint(painter, option, index);
   break;
  }
 }
}


/*!
    \fn DRecibo::sizeHint(const QStyleOptionViewItem &option,
 const QModelIndex &index) const
 */
QSize DRecibo::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
  switch( index.column() )
 {
  case 6:
  case 7:
  {
    return PaintingScaleFactor * QSize( 1, 1 );
    break;
  }
  default:
  {
   return QSqlRelationalDelegate::sizeHint( option, index );
   break;
  }
 }
}
