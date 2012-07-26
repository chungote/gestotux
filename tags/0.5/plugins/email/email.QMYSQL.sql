CREATE TABLE IF NOT EXISTS `servidores_email` ( `id_servidor` int(1) NOT NULL auto_increment, `nombre` tinytext NOT NULL, `direccion` tinytext NOT NULL, `puerto` int(2) NOT NULL, `usuario` tinytext NOT NULL, `pass` tinytext,`de` tinytext, `predeterminado` tinyint(2) NOT NULL default '0', PRIMARY KEY  (`id_servidor`) ) ENGINE=MyISAM DEFAULT CHARSET=latin1;
CREATE TABLE IF NOT EXISTS `emails` ( `id_mail` int(2) NOT NULL auto_increment, `id_unico` text NOT NULL, `para` tinytext NOT NULL, `cc` tinytext, `bcc` tinytext, `cuerpo` mediumblob NOT NULL, `content-type` tinytext, `asunto` tinytext, PRIMARY KEY  (`id_mail`) ) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;