for i in ./Syntaxe/OK/*.c ; do
  echo -e "\n"
  message='Fichier testé :'
  echo $message $i
 ../minicc $i -v
done
