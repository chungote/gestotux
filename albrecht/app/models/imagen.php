<?php

class Imagen extends AppModel {
   var $name = 'imagen';
   var $useTable = "imagenes";
   var $uses = array( 'Folder' );

   var $belongsTo = array(
				'Propiedad' =>
					array( 'className' => 'propiedad',
						 'foreignKey' => 'propiedad_id',
						 'dependent' => false )
				);

	var $__defaultSettings = array(
		'enabled' => true,
		'fileField' => 'filename',
		'dirField' => 'ruta',
		'allowedMime' => array('image/jpeg', 'image/pjpeg', 'image/gif', 'image/png'),
		'allowedExt' => array('jpg','jpeg','gif','png'),
		'allowedSize' => '8', // '*' for no limit (in any event limited by php settings)
		'allowedSizeUnits' => 'MB', 
		'overwriteExisting' => false,
		/* Dynamic path/file names 
		 * The constants DS, APP, WWW_ROOT can be used if wrapped in {}
		 * To use a variable, wrap in {} if the var is not defined during setup it is assumed to be the name
		 * of a field in the submitted data
		 */
		'baseDir' => '{WWW_ROOT}img{DS}propiedades{DS}',
		'relDir' => 'propiedades{DS}', // Directorio relativo al root
		'dirFormat' => '{$propiedad_id}', // include {$baseDir} to have absolute paths
		'fileFormat' => '{$filename}', // include {$dir} to store the dir & filename in one field
		'pathReplacements' => array(),
		'_setupError' => false
	);

	function setup( $config=array()) {
		$settings = am ($this->__defaultSettings, $config);
		uses('Folder');
		$this->settings[$this->name] = $settings;
		extract ($this->settings[$this->name]);
		
		$this->addReplace( '{WWW_ROOT}', WWW_ROOT);
		$this->addReplace( '{APP}' , APP);
		$this->addReplace( '{DS}', DS);
		$path2 = $this->__replacePseudoConstants( $relDir );
		$path = $this->__replacePseudoConstants( $baseDir );
		
		if (!file_exists($path)) {
			new Folder($path, true);
			if (!file_exists($path)) {
				trigger_error('Base directory ' . $path . ' doesn\'t exist and cannot be created. '.__METHOD__, E_USER_WARNING);
				$this->settings[$this->name]['enabled'] = false;
				$this->settings[$this->name]['_setupError'] = true;
			}
		} elseif(!is_writable($path)) {
			trigger_error('Base directory ' . $path . ' is not writable. '.__METHOD__, E_USER_WARNING);
			$this->settings[$this->name]['enabled'] = false;
			$this->settings[$this->name]['_setupError'] = true;
		};
		$this->settings[$this->name]['baseDir'] = $path;
		$this->settings[$this->name]['relDir'] = $path2;
		if (!$enabled) {
			return;
		}
		$this->setupUploadValidations();
	}

	function enableUpload( $enable = null) {
		if ($enable !== null) {
			$this->settings[$this->name]['enabled'] = $enable;
		}
		return $this->settings[$this->name]['enabled'];
	}
	
	function addReplace( $find, $replace = '') {
		$this->settings[$this->name]['pathReplacements'][$find] = $replace;
	}
	
	function beforeDelete() {
		extract ($this->settings[$this->name]);
		if (!$enabled) {
			return true;
		}
		if ($this->hasField($dirField)) {
			$data = $this->read(array($dirField,$fileField));
			$dirField = $data[$this->name][$dirField];
			$filename = $data[$this->name][$fileField];
			$filename = $dirField . DS . $filename;
		} else {
			$filename = $this->field($fileField);
		}
		if (file_exists($baseDir . $filename) && !unlink($baseDir . $filename)) {
			return false;
		}
        	return true;
    	}

	function beforeSave() {
		extract ($this->settings[$this->name]);
		if (!$enabled) {
			return true;
		}
		return $this->_processUpload();
	}

	function afterSave() {
		return $this->resize();
	}

