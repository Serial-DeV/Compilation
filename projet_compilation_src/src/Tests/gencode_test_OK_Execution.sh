for i in ./Gencode/OK/*.c ; do
  echo -e "\n"
  message='Fichier testé :'
  echo $message $i
  ../minicc $i
  java -jar Mars_4_2.jar out.s
done
