#ifndef UTIL_H
#define UTIL_H

class QString;
/*!
 * \brief The Util class
 * Colección de métodos estaticos varios que no requieren una clase específica.
 * \author Esteban Zeller
 */
class Util
{
public:
    static QString comparacionSQL(const QString texto );
    static QString funcionComparacionSQL( const QString nombre_campo );

};

#endif // UTIL_H
