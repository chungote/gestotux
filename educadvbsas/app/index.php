<?php
/* SVN FILE: $Id: index.php 7945 2008-12-19 02:16:01Z gwoo $ */
/**
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
 * @subpackage    cake.app
 * @since         CakePHP(tm) v 0.10.0.1076
 * @version       $Revision: 7945 $
 * @modifiedby    $LastChangedBy: gwoo $
 * @lastmodified  $Date: 2008-12-18 18:16:01 -0800 (Thu, 18 Dec 2008) $
 * @license       http://www.opensource.org/licenses/mit-license.php The MIT License
 */
define ('APP_DIR', 'app');
define ('DS', DIRECTORY_SEPARATOR);
define ('ROOT', dirname(__FILE__).DS);

require_once ROOT.'cake'.DS.'basics.php';
require_once ROOT.APP_DIR.DS.'config'.DS.'core.php';
require_once ROOT.'cake'.DS.'config'.DS.'paths.php';

$uri = setUri();

/**
 * As mod_rewrite (or .htaccess files) is not working, we need to take
care
 * of what would normally be rewritten, i.e. the static files in
/public
 */
if ($uri === '/' || $uri === '/index.php')
{
    $_GET['url'] = '/';
    require_once ROOT.APP_DIR.DS.WEBROOT_DIR.DS.'index.php';
}

else
{
    $elements = explode('/index.php', $uri);
    if(!empty($elements[1]))
    {
        $path = $elements[1];
        if (! SERVER_APACHE)
        {
            $path=substr($path,5);
                $path=split('&',$path);
                $path=$path[0];
        }
    }
    else
    {
        $path = '/';
    }

    $_GET['url'] = $path;

    require_once ROOT.APP_DIR.DS.WEBROOT_DIR.DS.'index.php';
} 
//require 'webroot' . DIRECTORY_SEPARATOR . 'index.php';
?>