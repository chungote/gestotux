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
#include "NumeroComprobante.h"

#define CANT_DIGITOS 6

NumeroComprobante::NumeroComprobante( QObject *parent )
{
    this->setParent( parent );
    _dato.first = -1;
    _dato.second = -1;
}

NumeroComprobante::NumeroComprobante( QObject *parent, int serie, int numero )
{
    setParent( parent );
    _dato.first = serie;
    _dato.second = numero;
}

/*!
 * \fn NumeroComprobante::setearNumero( int numero )
 * Setea el numero de comprobante
 * @param Numero del comprobante
 */
void NumeroComprobante::setearNumero( int numero ) { _dato.second = numero; }
/*!
 * \fn NumeroComprobante::setearSerie( int serie )
 * Setea el numero de serie del comprobante
 * @param Numero del comprobante
 */
void NumeroComprobante::setearNumeroSerie( int serie ) { _dato.first = serie; }
/*!
 * \fn NumeroComprobante::serie() const
 * Devuelve el numero de serie del comprobante
 * @return numero de serie
 */
int NumeroComprobante::serie() const { return _dato.first; }
/*!
 * \fn NumeroComprobante::numero() const
 * Devuelve el numero  del comprobante
 * @return numero de Comprobante
 */
int NumeroComprobante::numero() const { return _dato.second; }
/*!
 * \fn NumeroComprobante::aCadena() const
 * Devuelve una cadena con <serie>-<numero> del comprobante
 * @return
 */
QString NumeroComprobante::aCadena() {
  return serieLleno() + "-" + numeroLleno();
}

QString NumeroComprobante::numeroLleno() {
  int llenar = CANT_DIGITOS - cuentaRecursivo( _dato.first );
  QString r;
  for( int i =0; i<llenar; i++ ) { r.append("0"); }
  r.append( QString::number( _dato.first ) );
  return r;
}

QString NumeroComprobante::serieLleno() {
    int llenar = CANT_DIGITOS - cuentaRecursivo( _dato.second );
    QString r;
    for( int i =0; i<llenar; i++ ) { r.append("0"); }
    r.append( QString::number( _dato.second ) );
    return r;
}

int NumeroComprobante::cuentaRecursivo( int dato ) {
    double temp = dato / 10.0;
    if( temp < 1 ) {
        return 0;
    } else {
        return cuentaRecursivo( (int) temp ) + 1;
    }
}

/*!
 * \fn NumeroComprobante::esValido() const
 * Devuelve si el numero es valido o no
 * @return verdadero o falso
 */
bool NumeroComprobante::esValido() const {
    if( _dato.first == -1 || _dato.second == -1 ) {
        return false;
    } else { return true; }
}