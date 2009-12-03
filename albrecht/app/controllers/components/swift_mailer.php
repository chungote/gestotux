<?php
/*
 * SwiftMailer Component Original By othman ouahbi.
 * Ported for Swift Mailer 3 By Wouter Verweirder
 * comments, bug reports are welcome wouter AT aboutme DOT be
 * @author Wouter Verweirder
 * @author othman ouahbi aka CraZyLeGs
 * @version 0.2
 * @license MIT
 */


class SwiftMailerComponent extends Object {
	var $controller = false;
	var $mailer = null;
	var $connection = 'smtp'; // sendmail, native

	var $smtp_host = null; // null auto detect
	var $smtp_port = false; // false to let the mailer choose. default 25, 465 for ssl.
	var $smtp_type = 'open'; // open, ssl, tls

	var $username = null;
	var $password = null;
	
	var $message = null; //reference to a Swift_Message object
	var $subject = '';
	var $recipients = null;
	var $from = null;

	var $layout = 'swift_email';

	var $email_views_dir = 'swift_emails';

	var $sendmail_cmd = false; // false: SWIFT_AUTO_DETECT, 'default': '/usr/sbin/sendmail -bs' etc..

	function startup(& $controller) {
		$this->controller = & $controller;
	}

	function connect() {
		switch ($this->connection) {
			case 'smtp' :
				$this->connect_smtp();
				break;
			case 'sendmail' :
				$this->connect_sendmail();
				break;
			case 'native' :
			default :
				$this->connect_native();
				break;
		}

		//return $this->mailer->isConnected();
		return true;
	}

	function connect_native() {
		vendor('Swift');
		vendor('Swift/Connection/NativeMail');

		$this->mailer = new Swift(new Swift_Connection_NativeMail());
	}

	function connect_sendmail() {
		vendor('Swift');
		vendor('Swift/Connection/Sendmail');

		if ($this->sendmail_cmd == false)
		{
			$this->sendmail_cmd = -2;
		}
		elseif ( $this->sendmail_cmd == 'default' )
		{
			$this->sendmail_cmd = '/usr/sbin/sendmail -bs';
		}

		$this->mailer = new Swift(new Swift_Connection_Sendmail($this->sendmail_cmd));
	}

	function connect_smtp() {
		vendor('Swift');
		vendor('Swift/Connection/SMTP');

		// SWIFT_AUTO_DETECT
		if (is_null($this->smtp_host)) {
			$this->smtp_host = -2;
		}
		
		if (is_null($this->smtp_port)) {
			$this->smtp_port = -2;
		}
		
		$ssl_types = array('open'=>8,'ssl'=>4,'tls'=>2);
		
		if(in_array($this->smtp_type, array ('open','ssl','tls')))
		{
			$ssl_type = $ssl_types[$this->smtp_type];
		}else
		{
			$ssl_type = $ssl_types['open'];
		}
		
		$smtp =& new Swift_Connection_SMTP($this->smtp_host, $this->smtp_port, $ssl_type);
		$smtp->setUsername($this->username);
		$smtp->setPassword($this->password);

		$this->mailer = new Swift($smtp);

	}

	function auth() {
		return true;
	}

	function errors() {
		//disabled for now
		//return $this->mailer->errors;
		return null;
	}

	function transactions() {
		//disabled for now
		//return $this->mailer->transactions;
		return null;
	}

	function close() {
		//disabled for now
		//$this->mailer->close();
	}

