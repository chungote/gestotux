<?php

class User Extends AppModel{
	var $name = 'User';
	var $scaffold;

	var $belongsTo = 'Grupo';
}
?>