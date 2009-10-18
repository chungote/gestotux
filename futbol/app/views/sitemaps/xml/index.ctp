<urlset xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://www.sitemaps.org/schemas/sitemap/0.9 http://www.sitemaps.org/schemas/sitemap/0.9/sitemap.xsd" xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">
	<url>
		<loc><?php echo Router::url('/',true); ?></loc>
		<changefreq>daily</changefreq>
		<priority>1.0</priority>
	</url>
	<?php foreach ($anuncios as $anuncio ):?>
	<url>
		<loc><?php echo Router::url( '/anuncios/ver/'.$anuncio['Anuncios']['id_anuncio'],true); ?></loc>
		<lastmod><?php echo $time->toAtom($anuncio['Anuncios']['modified']); ?></lastmod>
		<priority>0.8</priority>
	</url>
	<?php endforeach; ?>
	<?php foreach( $partidos as $partido ): ?>
	<url>
		<loc><?php echo Router::url( '/partidos/ver/'.$partido['Partidos']['id_partido'], true ); ?></loc>
		<lastmod><?php echo $time->toAtom( $partido['Partidos']['modified'] ); ?></lastmod>
		<priority>0.4</priority>
	</url>
	<?php endforeach; ?>
	<url>
		<loc><?php echo Router::url('/torneos/goleadores',true); ?></loc>
		<changefreq>daily</changefreq>
		<priority>1.0</priority>
	</url>
</urlset>