	/*
	 * description: 
	 * Renders a body view located in the emails dir.
	 * if html, wraps it with a layout and embeds images that have the embed="swift" attribute
	 * strip tags if plain.
	 */
	function viewBody($name, $type = 'both', $return = false) {
		switch ($type) {
			case 'both' :
				$plain = true;
				$html = true;
				break;
			case 'html' :
				$html = true;
				break;
			case 'plain' :
				$plain = true;
				break;
			default :
				return;
				break;
		}
		
		$this->message =& new Swift_Message($this->subject);

		if (isset ($html)) {
			$name .= "_html";
			$view = VIEWS . $this->email_views_dir . DS . $name . '.thtml';
			$old_layout = $this->controller->layout;
			ob_start();
			$this->controller->render(null, $this->layout, $view);
			$html_msg = ob_get_clean();
			$html_msg = $this->replaceIMG($html_msg);
			$this->controller->layout = $old_layout;
		}

		if (isset ($plain)) {
			$view = VIEWS . $this->email_views_dir . DS . $name . '.thtml';
			$old_layout = $this->controller->layout;
			$this->controller->layout = '';
			ob_start();
			$this->controller->render(null, null, $view);
			$plain_msg = strip_tags(ob_get_clean());
			$this->controller->layout = $old_layout;
		}

		switch ($type) {
			case 'both' :
				if ($return) {
					return array (
						$plain_msg,
						$html_msg
					);
				}
				$this->message->attach(new Swift_Message_Part($html_msg, "text/html"));
				$this->message->attach(new Swift_Message_Part($plain_msg, "text/plain"));
				break;
			case 'html' :
				if ($return) {
					return $html_msg;
				}
				$this->message->attach(new Swift_Message_Part($html_msg, "text/html"));
				break;
			case 'plain' :
				if ($return) {
					return $plain_msg;
				}
				$this->message->attach(new Swift_Message_Part($plain_msg, "text/plain"));
				break;
		}

	}

	function replaceIMG($msg) {
		$matches = array ();
		$files = array ();
		if (preg_match_all('#<img.*src=\"(.*?)\".*?\/>#', $msg, $matches)) {
			for ($i = 0; $i < count($matches[0]); $i++) {
				$pos = strpos($matches[0][$i], 'embed="swift"');
				if ($pos !== false) {
					$file = substr($matches[1][$i], strrpos($matches[1][$i], '/') + 1);
					if (array_key_exists($file, $files)) {
						$replace = $files[$file];
					} else {
						//$replace = $this->mailer->addImage(WWW_ROOT . 'img' . DS . $file);
						$replace = $message->attach(new Swift_Message_Image(new Swift_File(WWW_ROOT . 'img' . DS . $file)));
						$files[$file] = $replace;
					}

					$msg = str_replace($matches[1][$i], $replace, $msg);
				}
			}
		}
		return $msg;

	}

	/*
	 * description: 
	 * Wraps the body with a layout, strips tags if not html
	 */
	function wrapBody($msg, $type = 'plain', $return = false) {
		$view = VIEWS . $this->email_views_dir . '/default.thtml';

		$this->controller->set('swiftMailer_data', $msg);

		ob_start();
		$this->controller->render(null, $this->layout, $view);
		$msg = ob_get_clean();

		if ($type != 'html') {
			$msg = strip_tags($msg);
		}

		if ($return) {
			return $msg;
		}

		$this->message =& new Swift_Message($this->subject);
		if($type == 'html'){
			$this->message->attach(new Swift_Message_Part($msg, "text/plain"));
		}else{
			$this->message->attach(new Swift_Message_Part($msg, "text/html"));
		}
	}

	// original idea Tommy0	
	function addTo($type, $address, $name = false) {
		if(empty($this->recipients)){
			$this->recipients =& new Swift_RecipientList();
		}
		switch($type){
			case 'to':
				$this->recipients->addTo($address, $name);
				break;
			case 'from':
				$this->from =& new Swift_Address($address, $name);
				break;
			case 'cc':
				$this->recipients->addCc($address, $name);
				break;
			case 'bcc':
				$this->recipients->addBcc($address, $name);
				break;
		}
	}

	// original idea Tommy0
	function send($subject) {
		//subject updaten
		$this->message->setSubject($subject);
		//
		if ($this->mailer->send($this->message, $this->recipients, $this->from)) {
			$this->close();
			return true;
		}
		return false;
	}

	function sendWrap($subject, $body, $type = 'plain') {
		$this->wrapBody($body, $type);

		return $this->send($subject);
	}

	function sendView($subject, $view, $type = 'plain') {
		$this->viewBody($view, $type);

		return $this->send($subject);
	}

}
?>