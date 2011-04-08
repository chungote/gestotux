<?php
/* SVN FILE: $Id: edit.ctp 7945 2008-12-19 02:16:01Z gwoo $ */
/**
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
 * @subpackage    cake.cake.libs.view.templates.scaffolds
 * @since         CakePHP(tm) v 0.10.0.1076
 * @version       $Revision: 7945 $
 * @modifiedby    $LastChangedBy: gwoo $
 * @lastmodified  $Date: 2008-12-18 18:16:01 -0800 (Thu, 18 Dec 2008) $
 * @license       http://www.opensource.org/licenses/mit-license.php The MIT License
 */
?>
<div class="<?php echo $pluralVar;?> form">
<?php
	echo $form->create();
	echo $form->inputs(null, array('created', 'modified', 'updated'));
	echo $form->end(__('Enviar', true));
?>
</div>
<div class="actions">
	<ul>
<?php if ($this->action != 'add'):?>
		<li><?php echo $html->link(__('Eliminar', true), array('action'=>'delete', $form->value($modelClass.'.'.$primaryKey)), null, __('Are you sure you want to delete', true).' #' . $form->value($modelClass.'.'.$primaryKey)); ?></li>
<?php endif;?>
		<li><?php echo $html->link(__('Listar', true).' '.$pluralHumanName, array('action'=>'index'));?></li>
<?php
		$done = array();
		foreach ($associations as $_type => $_data) {
			foreach ($_data as $_alias => $_details) {
				if ($_details['controller'] != $this->name && !in_array($_details['controller'], $done)) {
					echo "\t\t<li>".$html->link(sprintf(__('Listar %s', true), Inflector::humanize($_details['controller'])), array('controller'=> $_details['controller'], 'action'=>'index'))."</li>\n";
					echo "\t\t<li>".$html->link(sprintf(__('Nuevo/a %s', true), Inflector::humanize(Inflector::underscore($_alias))), array('controller'=> $_details['controller'], 'action'=>'add'))."</li>\n";
					$done[] = $_details['controller'];
				}
			}
		}
?>
	</ul>
</div>