	function checkUploadSetup ( $fieldData) {
		extract ($this->settings[$this->name]);
		if ($_setupError) {
			return false;
		}
		if (!$enabled) {
			return true;
		}
		if (!is_array($fieldData)) {
			trigger_error('The form field (' . $fileField. ') is not an array, check the form has enctype=\'multipart/form-data\'. If you are using the form helper include \'type\' => \'file\' in the second parameter '.__METHOD__, E_USER_WARNING);
			return false;
		}
		return true;
	}

	function checkUploadError ( $fieldData) {
		extract ($this->settings[$this->name]);
		if (!$enabled || $_setupError || !is_array($fieldData)) {
			return true;
		}
		if ($fieldData['size'] && $fieldData['error']) {
			return false;
		}
		return true;
	}

	function checkUploadMime ( $fieldData) {
		extract ($this->settings[$this->name]);
		if (!$enabled || $_setupError || !is_array($fieldData) || $allowedMime == '*') {
			return true;
		}
		if (is_array($allowedMime)) {
			if (in_array($fieldData['type'], $allowedMime)) {
				return true;
			}
		} elseif ($allowedMime == $fieldData['type']) {
			return true;
		}
		return false;
	}

	function checkUploadExt ( $fieldData) {
		extract ($this->settings[$this->name]);
		if (!$enabled || $_setupError || !is_array($fieldData) || $allowedExt == '*') {
			return true;
		}
		$info = pathinfo($fieldData['name']);
		$fileExt = low ($info['extension']);
		if (is_array($allowedExt)) {
			if (in_array($fileExt, $allowedExt)) {
				return true;
			}
		} elseif ($allowedExt == $fileExt) {
			return true;
		}
		return false;
	}

	function checkUploadSize ( $fieldData) {
		extract ($this->settings[$this->name]);
		if (!$enabled || $_setupError || !is_array($fieldData) || !$fieldData['size'] || $allowedSize == '*') {
			return true;
		}
		$factor = 1;
		switch ($allowedSizeUnits) {
			case 'KB':
				$factor = 1024;
			case 'MB':
				$factor = 1024 * 1024;
		}
		if ($fieldData['size'] < ($allowedSize * $factor)) {
			return true;
		}
		return false;
	}

	function absolutePath ( $id = null, $folderOnly = false) {
		if (!$id) {
			$id = $this->id;
		}
		extract ($this->settings[$this->name]);
		$path = $baseDir;
		if ($this->hasField($dirField)) {
			if (isset($this->data[$this->name][$dirField])) {
				$dir = $this->data[$this->name][$dirField];
			} else {
				$dir = $this->field($dirField);
			}
			$path .= $dir . DS;
			//$path .= $dir;
		}
		if ($folderOnly) {
			return $path;
		}
		if (isset($this->data[$this->name][$dirField])) {
			$path .= $this->data[$this->name][$fileField];
		} else {
			$path .= $this->field($fileField);
		}
		return $path; 
	}	
	
	function processUpload( $data = array()) {
		return $this->_processUpload($this, $data, true);
	}

	function setupUploadValidations() {
		extract ($this->settings[$this->name]);
		if (isset($this->validate[$fileField])) {
			$existingValidations = $this->validate[$fileField];
			if (!is_array($existingValidations)) {
				$existingValidations = array($existingValidations);
			}	
		} else {
			$existingValidations = array();
		}

		$validations['uploadSetup'] = array(
				'rule' => 'checkUploadSetup',
				'message' => 'Upload not possible. There is a problem with the setup on the server, more info available in the logs.'	
			);
		$validations['uploadError'] = array(
				'rule' => 'checkUploadError',
				'message' => 'An error was generated during the upload.'	
			);
		if ($allowedMime != '*') {
			if (is_array($allowedMime)) {
				$allowedMimes = implode(',', $allowedMime);
			} else {
				$allowedMimes = $allowedMime;
			}
			$validations['uploadMime'] = array(
				'rule' => 'checkUploadMime',
				'message' => 'The submitted mime type is not permitted, only ' . $allowedMimes . ' permitted.'
				);
		}
		if ($allowedExt != '*') {
			if (is_array($allowedExt)) {
				$allowedExts = implode(',', $allowedExt);
			} else {
				$allowedExts = $allowedExt;
			}
			$validations['uploadExt'] = array(
				'rule' => 'checkUploadExt',
				'message' => 'The submitted file extension is not permitted, only ' . $allowedExts . ' permitted.'
				);
		}
		$validations['uploadSize'] = array(
			'rule' => 'checkUploadSize',
			'message' => 'The file uploaded is too big, only files less than ' . $allowedSize . ' ' . $allowedSizeUnits .' permitted.'	
		);
		$this->validate[$fileField] = am($validations, $existingValidations); //Run the behavior validations first.
	}

