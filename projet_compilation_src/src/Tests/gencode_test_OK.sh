for i in ./Gencode/OK/*.c ; do
  echo -e "\n"
  message='Fichier testé :'
  echo $message $i
  ../minicc $i
done
