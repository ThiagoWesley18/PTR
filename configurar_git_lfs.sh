#!/bin/bash

# Instalar Git LFS
sudo apt-get install git-lfs

# Inicializar Git LFS no repositório
cd /home/thiago/Documentos/PTR
git lfs install

# Configurar arquivos CSV grandes para usar LFS
git lfs track "*.csv"

# Commit do arquivo .gitattributes
git add .gitattributes
git commit -m "Configurar Git LFS para arquivos CSV grandes"

# Tentar enviar novamente
git push