	function _afterProcessUpload( $data, $direct) {
		return true;
	}

	function _beforeProcessUpload( $data, $direct) {
		return true;
	}

	function _getFilename( $string) {
		extract ($this->settings[$this->name]);
		if (strpos($string,'{') === false) {
			return Inflector::underscore(preg_replace('@[^\p{L}0-9]@u', '', $string));
		}
		return $this->__replacePseudoConstants( $string);
	}

	function _getPath ( $path) {
		extract ($this->settings[$this->name]);
		if (strpos($path,'{') === false) {
			return $path;
		}
		$path = $this->__replacePseudoConstants( $path);
		new Folder ($baseDir . $path, true, true );
		return $path;
	}

	function _processUpload( $data = array(), $direct = false) {
		if ($data) {
			$this->data = $data;
		}
		// Double check for upload start
		extract ($this->settings[$this->name]);
		if(!isset($this->data[$this->name][$fileField])) {
			if ($direct) {
				trigger_error('The method processUpload has been explicitly called but the filename field (' . $fileField . ') is not present in the submitted data. '.__METHOD__, E_USER_WARNING);
				return false;
			}
			return true; 
		}
		// Double check for upload end
		
		if (!$this->_beforeProcessUpload( $data, $direct)) {
			return false;
		}
		extract ($this->settings[$this->name]);
		
		// Get file path
		$info = pathinfo($this->data[$this->name][$fileField]['name']);
		$extension = $info['extension'];
		$filename = $info['basename'];
		$dir = $this->_getPath( $dirFormat);

		if (!$dir) {
			trigger_error('Couldn\'t determine or create the directory. '.__METHOD__, E_USER_WARNING);
			return false;
		}
		$this->addReplace( '{$dir}', $dir);

		// Get filename
		uses('Sanitize');
		$this->addReplace( '{$filename}', Sanitize::paranoid($filename, array(' ', '_', '-')));
		$filename = $this->_getFilename( $fileFormat);
		$this->data[$this->name][$fileField]['name'] = $filename.'.'.$extension;
		
		// Create save path
		$saveAs = $dir . DS . $filename . '.' . $extension;
		
		// Check if file exists
       	        if(file_exists($baseDir . $saveAs)) {
			if($overwriteExisting) {
				if(!unlink($saveAs)) {
					trigger_error('The file ' . $saveAs . ' already exists and cannot be deleted. '.__METHOD__, E_USER_WARNING);
					return false;
				}
			} else {
				$count = 2;
				while(file_exists($baseDir . $dir . DS . $filename . '_' . $count . '.' . $extension)) {
					$count++;
				}
				$this->data[$this->name][$fileField]['name'] = $filename . '_' . $count . '.' . $extension;
				$saveAs = $dir . DS . $filename . '_' . $count . '.' . $extension;
			}
               	} 
			
		// Attempt to move uploaded file
		if(!move_uploaded_file($this->data[$this->name][$fileField]['tmp_name'], $baseDir . $saveAs)) {
			trigger_error('Couldn\'t move the uploaded file. '.__METHOD__, E_USER_WARNING);
			return false;
		}
		
		// Update model data
		if (!$this->hasField($dirField)) {
			$this->data[$this->name][$fileField] = $dir . $this->data[$this->name][$fileField];
		}
		$this->data[$this->name][$dirField] = $dir;
		$this->data[$this->name]['mimetype'] =  $this->data[$this->name][$fileField]['type'];
		$this->data[$this->name]['filesize'] = $this->data[$this->name][$fileField]['size'];
		$this->data[$this->name][$fileField] = $this->data[$this->name][$fileField]['name'];
		$this->data[$this->name]['ruta'] = $relDir . $this->data[$this->name]['propiedad_id'] . '/';
		$maximo = $this->field( 'MAX( imagen.orden )', 'imagen.propiedad_id = '.$this->data[$this->name]['propiedad_id'], 'imagen.orden ASC' );
		$this->data[$this->name]['orden'] =  $maximo+1;
		$this->_afterProcessUpload( $data, $direct);
		return true;
	}

