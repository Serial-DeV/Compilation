for ((i=1;i<=35;i++)) ; do
  f=./Gencode/OK/test$i.c
  echo -e "\n"
  message='Fichier testé :'
  echo $message $f
  ../minicc $f
  java -jar Mars_4_2.jar out.s|sed '1d'|sed '1d' >> Gencode/OK/Sorties_attendues/tmp
  cpt=$(diff Gencode/OK/Sorties_attendues/$i Gencode/OK/Sorties_attendues/tmp|wc -l)
  rm Gencode/OK/Sorties_attendues/tmp
  rm out.s
  if [[ $cpt != 0 ]] ; then
    echo "Erreur: résultat inattendu pour $f"
  fi
done

