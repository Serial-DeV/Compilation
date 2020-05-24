for i in ./Verif/KO/*.c ; do
  echo -e "\n"
  message='Fichier testé :'
  echo $message $i
 ../minicc $i -v
done
