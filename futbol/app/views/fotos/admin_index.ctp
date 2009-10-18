<h1>Administrador de Fotos</h1><hr>
<?php
if( sizeof( $todas ) <= 0 )
{
  echo "<div>No existen fotos!</div>";
}
else
{ /*pr( $todas );*/ ?>
<h1>Fotos del <?php echo $nombre_fecha; ?></h1><hr>
<table class="tabla_admin" width="100%" cellspacing="2" border="0" cellpadding="0" align="center" style="border-bottom-color : #59b034; border-bottom-style : solid; border-bottom-width : 2px; border-collapse : separate; border-left-color : #59b034; border-left-style : solid; border-left-width : 2px; border-right-color : #59b034; border-right-style : solid; border-right-width : 2px; border-spacing : 1px 0px; border-top-color : #59b034; border-top-style : solid; border-top-width : 2px;">
  <tbody>
<?php
//pr( $todas );
echo $html->tableHeaders( array( '#ID', 'Foto', 'Titulo', 'Publicado', 'Acciones' ) );
foreach( $todas as $foto )
{
 if( $foto['Foto']['publicado'] == 1 )
 { $foto['Foto']['publicado'] =  $html->link( "si", '/admin/fotos/publicar/0/'.$foto['Foto']['id_foto'].'/'.$que.'/'.$id ); }
 else
 { $foto['Foto']['publicado'] = $html->link( "no", '/admin/fotos/publicar/1/'.$foto['Foto']['id_foto'].'/'.$que.'/'.$id ); }
 echo $html->tableCells ( array(
			array( $foto['Foto']['id_foto'],
				 ' '.$thumbnail->show( array(
							'src' => $foto['Foto']['archivo'],
							'w' => 80 ) ),
				 $foto['Foto']['titulo'],
				 $foto['Foto']['publicado'],
				 $html->link( "Eliminar", '/admin/fotos/eliminar/'.$foto['Foto']['id_foto'].'/'.$que.'/'.$id , array(), 'Esta seguro que desea eliminar esta foto?' )
			) ) );
}
?>
    <tr>
      <td><?php echo $paginator->prev('<< Anterior', null, null, array('class' => 'disabled')); ?></td>
      <td colspan="4"><?php echo $paginator->counter( array( 'format' => 'Pagina %page% de %pages%, %current% de %count%' ) ); ?></td>
      <td><?php echo $paginator->next('Siguiente >>', null, null, array('class' => 'disabled')); ?></td>
    </tr>
  </tbody>
</table>
<?php
  
}
if( $que != null ) {
  echo $html->link( "Agregar nueva foto", '/admin/fotos/agregar/'.$que.'/'.$id );
}
 ?>