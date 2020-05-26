for ((i=1;i<=4;i++)) ; do
  f=./Gencode/KO/test$i.c
  echo -e "\n"
  message='Fichier testé :'
  echo $message $f
  ../minicc $f
  java -jar Mars_4_2.jar out.s
done

