@echo off
if %1 == eliminar
  del src/cliente.pri
else
  del src/cliente.pri

  echo "TARGET = " %1 >> src/cliente.pri
  echo "win32 {" >> src/cliente.pri
  echo "  RC_FILE = ../plugins/$2" >> src/cliente.pri
  echo "}" >> src/cliente.pri
fi