	function __replacePseudoConstants( &$string) {
		extract($this->settings[$this->name]);
		$random = uniqid(""); // generate a random var each time called.
		preg_match_all('@{\$([^{}]*)}@', $string, $r);
		foreach ($r[1] as $i => $match) {
			if (!isset($this->settings[$this->name]['pathReplacements'][$r[0][$i]])) {
				if (isset($$match)) {
					$this->addReplace($r[0][$i], $$match);
				} elseif (isset($this->data[$this->name][$match])) {
					$this->addReplace( $r[0][$i], $this->data[$this->name][$match]);
				} else {
					trigger_error('Cannot replace ' . $match . ' as the variable $' . $match . ' cannot be determined '.__METHOD__, E_USER_WARNING);
				}
			}
		}
		$markers = array_keys($this->settings[$this->name]['pathReplacements']);
		$replacements = array_values($this->settings[$this->name]['pathReplacements']);
		return str_replace ($markers, $replacements, $string);
	}

	function resizeFile( $fullpath, $width = 600, $height = 400, $writeTo = false, $aspect = true) {
		if (!$width||!$height) {
			return false;
		}
		extract($this->settings[$this->name]);
		if (!($size = getimagesize($fullpath))) { 
			return false; // image doesn't exist
		}
		list($currentWidth, $currentHeight, $currentType) = $size;

		// adjust to aspect.
		if ($aspect) { 
			if (($currentHeight/$height) > ($currentWidth/$width)) {
				$width = ceil(($currentWidth/$currentHeight) * $height);
			} else { 
				$height = ceil($width / ($currentWidth/$currentHeight));
			}
		}
		$types = array(1 => "gif", "jpeg", "png", "swf", "psd", "wbmp");
		$image = call_user_func('imagecreatefrom'.$types[$currentType], $fullpath);

		if (function_exists("imagecreatetruecolor") && ($temp = imagecreatetruecolor ($width, $height))) {
			imagecopyresampled ($temp, $image, 0, 0, 0, 0, $width, $height, $currentWidth, $currentHeight);
  		} else {
			$temp = imagecreate ($width, $height);
			imagecopyresized ($temp, $image, 0, 0, 0, 0, $width, $height, $currentWidth, $currentHeight);
		}
		
		$return = false;
		if ($writeTo) {
			uses('File');
			new File($writeTo, true);
			if (call_user_func("image".$types[$currentType], $temp, $writeTo)) {
				$return = true;
			}
		} else {
			ob_start();
			call_user_func("image".$types[$currentType], $temp);
			$return = ob_get_clean();		
		}
		imagedestroy ($image);
		imagedestroy ($temp);
		return $return;
	}

	function resize( $id=null, $width = 600, $height = 400, $writeTo = false, $aspect = true) {
		if ($id === null && $this->id) {
			$id = $this->id;
		} elseif (!$id) {
			$id = null;
		}
		extract($this->settings[$this->name]);
		$readResult = $this->read(array($fileField, $dirField), $id);
		extract($readResult[$this->name]);
		$fullPath = WWW_ROOT . DS . 'img'. DS . $$dirField . $$fileField;
		return $this->resizeFile( $fullPath, $width, $height, $fullPath, $aspect);
	}


}

?>