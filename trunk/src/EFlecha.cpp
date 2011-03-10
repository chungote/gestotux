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

#include "EFlecha.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPaintEngine>
#include "math.h"


EFlecha::EFlecha( QWidget *parent ) {
  this->setParent( parent );
}


EFlecha::EFlecha(QWidget *parent, QWidget *origen, QWidget *destino, int tamFlecha ) :
QWidget(parent), QLineF()
{
    this->setParent( parent );

    //this->setAutoFillBackground( false );

    this->origen = origen;
    this->move( this->origen->pos() );
    qDebug( "EFlecha: movido" );
    this->destino = destino;
    this->resize( this->destino->x() - this->pos().x(), this->destino->y() - this->pos().y() + 20 );
    qDebug( "EFlecha: Redimensionado" );
    this->tamFlecha = tamFlecha;
    qDebug( "EFlecha: Inicializado" );
    // Por ahora dibujo una flecha desde las esquinas
    this->p1().setX( origen->x() );
    this->p1().setY( origen->y() );
    this->p2().setX( destino->x() );
    this->p2().setY( destino->y() );
    // Seteo los puntos de la linea segun los widgets
    // busco que lado del rect esta mas cerca del otro widget
    //int difArAb = origen->rect().top().y() -
}

QSize EFlecha::sizeHint() const
{
    if( this->origen == 0 || this->destino == 0 ) {
        return QSize( 0, 0 );
    } else {
        return QRect( this->p1().toPoint(), this->p2().toPoint() ).size();
    }
}

void EFlecha::setearOrigen( QWidget *origen ) {
  this->origen = origen;
  this->p1().setX( origen->x() );
  this->p1().setY( origen->y() );
}

void EFlecha::setearDestino( QWidget *destino ) {
  this->destino = destino;
  this->p2().setX( destino->x() );
  this->p2().setY( destino->y() );
}

void EFlecha::setearTamFlecha( int tam )
{ this->tamFlecha = tam; }


void EFlecha::paintEvent( QPaintEvent *evento )
{
    (void)evento;
    this->setP1( QPointF( 10, 50 ) );
    this->setP2( QPointF( 100, 50 ) );
    tamFlecha = 20;
    QPoint f1;
    double tangente = atan2( (double)( p2().y() - p1().y() ), (double) ( p2().x() - p1().x() ) );

    /*qDebug( QString( "f1x = %1 ").arg( tamFlecha * cos( M_PI * ( 3.0 / 4.0 ) ) ).toLocal8Bit() );
    qDebug( QString( "f1y = %1 ").arg( tamFlecha * sin( M_PI * ( 3.0 / 4.0 ) ) ).toLocal8Bit() );
    qDebug( QString( "difx = %1 ").arg( ( p2().x() - p1().x() ) ).toLocal8Bit() );
    qDebug( QString( "dify = %1 ").arg( ( p2().y() - p1().y() ) ).toLocal8Bit() );
    qDebug( QString( "sin1 = %1 ").arg( sin( M_PI * ( 3.0 / 4.0 ) ) ).toLocal8Bit() );
    qDebug( QString( "sin2 = %1 ").arg( sin( M_PI * ( 5.0 / 4.0 ) ) ).toLocal8Bit() );
    qDebug( QString( "tangente = %1 ").arg( tangente ).toLocal8Bit() );*/

    f1.setX( tamFlecha * cos( M_PI * ( 3.0 / 4.0 ) ) );
    f1.setY( tamFlecha * sin( M_PI * ( 3.0 / 4.0 ) ) );

    QPainter p(this);
    p.setPen( Qt::yellow );
    p.drawLine( this->p1(), this->p2() );
     p.save();
     p.setPen( Qt::red );
     // Me muevo a la punta de la flecha
     p.translate( p2().x(), p2().y() );
     p.save();
      // Me muevo el angulo de la linea ( esta en radianes )
      p.rotate( ( tangente * 180 ) / M_PI );
      p.drawLine( QPointF( 0, 0 ), f1 );
       //p.save();
       // Giro 90 grados
       p.rotate( ( 90.0 * 180 ) / M_PI );
       p.setPen( Qt::blue );
       //qDebug( QString( "f1 x = %1 y=%2 ").arg( f1.x() ).arg( f1.y() ).toLocal8Bit() );
       p.drawLine( QPointF( 0, 0 ), f1 );

     // p.restore();
     p.restore();
    p.restore();
    // fin
}
