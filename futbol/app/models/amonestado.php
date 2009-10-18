<?php
/*
CREATE TABLE amonestados (
 id_amonestado BIGINT PRIMARY KEY auto_increment,
 partido_id BIGINT REFERENCES partidos(id_partido),
 equipo_id BIGINT REFERENCES equipo(id_equipo),
 nombre_jugador TINYTEXT NOT NULL,
 cantidad SMALLINT NOT NULL DEFAULT 1,
 publicado TINYINT NOT NULL DEFAULT 1
) ENGINE=InnoDB
*/

class Amonestado extends AppModel {
 var $name = "Amonestado";
 var $primaryKey = 'id_amonestado';

 var $belongsTo = array( 'Partido', 'Equipo' );
}
?>