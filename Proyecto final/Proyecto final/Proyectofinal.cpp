#include <iostream>

using namespace std;

template <typename Item>
struct node{
		
	Item item;
	node<Item> *next;
	
	node(Item _item, node<Item> *_next){
		item = _item;
		next = _next;
	}

};

template <typename Item>
class list{
	node<Item> *head;
	node<Item> *tail;
	
	public:
		
	list(node<Item> *_head = NULL, node<Item> *_tail = NULL){
		head = _head;
		tail = _tail;
	}		
	
	int longitud();
	void insertaAlInicio(Item item);
	void insertaAlFinal(Item item);
	node<Item>* regresaNth(int N);
	void limpiar();
	node<Item>* primero();
	node<Item>* ultimo();
	void quitaPrimero();
	void quitaUltimo();	
	
	~list(){
		limpiar();
	}
};

template<typename Item>
int list<Item>::longitud(){
	int len=0;
	
	node<Item> *copy = head;
	
	while(copy!=NULL){
		len++;
		copy = copy->next; 
	}
	
	return len;
}

template <typename Item>
void list<Item>::insertaAlInicio(Item item){
	head = new node<Item>(item, head);
	if(tail==NULL)
		tail = head;
	
	return;
}

template <typename Item>
void list<Item>::insertaAlFinal(Item item){
	if(head == NULL){
		insertaAlInicio(item);
		return;
	}
		 
	tail->next = new node<Item>(item, NULL);
	tail = tail->next;
	
	return;
}

template <typename Item>
node<Item>* list<Item>::regresaNth(int N){
	if(N <= 0)
		return NULL;
	
	node<Item> *copy = head;
	
	for(int i=1; i<N && copy != NULL; i++)
		copy = copy->next;
		
	return copy;
}

template <typename Item>
void list<Item>::limpiar(){
	node<Item> *aux;
	
	while (head != NULL){
		aux = head;
		head = aux->next;
		delete aux;
	}
	
	tail=NULL;
	
	return;
}

template <typename Item>
node<Item>* list<Item>::primero(){
	return head;
}

template <typename Item>
node<Item>* list<Item>::ultimo(){
	return tail;
}

template <typename Item>
void list<Item>::quitaPrimero(){
	if(head == NULL)
		return;
	
	if(tail==head)
		tail=NULL;
		
	node<Item> *aux = head;
	head = aux->next;
	
	delete aux;
	
	return;
}

template <typename Item>
void list<Item>::quitaUltimo(){
	
	if(tail == NULL)
		return;	
		
	if(tail==head){
		tail=NULL;
		delete head;
		head=NULL;
		
		return;
	}
		
	node<Item> *copy = head;
		
	while(copy->next != tail)
		copy = copy->next;
			
	delete tail;
	tail = copy;	
	tail->next = NULL;
	
	return;
}

template <typename Item>
class Stack{
	list<Item> stack;
	
	public:
	
	Stack(){
		stack = list<Item>();
	}
	
	void push(Item item){
		stack.insertaAlInicio(item);
		return;
	}
	
	void pop(){
		stack.quitaPrimero();
		return;
	}
	
	int size(){
		return stack.longitud();
	}
	
	Item peek(){
		/*node<Item> *top = lista.regresaNth(1);
		return top == NULL ? 0 : top->item;*/
		return stack.regresaNth(1)->item;
	}
	
	bool empty(){
		return (stack.regresaNth(1) == NULL) ? true : false;
	}
	
	~Stack(){
		stack.limpiar();
	}
};

//PROYECTO FINAL: ALGORITMO DEL CABALLO EN EL TABLERO DE AJEDREZ
//PRESENTA: LESLIE JANETH QUINCOSA RAMIREZ

using namespace std;

struct position{ //estructura posición
	int i, j;	//nos indica la posición del caballo en el tablero, en sus respectivas coordenadas
	
	position(int _i=0, int _j=0) {	i=_i; j=_j;	}
	
	void operator=(position p){	i=p.i;	j=p.j;	}
	
	position operator+(position p){	
		position sum(i+p.i,j+p.j);
		return sum;	
	}
};

bool isMove(position p){
	if(p.i>=0 && p.i<=7 && p.j>=0 && p.j<=7)
		return true;
	
	return false;
}

void KnightsTour(position inicio){ 
	if(!isMove(inicio)) // preguntamos si la casilla de inicio esta en el tablero
		return;
	
	int tour[8][8], i, j, count=0;//count es el numero de movimiento que ha hecho el caballo
	bool visit[8][8];// la entrada (i,j) es true si el caballo ya ha estado anteriormente en la casilla (i,j). Es false en otro caso
	
	position actual, next, moves[8];//next es la proxima posicion posible a mover
	moves[0]=position(2,-1); moves[1]=position(2,1); moves[2]=position(1,-2); moves[3]=position(1,2); moves[4]=position(-1,-2); 
	moves[5]=position(-1,2); moves[6]=position(-2,-1); moves[7]=position(-2,1);
	
//sumar una posicion p con un movimiento move nos regresa la coordenada sumar(p, move) a la que se movera el caballo 	
	for(i=0; i<8; i++)
		for(j=0; j<8; j++)
			visit[i][j]=false;
	
	Stack<position> pila;// a la pila iremos agregando los movimientos posibles en cada momento
	pila.push(inicio);//agregamos la posicion inicial a la pila
	
	while(count<64){
		actual=pila.peek(); // nos movemos a la posicion que esta en la cima de la pila
		
		if(visit[actual.i][actual.j]){ //si actual no tenia movimientos posibles una iteracion anterior, nos regresamos){
			count--;
			visit[actual.i][actual.j]=false;
			pila.pop();
			continue;
		}
		
		count++; //se hizo un movimiento más
		tour[actual.i][actual.j]=count; //ponemos en tablero el movimiento en el que estamos
		visit[actual.i][actual.j]=true; //ponemos como visitada la posicion actual
		
		for(i=0; i<8; i++){
			next=actual+moves[i]; //candidato a posible movimiento futuro
			
			if(isMove(next) && !visit[next.i][next.j]) //si next es valido y no he visitado esa casilla
				pila.push(next);
		}
	}
	
	for(i=0; i<8; i++){
		for(j=0; j<8; j++)
			cout << tour[i][j] << "\t";
		cout << endl;
	}
	
}

//Observaciones:
//El programa tarda mucho cuando las coordenadas de la posición del caballo están en el centro. Ejemplo: (5,6)
//El codigo funciona muy rápido en las orillas
int main(){
	int x, y;
	cout << "TOUR DEL CABALLO" << endl;
	cout << "Inserta la coordenada inicial del caballo: "<< endl;
	cout <<"inserte la coordenada x: ";
	cin >>x;
	cout <<" "<< endl;
	cout <<"inserte la coordenada y: ";
	cin >>y;
	position start(x,y);
	KnightsTour(start);
	
	return 0;
}
