# Simulatore di equazioni differenziali in ambito biologico

Questo programma è un'implementazione a scopo didattico di un risolutore di equazioni differenziali.

## Requisiti per la complilazione
+ Un compilatore c++ (durante i test è stato usato g++)
+ La libreria libsbml
+ Il programma gnuplot per disegnare i grafici
+ Il wrapper gnuplot-iostream (Già presente nel progetto; si tratta dell'header gnuplot-iostream.h)
+ Un'implementazione di make

Per compilare è sufficente lanciare make nella cartella del progetto

## Esecuzione
Per eseguire il programma è sufficiente lanciare l'eseguibile __sim__ generato in fase di compilazione.

## Struttura del progetto
Il progetto è formato dalle seguenti classi:
+ **Stepper**: è la classe padre di tutti i possibili stepper; la classe implementa le seguenti funzioni:
	+ Importazione di un modello **SBML** 
	+ Gestione del passo adattivo tramite **step doubling**.
	+ Valutazione delle formule in formato **AST** (Sono implementate solo le funzioni principali)
+ **Euler_Stepper & RK4_Stepper**: sono due classi figle della classe stepper:
	+ Ridefiniscono il metodo **do_stepp** in modo da implementare rispettivamente il **Metodo di Eulero**
	  e un metodo **Runge-Kutta 4**
	+ Assegnano all'attributo k il corretto valore dove k è l'esponente dell'errore globale in relazione al passo:
		<img src="https://latex.codecogs.com/gif.latex?$\epsilon&space;=&space;O(h^k)$" title="$\epsilon = O(h^k)$" />
+ **gui** è il contenitore di una serie di utility per esportare i dati in csv e disegnarli a schermo tramite gnuplot


