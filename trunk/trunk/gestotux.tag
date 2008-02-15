<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="class">
    <name>DRecibo</name>
    <filename>classDRecibo.html</filename>
    <member kind="function">
      <type></type>
      <name>DRecibo</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>f3ab0aa909c29e20126fac9faa5162fc</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setModelData</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>2385602abb48f34ad8696e05bc1ef1b5</anchor>
      <arglist>(QWidget *editor, QAbstractItemModel *model, const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setEditorData</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>e99d70c8957fbbbb5dab9e211d18d98d</anchor>
      <arglist>(QWidget *editor, const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>QWidget *</type>
      <name>createEditor</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>057bd2d196e5c33bf9986ba9a0903a42</anchor>
      <arglist>(QWidget *parent, const QStyleOptionViewItem &amp;option, const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>paint</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>4050033a2df56ea396d9d28f83d1455c</anchor>
      <arglist>(QPainter *painter, const QStyleOptionViewItem &amp;option, const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>QSize</type>
      <name>sizeHint</name>
      <anchorfile>classDRecibo.html</anchorfile>
      <anchor>1e85d439cdddcee5f84510e050998518</anchor>
      <arglist>(const QStyleOptionViewItem &amp;option, const QModelIndex &amp;index) const</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EActualizacion</name>
    <filename>classEActualizacion.html</filename>
    <base>EVentana</base>
    <member kind="slot">
      <type>void</type>
      <name>detener</name>
      <anchorfile>classEActualizacion.html</anchorfile>
      <anchor>49153014557bd58282c9875796368322</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>iniciar</name>
      <anchorfile>classEActualizacion.html</anchorfile>
      <anchor>0f5817990b0e1345c7bb2cd743a62b32</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EActualizacion</name>
      <anchorfile>classEActualizacion.html</anchorfile>
      <anchor>3bdca541480212757713375b97bbd1da</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Ebackup</name>
    <filename>classEbackup.html</filename>
    <base>EVentana</base>
    <member kind="slot">
      <type>void</type>
      <name>iniciar</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>56da080f6fb833821359c54613dac750</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>detener</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>82ef476d15c1e7b1ea15d921b231b208</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>cambiarDetener</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>4e1d089dd6ec5f9f8e998215766182fb</anchor>
      <arglist>(bool estado)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Ebackup</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>56917d94c15ff8bc9e7072da2a5be1e0</anchor>
      <arglist>(QWidget *parent)</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>generar_config</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>114be84146a49373fa0c96b969960be7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>ejecutar_colas</name>
      <anchorfile>classEbackup.html</anchorfile>
      <anchor>43b56c68beb005d1d98a3ddbd2ae112b</anchor>
      <arglist>(QList&lt; QByteArray &gt; colas)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EEnvioBackup</name>
    <filename>classEEnvioBackup.html</filename>
    <member kind="function">
      <type></type>
      <name>EEnvioBackup</name>
      <anchorfile>classEEnvioBackup.html</anchorfile>
      <anchor>dbc767817ce9f9b3b16bae60343007cb</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function" virtualness="virtual">
      <type>virtual void</type>
      <name>run</name>
      <anchorfile>classEEnvioBackup.html</anchorfile>
      <anchor>112be63982be717b1a63dfbc7831e7d2</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EInfoPrograma</name>
    <filename>classEInfoPrograma.html</filename>
    <member kind="function">
      <type></type>
      <name>EInfoPrograma</name>
      <anchorfile>classEInfoPrograma.html</anchorfile>
      <anchor>a7ef951b60ae0262c69f46236d4a2292</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EVentana</name>
    <filename>classEVentana.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>ayuda</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>c37415add4b63bbd3df607bd096c8426</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>EVentana</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>b383d6d4b2e4765916499759eac02f75</anchor>
      <arglist>(QWidget *padre)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>setNombreVentana</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>1a34c10804cb12bf8350611dbf82b43d</anchor>
      <arglist>(QString texto)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>get_nombre_ventana</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>b80a75afbbd16a08e7874add1ef02581</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>closeEvent</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>bd13dd5f4f63ecf242dbd1a9d3637083</anchor>
      <arglist>(QCloseEvent *event)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>nombre_archivo_ayuda</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>cc040cfab6787a6646439dc7af9b4b43</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QString</type>
      <name>nombre_ventana</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>8ec9b6d58e81d739339d35eb49449b65</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QWidget *</type>
      <name>padre</name>
      <anchorfile>classEVentana.html</anchorfile>
      <anchor>f85d5a05aa128f2a798b21e4f6843bed</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>EVLista</name>
    <filename>classEVLista.html</filename>
    <base>EVentana</base>
    <member kind="function">
      <type></type>
      <name>EVLista</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>222d52380c755478331a80e72dd4a336</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>closeEvent</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>c3dff0f1614fb5fe728478eff054c719</anchor>
      <arglist>(QCloseEvent *c)</arglist>
    </member>
    <member kind="variable">
      <type>QTableView *</type>
      <name>vista</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>fe3df10a1bff0632a7b79e81754bf7f8</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActAgregar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>7ee9c43db4bd6d0f336eb5f368b09faf</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActModificar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>d279917337546a416088e6958398b145</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActEliminar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>809406a6eded4c0b9a72ae3bce33decb</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActBuscar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>831a3dceb083167a766770f3152495a7</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActImprimir</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>0871f47ade45a0698f184d6f22677238</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>QAction *</type>
      <name>ActCerrar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>75253b15c9ebf7b9b35f032fbe58d74e</anchor>
      <arglist></arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cerrar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>bf5897c819ff3109bb691b59d9602382</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>agregar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>ce5b21676292bf70464a5075c23d355d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>eliminar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>3c0768fc13ee8f868a7e24242029ae2f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected" virtualness="pure">
      <type>virtual void</type>
      <name>antes_de_insertar</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>b6f2e8e2c02a89961b183097b8785dcb</anchor>
      <arglist>(int row, QSqlRecord &amp;record)=0</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>QSqlTableModel *</type>
      <name>modelo</name>
      <anchorfile>classEVLista.html</anchorfile>
      <anchor>e9455d425525fd2ddc05445f773ba26b</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAcercaDe</name>
    <filename>classFormAcercaDe.html</filename>
    <base>EVentana</base>
    <member kind="function">
      <type></type>
      <name>FormAcercaDe</name>
      <anchorfile>classFormAcercaDe.html</anchorfile>
      <anchor>e560693a5714bb7a8646b215a285d442</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormAgregarRecibo</name>
    <filename>classFormAgregarRecibo.html</filename>
    <member kind="function">
      <type></type>
      <name>FormAgregarRecibo</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>e6c02c347b49fcfabb6a959e482d8536</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>nombre</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>0c1797b00588bc61571077c36977f1a7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioImporte</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>bedb081406bfb131ad564c6e4342629b</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioEstadoPagoMes</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>6fbdc6d80dab838aae3ba9fb2ffb16c4</anchor>
      <arglist>(int estado)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioEstadoRecargos</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>bfd7d30cb6280bdca95f2d5912db3646</anchor>
      <arglist>(int estado)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>guardar</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>bc4388d2dfb2fc5d8e03dec139673ef8</anchor>
      <arglist>(bool imprimir=false)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>guardarImprimir</name>
      <anchorfile>classFormAgregarRecibo.html</anchorfile>
      <anchor>b0f9e9831c69a1ec36669b6b718c9b66</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormModificarRecibo</name>
    <filename>classFormModificarRecibo.html</filename>
    <member kind="function">
      <type></type>
      <name>FormModificarRecibo</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>ddbdea66f7e3556fad01a20c2ae79168</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>cargarDatos</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>6a30b5afd2c03db833f657b8ce5c94b6</anchor>
      <arglist>(QModelIndex idDB, QSqlTableModel *modelo)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>nombre</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>399b88773ecaf0123cd01502e6a15fae</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioImporte</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>e0c0f0e0487fddaac889773429eb0d9b</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioEstadoPagoMes</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>d6554dfa9a76696a91786ad895a50807</anchor>
      <arglist>(int estado)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioEstadoRecargos</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>02de0d46b4e679d7f6d1c0b126294b36</anchor>
      <arglist>(int estado)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>guardar</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>e6615670bf1ca80274369c6b9f5efb10</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>guardarImprimir</name>
      <anchorfile>classFormModificarRecibo.html</anchorfile>
      <anchor>edb2c89258e7718b45e0cb2d8ef3f6cd</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormPreferencias</name>
    <filename>classFormPreferencias.html</filename>
    <base>EVentana</base>
    <member kind="signal">
      <type>void</type>
      <name>guardar</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>a1ba4a1ef532dd47e3b9d8074f2529aa</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>aplicar</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>98cc2f9f46c073ba6208a8f92df18662</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="signal">
      <type>void</type>
      <name>cargar</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>efc8131a4dda81c9df7e233a669ad0b7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormPreferencias</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>b4e8295828c722a55ac4293b3d37717d</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>changePage</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>a966bf34e0c875252dce5a4332d78374</anchor>
      <arglist>(QListWidgetItem *current, QListWidgetItem *previous)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cancelar</name>
      <anchorfile>classFormPreferencias.html</anchorfile>
      <anchor>93baeeec2fa133c19f233cda377a8f11</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormPrefHijo</name>
    <filename>classFormPrefHijo.html</filename>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>aplicar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>635ad3169d1f679ca406cbf702416dad</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>cargar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>559b4ee32e995ed8f63a10b560f31593</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="slot" virtualness="pure">
      <type>virtual void</type>
      <name>guardar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>bff213f50abb890b19ba61934503813e</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormPrefHijo</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>b909fe9e7749c3c11fbac3e4f88d0a72</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FormPrefHijo</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>b909fe9e7749c3c11fbac3e4f88d0a72</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>aplicar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>635ad3169d1f679ca406cbf702416dad</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>cargar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>559b4ee32e995ed8f63a10b560f31593</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void</type>
      <name>guardar</name>
      <anchorfile>classFormPrefHijo.html</anchorfile>
      <anchor>bff213f50abb890b19ba61934503813e</anchor>
      <arglist>()=0</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FormularioCentral</name>
    <filename>classFormularioCentral.html</filename>
    <member kind="function">
      <type></type>
      <name>FormularioCentral</name>
      <anchorfile>classFormularioCentral.html</anchorfile>
      <anchor>f2c9a1778d376b52e0fe4f1d1fc6b508</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioWidget</name>
      <anchorfile>classFormularioCentral.html</anchorfile>
      <anchor>a9cc24523e1282a2cf70d0ca64c73c5d</anchor>
      <arglist>(int id)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cerrarActivo</name>
      <anchorfile>classFormularioCentral.html</anchorfile>
      <anchor>6484a9ecc7d0a95797a745a7abbe0b50</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FPrefGeneral</name>
    <filename>classFPrefGeneral.html</filename>
    <base>FormPrefHijo</base>
    <member kind="slot">
      <type>void</type>
      <name>cargar</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>95dcc026453cd7b7696fee5061853e04</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>guardar</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>5bec1f94ecc80368c72b1fcd6c5b8606</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>aplicar</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>c9f7b73c1275ca8f8d0fffee9085213c</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FPrefGeneral</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>fb9e3f7978a7394ebb18fc8c2da3fc4f</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>cambioEstadoBarra</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>b111e15da4f99917fe8dbcb583e568df</anchor>
      <arglist>(int estado)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>avanzarBarra</name>
      <anchorfile>classFPrefGeneral.html</anchorfile>
      <anchor>fd821e0c601ff32b4e8ac1ce4356dacd</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>FPrefRecibos</name>
    <filename>classFPrefRecibos.html</filename>
    <base>FormPrefHijo</base>
    <member kind="slot">
      <type>void</type>
      <name>cargar</name>
      <anchorfile>classFPrefRecibos.html</anchorfile>
      <anchor>f1b90ce37e894965def60dfec6f121a5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>aplicar</name>
      <anchorfile>classFPrefRecibos.html</anchorfile>
      <anchor>b11bfc79310ee8070d0a82b2c7c2dc5f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot">
      <type>void</type>
      <name>guardar</name>
      <anchorfile>classFPrefRecibos.html</anchorfile>
      <anchor>b36c2efe57e9a7ba5bb196934cfdc901</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>FPrefRecibos</name>
      <anchorfile>classFPrefRecibos.html</anchorfile>
      <anchor>4faaffdd913d550d1fecafa76af68042</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MCategorias</name>
    <filename>classMCategorias.html</filename>
    <member kind="function">
      <type></type>
      <name>MCategorias</name>
      <anchorfile>classMCategorias.html</anchorfile>
      <anchor>24e9e075f9421f286d737beef138582c</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MClientes</name>
    <filename>classMClientes.html</filename>
    <member kind="function">
      <type></type>
      <name>MClientes</name>
      <anchorfile>classMClientes.html</anchorfile>
      <anchor>acf06bee65f3f31c4ebf76a2a92a4fee</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QVariant</type>
      <name>data</name>
      <anchorfile>classMClientes.html</anchorfile>
      <anchor>3d75e6e324a286e9092b7a7f7334197f</anchor>
      <arglist>(const QModelIndex &amp;idx, int role) const</arglist>
    </member>
    <member kind="function">
      <type>Qt::ItemFlags</type>
      <name>flags</name>
      <anchorfile>classMClientes.html</anchorfile>
      <anchor>d3d0319c4aa9fa17ffb5a2a5940f892f</anchor>
      <arglist>(const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setData</name>
      <anchorfile>classMClientes.html</anchorfile>
      <anchor>82ae05fa33d23ae3e192ec529672e95d</anchor>
      <arglist>(const QModelIndex &amp;index, const QVariant &amp;value, int role)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MProductos</name>
    <filename>classMProductos.html</filename>
    <member kind="function">
      <type></type>
      <name>MProductos</name>
      <anchorfile>classMProductos.html</anchorfile>
      <anchor>7567c03fb05fae7917b6564c9170a6f0</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QVariant</type>
      <name>data</name>
      <anchorfile>classMProductos.html</anchorfile>
      <anchor>d99aa6d11cb0a3bc760734303a38abe5</anchor>
      <arglist>(const QModelIndex &amp;item, int role) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setData</name>
      <anchorfile>classMProductos.html</anchorfile>
      <anchor>d85b82a78a82c471d8675dd6337bb397</anchor>
      <arglist>(const QModelIndex &amp;index, const QVariant &amp;value, int role=Qt::EditRole)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>MRecibo</name>
    <filename>classMRecibo.html</filename>
    <member kind="function">
      <type></type>
      <name>MRecibo</name>
      <anchorfile>classMRecibo.html</anchorfile>
      <anchor>4f3302a3aa3113373aa3f5eb1ba355b4</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QVariant</type>
      <name>data</name>
      <anchorfile>classMRecibo.html</anchorfile>
      <anchor>6e87eebe1cce310cc23ce22fa80b023e</anchor>
      <arglist>(const QModelIndex &amp;idx, int role) const</arglist>
    </member>
    <member kind="function">
      <type>Qt::ItemFlags</type>
      <name>flags</name>
      <anchorfile>classMRecibo.html</anchorfile>
      <anchor>f0ef6a8f9c23831fb6c73002b2ba7b3d</anchor>
      <arglist>(const QModelIndex &amp;index) const</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>setData</name>
      <anchorfile>classMRecibo.html</anchorfile>
      <anchor>617c2763fb51caa87d82b1a410f714b2</anchor>
      <arglist>(const QModelIndex &amp;index, const QVariant &amp;value, int role)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>preferencias</name>
    <filename>classpreferencias.html</filename>
    <member kind="function">
      <type>void</type>
      <name>inicio</name>
      <anchorfile>classpreferencias.html</anchorfile>
      <anchor>88f468add780b544f0728e85fa6a0747</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function" static="yes">
      <type>static preferencias *</type>
      <name>getInstancia</name>
      <anchorfile>classpreferencias.html</anchorfile>
      <anchor>922b107fda4a85350dd1f694b9bb40e3</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Recibo</name>
    <filename>classRecibo.html</filename>
    <member kind="function">
      <type></type>
      <name>Recibo</name>
      <anchorfile>classRecibo.html</anchorfile>
      <anchor>43224f7d2b296206cacbc97eaa8acbd5</anchor>
      <arglist>(QObject *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QByteArray</type>
      <name>obtenerByteArray</name>
      <anchorfile>classRecibo.html</anchorfile>
      <anchor>48e24e933b12f9df0cab67491a352338</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>titulo</name>
      <anchorfile>classRecibo.html</anchorfile>
      <anchor>e1e3fc397adb8a4bd53b7e45de8ae1c5</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>bool</type>
      <name>cargarRegistro</name>
      <anchorfile>classRecibo.html</anchorfile>
      <anchor>3af9ba15c27f31401803c616aa327400</anchor>
      <arglist>(int idDB)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>imprimir</name>
      <anchorfile>classRecibo.html</anchorfile>
      <anchor>08794b97e55fc8ae9d0c086ab60024b7</anchor>
      <arglist>(QPainter *impresora)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Reloj</name>
    <filename>classReloj.html</filename>
    <member kind="function">
      <type></type>
      <name>Reloj</name>
      <anchorfile>classReloj.html</anchorfile>
      <anchor>4eca21c50110d655cbbf956505627ac8</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VCategorias</name>
    <filename>classVCategorias.html</filename>
    <base>EVLista</base>
    <member kind="slot">
      <type>void</type>
      <name>antes_de_insertar</name>
      <anchorfile>classVCategorias.html</anchorfile>
      <anchor>09121ae5eb150325637dfff828f85677</anchor>
      <arglist>(int row, QSqlRecord &amp;record)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>VCategorias</name>
      <anchorfile>classVCategorias.html</anchorfile>
      <anchor>086291213effb335c648bc727c14ecb4</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VCliente</name>
    <filename>classVCliente.html</filename>
    <base>EVLista</base>
    <member kind="function">
      <type></type>
      <name>VCliente</name>
      <anchorfile>classVCliente.html</anchorfile>
      <anchor>c6ff07e9517ea4fe42222e0914bcfd4a</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>antes_de_insertar</name>
      <anchorfile>classVCliente.html</anchorfile>
      <anchor>fab307ea0b5e70f715415f5df52e95d7</anchor>
      <arglist>(int row, QSqlRecord &amp;record)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>agregar</name>
      <anchorfile>classVCliente.html</anchorfile>
      <anchor>b9ec4f1b258179ac13ecf6bb5da2afa5</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>visorRecibo</name>
    <filename>classvisorRecibo.html</filename>
    <member kind="slot">
      <type>void</type>
      <name>imprimir</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>d7b27d910dbf2f408c3171cb6a438d6e</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>visorRecibo</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>f8f26a1023980582d6a23dd448f44848</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>QString</type>
      <name>nombre</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>383de93406e5813f5492db7a9f31574f</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>Recibo *</type>
      <name>recibo</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>10d658bd0f286982f093e56f1df1fbcb</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>verRecibo</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>45ab766a3b38ade864e48365bb105df2</anchor>
      <arglist>(int idDB)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>aPdf</name>
      <anchorfile>classvisorRecibo.html</anchorfile>
      <anchor>7984044cdc23c4b57a1fede7ba104938</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VProductos</name>
    <filename>classVProductos.html</filename>
    <base>EVLista</base>
    <member kind="function">
      <type></type>
      <name>VProductos</name>
      <anchorfile>classVProductos.html</anchorfile>
      <anchor>65730b129be6d2f1ae30050951a74814</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>closeEvent</name>
      <anchorfile>classVProductos.html</anchorfile>
      <anchor>1a8617b3041bc6464ab63056073de544</anchor>
      <arglist>(QCloseEvent *event)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>verCategorias</name>
      <anchorfile>classVProductos.html</anchorfile>
      <anchor>8c9dae17cdd00c97a398e6894af6a895</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>VRecibos</name>
    <filename>classVRecibos.html</filename>
    <member kind="function">
      <type></type>
      <name>VRecibos</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>2ae49fcbd395092b8c4d17201f431022</anchor>
      <arglist>(QWidget *parent=0)</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>ver</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>5f6ebe8d43114b5c90788e1e9d2770cd</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>eliminar</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>88f2408dd39c7d79c01a4b45904fefaf</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>modificar</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>7ae6722ddeaf39d3d8d6e7216a015a4d</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>agregar</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>8db60ff5b8b570bab8f937a0e294b189</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>imprimir</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>2f08454ed36c75141b4dc4e459dd44f0</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="slot" protection="protected">
      <type>void</type>
      <name>modificar</name>
      <anchorfile>classVRecibos.html</anchorfile>
      <anchor>5bc889232d3f06222057e783b6de2156</anchor>
      <arglist>(const QModelIndex &amp;index)</arglist>
    </member>
  </compound>
</tagfile>
