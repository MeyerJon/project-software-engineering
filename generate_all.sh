#! /bin/bash

echo 'BAAAAAAAAAAAAAAASH'
for FILE in $(find testInput/$FOLDER*.xml)
do
    echo "Processing $FILE"
    ./Metronet $FILE
done
