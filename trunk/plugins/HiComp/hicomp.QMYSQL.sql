CREATE TABLE IF NOT EXISTS `recibos` ( `id` int(10) NOT NULL auto_increment,`cliente` text NOT NULL,`num_mes` int(2) default NULL, `texto` tinyblob, `precio` double(15,4) default NULL, `fecha_pago` date default NULL, `contado` tinyint(1) default NULL, `cuenta_corriente` tinyint(1) default NULL, PRIMARY KEY  (`id`)) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;