#include "enviadoremail.h"

EnviadorEmail::EnviadorEmail( QString usuario,
                              QString contrasena,
                              QString direccion,
                              Email *parent,
                              QSqlDatabase db ) :
QThread(parent)
{
    this->db = db;
    this->_usuario = usuario;
    this->_contrasena = contrasena;
    this->_host = direccion;
}

/*!
 * \brief EnviadorEmail::terminarEjecucion
 */
void EnviadorEmail::terminarEjecucion()
{
}

/*!
 * \brief EnviadorEmail::enviarEmail
 */
void EnviadorEmail::enviarEmail()
{
}
