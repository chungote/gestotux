#!/bin/bash

cd ayuda
qhelpgenerator documentacion.qhp -o ../bin/documentacion.qch
echo "Listo."