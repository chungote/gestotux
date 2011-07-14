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

NumeroComprobante::NumeroComprobante( const NumeroComprobante &original ) : QObject() {
    setParent( original.parent() );
    _dato.first = original.serie();
    _dato.second = original.numero();
}

NumeroComprobante::NumeroComprobante( NumeroComprobante &original ) : QObject() {
    setParent( original.parent() );
    _dato.first = original.serie();
    _dato.second = original.numero();
}

NumeroComprobante & NumeroComprobante::operator=( const NumeroComprobante &t ) {
    NumeroComprobante *n = new NumeroComprobante( t.parent(), -1, -1 );
    n->setearNumero( t.numero() );
    n->setearNumeroSerie( t.serie() );
    return *n;
}

/*!
 * \fn NumeroComprobante::setearNumero( int numero )
 * Setea el numero de comprobante
 * @param Numero del comprobante
 */
void NumeroComprobante::setearNumero( int numero ) { _dato.second = numero; }
/*!
 * \fn NumeroComprobante::setearNumeroSerie( int serie )
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
  return QString( "%1-%2").arg( QString::number( _dato.first ), CANT_DIGITOS, '0' ).arg( QString::number( _dato.second ), CANT_DIGITOS, '0' );
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

/*!
 * \fn NumeroComprobante::siguienteNumero()
 * Devuelve un objeto con el siguiente numero valido.
 */
void NumeroComprobante::siguienteNumero() {
  if( !this->esValido() ) {
      return;
  }

  if( _dato.first <= 99999 ) {
      if( ( _dato.second + 1 ) <= 99999 ) { // Si el numero no llego al final aumento el numero
          this->_dato.second++;
          return;
      } else {
          if( ( _dato.first + 1 ) <= 99999 ) {  // si la serie no se va de mambo, aumento el serie y reinicio la numeracion
            _dato.first++;
            _dato.second = 1;
            return;
          } else {
              qCritical( "Error de desbordamiento de numero de comprobante!" );
              return;
          }
      }
  }
  return;
}
