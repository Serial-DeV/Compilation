int n = 3;
int h;
bool b = false;
bool c;
//n = 2; // impossible de reatribuer une valeur en dehors du main
//print(n); // print ne fonctionne pas en dehors du main
//int j = n; // global variables can only be initialized with a constant value

void main() 
{	
	//c = true; // quand cette ligne est presente avant la declaration d'un int : cause une erreur a la ligne suivante
	int i;
	//i = 1;
	//c = true;// meme chose avec les booleens
	bool z = false;;
	print(c);
	print(i);
	print("\n");
	print(h);
	print("\n");
	print(n);
	print("\n");
	n = n + 3;
	print(n);
	print("\n");
	n = i;
	print(n);
	print("\n");
	print(b);
	n = 6;
	
	//print(!b); // ne fonctionne pas
	//print(n+3); // ne fonctionne pas
	//bool c = true; // syntax error / impossible de declarer de booleen dans le main quand il suit un print
}




//// Bugs potentiels:


// En dehors du main

// impossible de reaffecter une valeur a un boleen en dehors du main (syntax error)
// impossible de reaffecter une valeur a un entier en dehors du main (syntax error)

// print non fonctionnel en dehors du main (syntax error)

// if et while non fonctionnels en dehors du main (syntax error)

// impossible d'initialiser une variable globale avec une variable



// Dans le main

// une reaffectation de valeur a un booleen, global ou local, mene a une erreur syntaxique A LA LIGNE SUIVANTE (syntax error)
// une reaffectation de valeur a un entier, global ou local, mene a une erreur syntaxique A LA LIGNE SUIVANTE (syntax error)

// un print ne peut pas imprimer le resultat d'une expression telle que: print(3+3), print(8) ou print(!b) avec b un booleen (syntax error)

// apres l'utilisation de print, il n'est PLUS possible de declarer de nouveau booleen (syntax error)
// apres l'utilisation de print, il n'est PLUS possible de declarer de nouvel entier (syntax error)

// l'utilisation de plusieurs multiples points-virgules successifs apres un print, une reaffectation de valeur, ou la declaration d'un booleen (avec ou sans affectation) ne pose pas de probleme, ce qui n'est pas le cas apres une declaration d'entier (avec ou sans affectation) (syntax error)








