for i in ./Gencode/KO/*.c ; do
  echo -e "\n"
  message='Fichier testé :'
  echo $message $i
 ../minicc $i
done
