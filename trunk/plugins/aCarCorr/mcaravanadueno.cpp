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
#include "mcaravanadueno.h"

#include <QStringList>

MCaravanaDueno::MCaravanaDueno(QObject *parent)
 : QAbstractTableModel(parent)
{
 setHeaderData( 0, Qt::Horizontal, "#ID" );
 setHeaderData( 1, Qt::Horizontal, "Codigo de Caravana" );
 setHeaderData( 2, Qt::Horizontal, "Dueño" );
}


MCaravanaDueno::~MCaravanaDueno()
{
}


bool MCaravanaDueno::setData( const QModelIndex& index, const QVariant& value, int role )
{
 if( !index.isValid() )
 {
  return false;
 }
 switch( index.column() )
 {
	case 0:
	{
		if( role == Qt::EditRole )
		{
			return false;
		}
		else
		{
			return false;
		}
		break;
	}
	// Codigo de la caravana
	case 1:
	{
		if( role == Qt::EditRole )
		{
			datos[index.row()].first = value.toString();
			emit dataChanged( index, index );
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
	//Dueño
	case 2:
	{
		if( role == Qt::EditRole )
		{
			datos[index.row()].second = value.toString();
			emit dataChanged( index, index );
			return true;
		}
		else
		{
			return false;
		}
		break;
	}
 	default:
	{
		return false;
		break;
	}
 }
}

bool MCaravanaDueno::removeRow( int row, const QModelIndex& parent )
{
 beginRemoveRows( parent, row, row );
 datos.remove( row );
 endRemoveRows();
 return true;
}

bool MCaravanaDueno::insertRow( int row, const QModelIndex& parent )
{
 beginInsertRows( parent, rowCount(), rowCount() );
 datos.insert( rowCount(), QPair<QString,QString>() );
 endInsertRows();
 return true;
}

Qt::ItemFlags MCaravanaDueno::flags( const QModelIndex& index ) const
{
  return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant MCaravanaDueno::data( const QModelIndex& index, int role ) const
{
 switch( index.column() )
 {
	case 0:
	{
		switch( role )
		{
			case Qt::DisplayRole:
			{
				return index.row();
				break;
			}
			default:
			{
				return QVariant();
				break;
			}
		}
		break;
	}
	// Codigo de la caravana
	case 1:
	{
		switch( role )
		{
			case Qt::DisplayRole:
			{
				return datos.value( index.row() ).first;
				break;
			}
			case Qt::EditRole:
			{
				return datos.value( index.row() ).first;
				break;
			}
			default:
			{
				return QVariant();
				break;
			}
		}
		break;	
	}
	case 2:
	{
		switch( role )
		{
			case Qt::DisplayRole:
			{
				return datos.value( index.row() ).second;
				break;
			}
			case Qt::EditRole:
			{
				return datos.value( index.row() ).second;
				break;
			}
			default:
			{
				return QVariant();
				break;
			}
		}
		break;	
	}
 	default:
	{
		return QVariant();
		break;
	}
 }
}

QModelIndex MCaravanaDueno::index( int row, int column, const QModelIndex &index ) const 
{
 if( row < rowCount()  && column < 3 )
 {
  return createIndex( row, column, row );
 }
 else
 { return QModelIndex(); }
}


int MCaravanaDueno::columnCount( const QModelIndex & parent ) const 
{ return 3; }

int MCaravanaDueno::rowCount ( const QModelIndex & parent ) const
{
 return datos.size();
}


/*!
    \fn MCaravanaDueno::listaCaravanas()
 */
QStringList MCaravanaDueno::listaCaravanas()
{
 QStringList l;
 for( int i = 0; i < rowCount(); i++ )
 {
  l.append( datos[i].first );
 }
 return l;
}


/*!
    \fn MCaravanaDueno::verificarAgregar( QString codigo )
 */
bool MCaravanaDueno::verificarAgregar( const QString &codigo, const QString &dueno )
{
 if( listaCaravanas().contains( codigo ) )
 {
  return false;
 }
 int anterior = rowCount();
 this->insertRow( -1 );
 this->setData( this->index( anterior, 1 ), codigo );
 this->setData( this->index( anterior, 2 ), dueno );
 return true;
}


/*!
    \fn MCaravanaDueno::verificarAgregar( QStringList &listado )
 */
bool MCaravanaDueno::verificarAgregar( const QStringList &listado, const QString &dueno )
{
 QString temp;
 foreach( temp, listado )
 {
  if( !verificarAgregar( temp, dueno ) )
  {
    return false;
  }
 }
 return true;
}


/*!
    \fn MCaravanaDueno::setDuenosTodos( const QString dueno )
 */
void MCaravanaDueno::setDuenosTodos( const QString &dueno )
{
///@todo implementar
}


/*!
    \fn MCaravanaDueno:::headerData ( int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const 
 */
QVariant MCaravanaDueno::headerData( int section, Qt::Orientation orientation, int role ) const 
{
 if( orientation == Qt::Horizontal )
 {
  switch( section )
  {
	case 1:
	{
		if( role == Qt::DisplayRole )
		{
			return "Codigo";
		}
		else
		{
			return QAbstractTableModel::headerData( section, orientation, role );
		}
		break;
	}
	case 2:
	{
		if( role == Qt::DisplayRole )
		{
			return "Dueño";
		}
		else
		{
			return QAbstractTableModel::headerData( section, orientation, role );
		}
		break;
	}
 	default:
	{
		return QAbstractTableModel::headerData( section, orientation, role );
		break;
	}
  }
 }
 else
 {
  return QAbstractTableModel::headerData( section, orientation, role );
 }
}
