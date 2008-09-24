//
// C++ Interface: etrgastos
//
// Description:
//
//
// Author: Esteban Javier Zeller <juiraze@yahoo.com.ar>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ETRGASTOS_H
#define ETRGASTOS_H

#include <QThread>

/**
	@author Esteban Javier Zeller <juiraze@yahoo.com.ar>
*/
class ETRGastos : public QThread
{
public:
    ETRGastos();
    ~ETRGastos();
    virtual void run();

};

#endif
