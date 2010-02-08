<?php
/* SVN FILE: $Id: database.php.default 8004 2009-01-16 20:15:21Z gwoo $ */
/**
 * This is core configuration file.
 *
 * Use it to configure core behaviour ofCake.
 *
 * PHP versions 4 and 5
 *
 * CakePHP(tm) :  Rapid Development Framework (http://www.cakephp.org)
 * Copyright 2005-2008, Cake Software Foundation, Inc. (http://www.cakefoundation.org)
 *
 * Licensed under The MIT License
 * Redistributions of files must retain the above copyright notice.
 *
 * @filesource
 * @copyright     Copyright 2005-2008, Cake Software Foundation, Inc. (http://www.cakefoundation.org)
 * @link          http://www.cakefoundation.org/projects/info/cakephp CakePHP(tm) Project
 * @package       cake
 * @subpackage    cake.app.config
 * @since         CakePHP(tm) v 0.2.9
 * @version       $Revision: 8004 $
 * @modifiedby    $LastChangedBy: gwoo $
 * @lastmodified  $Date: 2009-01-16 12:15:21 -0800 (Fri, 16 Jan 2009) $
 * @license       http://www.opensource.org/licenses/mit-license.php The MIT License
 */
class DATABASE_CONFIG {

	var $default = array(
		'driver' => 'mysql',
		'persistent' => false,
		'host' => 'localhost',
		'login' => 'educaadvbsas',
		'password' => 'educa',
		'database' => 'educaadvbsas',
		'prefix' => '',
	);

	var $test = array(
		'driver' => 'mysql',
		'persistent' => false,
		'host' => 'localhost',
		'login' => 'educaadvbsas',
		'password' => 'educa',
		'database' => ' educaadvbsas',
		'prefix' => '',
	);
}
?>