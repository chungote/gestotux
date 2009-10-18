<?php
class Fecha extends AppModel {
 var $name = 'Fecha';
 var $tableName = 'fechas';
 var $primaryKey = 'id_fecha';

 var $belongsTo = array( 'Torneo' =>
			   array( 'class' => 'Torneo',
				    'condition' => array( 'Fecha.torneo_id' => 'Torneo.id' ) ) );

   var $hasMany = array( 'Partido' =>
					array( 'className' => 'Partido',
						 'foreignKey' => 'fecha_id',
						 'dependent' => true )
				);

 var $hasOne = array( 'FotoFecha' =>
			array( 'className' => 'Foto',
				 'foreignKey' => false,
				 'conditions' => 'FotoFecha.foto_fecha = Fecha.id_fecha',
				 'fields' => array( 'id_foto', 'archivo', 'titulo' ),
				 'dependent' => false ) );

 var $validate = array(
	'fecha_inicio' => 'date',
	'fecha_fin' => 'date',
	'publicado' => 'boolean' );

}
?>