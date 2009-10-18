<?php
class User extends AppModel
{
    var $name = 'User';
    var $belongsTo = 'Group';

	var $validate = array(
			'user' => VALID_NOT_EMPTY,
			'passwd' => VALID_NOT_EMPTY,
			'email' => VALID_EMAIL );

	function beforeSave()
	{
		define('VALID_MD5', '/[A-Fa-f0-9]{32}/i');
		$passwd = isset($this->data['User']['passwd'])?$this->data['User']['passwd']:"";
		if (!empty($passwd)){
			if (!preg_match(VALID_MD5, $passwd))
			{
				$this->data['User']['passwd'] = md5($passwd);
			}
		}
		return true;
	}
}
?>