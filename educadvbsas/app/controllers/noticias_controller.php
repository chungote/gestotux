<?php
class NoticiasController extends AppController {
	var $uses = 'Noticias';
	var $scaffold;

	function ultimas() {
		return $this->Noticias->ultimas();
	}
}
?>