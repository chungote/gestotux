<?php
if( sizeof( $fotos ) > 0 ) {
	$c = 0;
	foreach( $fotos as $foto ) {
		if( $c >= 3 ) { echo "\n"; $c = 0; }
		if( $c >= 1 && $c < 3 ) { echo "|"; }
		echo $foto;
		$c++;
	}
}
?>