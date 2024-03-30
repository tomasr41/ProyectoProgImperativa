#include<iostream> 
#include<string>
#include <locale.h>					/*Nos permite utilizar tildes, "�", etc. por pantalla*/
using namespace std;
									
struct NODO{						/*Estructura para los nodos de prestamos*/
	int codigo_prestamo;
	int codigo_categoria;
	int codigo_prestatario;
	bool estado;
	string descripcion;
	NODO *siguiente;

};
NODO * lista = NULL;

struct CATEGORIA {					/*Estructura para los datos de la categor?a*/
	int categoria;
	string descripcion;
};
struct PRESTATARIO {				/*Estructura para los datos del prestatario*/
	int codigo_prestatario;
	string apellido;
	string nombre;
};

/* Dimensión física de para los arreglos */
const int DFcategoria = 100;
const int DFPrestatario = 100;

/*Dimensiones logicas de las distintas variables*/
int DLcategorias = 0;
int contador_prestamos = 0;
int DLprestatarios = 0;

/* Creacion de arreglos estaticos. */
CATEGORIA categorias[DFcategoria];
PRESTATARIO prestatarios[DFPrestatario];

/*Variable de tipo caracter para la utilizacion del menu*/
char opcion;

/*Las siguientes tres funciones muestran listas, las utilizamos para probar el funcionamiento del programa, y creemos que serán útiles para el usuario.

/*Muestra en pantalla un listado de las categorías.
Recibe como parametros el arreglo "categorias" y su dimensión lógica
Retorna: void*/
void listar_categorias(CATEGORIA categorias[],int dl){
	char cat;
	if (dl != 0) {
		cout <<endl;
		cout << "Si desea ver la lista de categorias(S/N): "; 	cin >> cat;
		cout <<endl;
		if (cat == 's' || cat == 'S') {
			cout << "Categorias:" << endl;
			for (int i = 0; i < dl; i++) {
				cout << categorias[i].categoria; cout << " // ";
				cout << categorias[i].descripcion << endl;
			}
			cout <<endl;
		}
	}
/*Si existen categorias, mediante una estructura for, muestra cada elemento del arreglo "categorias"*/
};

/*Muestra en pantalla un listado de los prestatarios.
Recibe como parametros el arreglo "prestatarios" y su dimensión lógica
Retorna: void*/
void listar_prestatarios(PRESTATARIO prestatarios[], int dl) {
	char cat;
	if(dl!=0){
		cout <<endl;
		cout << "Si desea ver la lista de prestatarios(S/N): "; cin >> cat;
		cout <<endl;
		if (cat == 's' || cat == 'S') {
			if (dl != 0) {
				cout <<endl;
				cout << "Prestatarios:" << endl;
				for (int i = 0; i < dl; i++) {
					cout << prestatarios[i].codigo_prestatario; cout << " // ";
					cout << prestatarios[i].apellido; cout << " ";
					cout << prestatarios[i].nombre << endl;
				}
			}
		}	
	}
	/*Si existen prestatarios, mediante una estructura for, muestra cada elemento del arreglo "prestatarios"*/
};

/*Declaración de funciones que se ejecutarán según la opción seleccionada por el usuario en el menú, en las de tipo int dejamos return 0; para que el programa funcione.*/




/*Muestra los prestamos cargados*/
/*Recorre la estructura con otra del mismo tipo e imprime los datos*/
void Mostrar_Lista(NODO *&lista){
	cout<<"Prestamos: "<<endl;
	NODO *actual = new NODO();

	actual = lista;
	if (lista != NULL){
		while(actual != NULL){
			cout<< actual->codigo_prestamo<<" = ";
			cout<< categorias[actual->codigo_categoria].descripcion<<" -> ";
			cout<< prestatarios[actual->codigo_prestatario].nombre<<" "<<prestatarios[actual->codigo_prestatario].apellido<<" -> ";
			if(actual->estado==true){
				cout<<"True"<<" -> ";
			}
			else{
				cout<<"False"<<" -> ";
			}
			cout<< actual->descripcion<<endl;
			actual = actual->siguiente;	
		}	
		
	}
	else{
		cout<<"No hay prestamos cargados actualmente. "<<endl;
	}
}



/*El usuario agrega una categoría, se solicita ingresar una descripción que será almacenada en el arreglo "categorías".
Toma como parámetro al arreglo “categorias” y su dimensión lógica.
Retorno: DL */

int Agregar_categoria(CATEGORIA categorias[], int dl) {
	listar_categorias(categorias, DLcategorias); /*Llamada a la funcion listar categorias)*/
	string desc;
	if (dl != 0) {
		cout << "===Nueva Categoria=== " << endl;
		cout << "Ingrese Descripcion(Salir x): "; cin >> desc;
		cout <<endl;
		while (desc != "x" && desc != "X" && (dl < DFcategoria)) {
			categorias[dl].categoria = categorias[dl - 1].categoria + 1;
			categorias[dl].descripcion = desc;
			cout << "===Nueva Categoria===" << endl;
			cout << "Ingrese Descripcion (Salir x): "; cin >> desc;
			cout <<endl;
			dl++;
		}
	}
	else {
		cout << "===Nueva Categoria===" << endl;
		cout << "Ingrese Descripcion(Salir x): "; cin >> desc;
		cout <<endl;
		while (desc != "x" && desc != "X" && (dl < DFcategoria)) {
			categorias[dl].categoria = dl;
			categorias[dl].descripcion = desc;
			cout << "===Nueva Categoria===" << endl;
			cout << "Ingrese Descripcion (Salir x): "; cin >> desc;
			cout <<endl;
			dl++;
		}
	}
	return dl;
	/*Mediante una estructura de control while genera un codigo de categoría automáticamente y pedirá al usuario que ingrese una descripción para la misma*/
};




/*Al usuario se le pedirá introducir un código de alguna de las categorías  para poder modificarlas.
Toma como parámetro al arreglo "categorias" y su dimensión lógica.
Retorno: void. */
void Modificar_categoria(CATEGORIA categorias[], int dl) {
	listar_categorias(categorias, dl);
	int cod;
	string desc;
	cout << "Ingrese la Categoria a Modificar: ";
	cin >> cod;
	for (int i = 0; i < dl; i++) {
		if (categorias[i].categoria == cod) {
			cout << "Ingrese la Nueva Descripcion: "; cin >> desc;
			categorias[i].descripcion = desc;
		}
	}
	/*Solicita al usuario ingresar el código de categoría que quiere modificar, con una estructura for recorre el arreglo, y con un condicional se verificará la existencia de la categoría(mediante el código) y permitirá modificar su descripción.*/
};

/*El usuario podrá eliminar una categoría anteriormente ingresada (se eliminan los elemento  del arreglo "categorias")
Toma como parámetro al arreglo “categorías” y a la dimensión lógica. Siempre y cuando la categoria a eliminar no se este utilizando en un prestamo pendiente.
Retorno: DL */
int Eliminar_categoria(CATEGORIA categorias[], int dl) {
	listar_categorias(categorias, dl);
	int i = 0;
	int l, cod;
	char a;
	a = 'S';
	cout << "Ingrese el codigo de Categoria a Eliminar: ";
	cin >> cod;
	while (i < dl && categorias[i].categoria != cod) {
		i++;
	}
	NODO *actual = new NODO();
	actual = lista;
	while(actual != NULL){
		if(categorias[i].categoria == actual->codigo_categoria){
			cout << endl;
			cout << "Esta Categoria no se puede Eliminar porque esta siendo utilizada en un Prestamo..." << endl;
			a = 'N';
			break;
		}
		actual = actual->siguiente;	
	}
	if (categorias[i].categoria == cod && a != 'N') {
		for (int j = i; j < dl - 1; j++)
		{
			categorias[j] = categorias[j + 1];
		}
		dl--;
		cout << endl;
		cout << "Categoria Eliminada Correctamente";
		cout << endl;
	}
	return dl;

	/*Se le solicita al usuario ingresar el código de categoría a eliminar.
	Mediante la estructura while, localiza el elemento (código) igual al que ingresó el usuario y le otorga un valor de índice.
	Luego, utiliza una estructura while para recorrer los préstamos y verificar que no existan préstamos activos con la categoría que se solicita eliminar(Utilizamos una variable de carácter para control(Si el valor cambia a N, se detiene la función)
	Verifica la coincidencia del código de categoría con el ingresado por el usuario, y el valor de "a"(Para saber si se encuentra en préstamos), suplantar cada arreglo en un índice por el índice+1 desde el que el usuario decidió eliminar*/
};


/*El usuario podrá agregar un prestatario ingresando un apellido y luego de un nombre, serán almacenados en el arreglo "prestatarios".
Toma como parámetro al arreglo "prestatarios"y a la dimensión lógica,
Retorno: DL*/
int Agregar_prestatario(PRESTATARIO prestatarios[], int dl) {
    listar_prestatarios(prestatarios, dl);
    string leer;
    int i;
    cout << endl;
    cout << "===Nuevo Prestatario===" << endl;
    cout << "Ingrese el Apellido (Salir x): ";
    getline(cin >> ws, leer);
    if (dl != 0) {
        while (leer.length() > 1 && dl < DFPrestatario) {
            leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
            prestatarios[dl].codigo_prestatario = prestatarios[dl - 1].codigo_prestatario + 1;
            prestatarios[dl].apellido = leer;
            cout << endl << "Ingrese el Nombre: ";
            getline(cin >> ws, leer);
            leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
            prestatarios[dl].nombre = leer;
            cout << endl;
            cout << "===Nuevo Prestatario===" << endl;
            cout << "Ingrese el Apellido (Salir x): ";
            getline(cin >> ws, leer);
            dl++;
        };
    }
    else {
        while (leer.length() > 1 && dl < DFPrestatario) {
            leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
            prestatarios[dl].codigo_prestatario = dl;
            prestatarios[dl].apellido = leer;
            cout << endl << "Ingrese el Nombre: ";
            getline(cin >> ws, leer);
            leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
            prestatarios[dl].nombre = leer;
            cout << endl;
            cout << "===Nuevo Prestatario===" << endl;
            cout << "Ingrese el Apellido (Salir x): ";
            getline(cin >> ws, leer);
            dl++;
        };
    }

    return dl;
	/*Mediante una estructura de control while genera un codigo de prestatario automaticamente y pedirá al usuario que ingrese un apellido y un nombre para el mismo*/
};

/*El usuario podrá modificar alguno de los prestatarios ya ingresados, ya sea, el apellido o el nombre.
Toma como parámetro al arreglo "prestatarios" y su dimensión lógica.
Retorno: void. */
void Modificar_prestatario(PRESTATARIO prestatarios[], int dl) {
	listar_prestatarios(prestatarios, dl);
	int cod;
	string leer;
	cout << "Ingrese el Prestatario a Modificar: ";
	cin >> cod;
	for (int i = 0; i < dl; i++) {
		if (prestatarios[i].codigo_prestatario == cod) {
			cout << "Ingrese el Nuevo Apellido: "; getline(cin >> ws, leer); /*Apellido y nombre tiene que tener la primer letra en mayusculas*/
			leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
			prestatarios[i].apellido = leer;
			cout << "Ingrese el Nuevo Nombre: "; getline(cin >> ws, leer);
			leer[0]=toupper(leer[0]);
			for(int j=1;j<leer.size();j++){
				if(leer[j]==' '){
					leer[j+1]=toupper(leer[j+1]);
					j=j+1;
					continue;
				}
				leer[j]=tolower(leer[j]);
			}
			prestatarios[i].nombre = leer;
		}
	}
	/*Solicita al usuario ingresar el código de prestatario que quiere modificar, con una estructura for recorre el arreglo, y con un condicional se verificará la existencia de la categoría(mediante el codigo) y permitira modificar su apellido y/o nombre*/
};

/*El usuario podrá eliminar a un prestatario anteriormente ingresado (se elimina el elemento seleccionado del arreglo "prestatarios").
Toma como parámetro al arreglo “prestatarios” y a su dimensión lógica. Siempre y cuando el prestatario a eliminar no se este utilizando en un prestamo pendiente.
Retorno: DL */
int Eliminar_prestatario(PRESTATARIO prestatarios[], int dl) {
	listar_prestatarios(prestatarios, dl);
	int i = 0;
	int l, cod;
	char a;
	a = 'g';
	cout << "Ingrese el código de prestatario a eliminar: ";
	cin >> cod;
	while (i < dl && prestatarios[i].codigo_prestatario != cod) {
		i++;
	}
	
	NODO *actual = new NODO();
	actual = lista;
	while(actual != NULL){
		if(cod == actual->codigo_prestatario && actual->estado==true){
			cout << endl;
			cout << "Este prestatario no se puede eliminar porque tiene prestamos pendientes..." << endl;
			a = 'N';
			break;
		}
		actual = actual->siguiente;	
	}

	if (prestatarios[i].codigo_prestatario == cod && a != 'N') {
		for (int j = i; j < dl - 1; j++)
		{
			prestatarios[j] = prestatarios[j + 1];
		}
		dl--;
		cout << endl;
		cout << "Prestatario Eliminado Correctamente.";
		cout << endl;
	}
	return dl;
	/*Se le solicita al usuario ingresar el código de prestatario a eliminar.
	Mediante la estructura while, localiza el elemento (código) igual al que ingresó el usuario y le otorga un valor de índice.
	Luego, utiliza una estructura while para recorrer los préstamos y verificar que no existan préstamos activos para el prestatario que se solicita eliminar(Utilizamos una variable de carácter para control(Si el valor cambia a N, se detiene la función)
	Verifica la coincidencia del código de prestatario con el ingresado por el usuario, y el valor de "a"(Para saber si se encuentra en préstamos), suplantar cada arreglo en un índice por el índice+1 desde el que el usuario decidió eliminar*/
};

/*Esta funcion es utilizada para agregar nuevos elementos del tipo NODO a la lsita de prestamos, recibe los datos necesarios que conforman un prestamo.
Retorno: entero*/

int Insertar_Lista(NODO *&lista,int c_cat, int c_prest, bool estado, string desc){
	NODO *nuevo_nodo =new NODO();
	
	nuevo_nodo->codigo_prestamo = contador_prestamos;
	nuevo_nodo->codigo_categoria = c_cat;
	nuevo_nodo->codigo_prestatario = c_prest;
	nuevo_nodo->estado = estado;
	nuevo_nodo->descripcion = desc;

	NODO *aux1 = lista;
	NODO *aux2;

	while(aux1 != NULL){
		aux2 = aux1;
		aux1= aux1->siguiente; 
	}
	if (lista==aux1){
		lista = nuevo_nodo;
	}
	else{
		aux2->siguiente=nuevo_nodo;
	}
	nuevo_nodo->siguiente= aux1;
	cout<< "Elemento insertado correctamente" << endl;
	contador_prestamos++;
	return contador_prestamos;
};

/*Permite almacenar préstamos, pide al usuario el ingreso de un código de categoría y un código de prestatario. Luego, una descripción sobre el préstamo. El préstamo será almacenado en la lista "prestamos"
Retorno: void*/

void Agregar_prestamo() {
    Mostrar_Lista(lista);
    int cod, i, cod_categoria,cod_prestatario;
    string desc;
	bool estado;
    char a,e,afir;
    a = 'n';
    e = 'n';
    cout << "Si desea ingresar un prestamo(S/N): "; cin >> afir;
    while (afir == 's' || afir == 'S'){
    	a = 'n';
    	e = 'n';
        cout << endl;
        cout << "Ingrese un codigo de categoria: "; cin >> cod;
        for (i = 0; i < DLcategorias; i++) {
            if (categorias[i].categoria == cod) {
				cod_categoria=cod;
                a = 'g';
                break;
            }
        }
        if (a == 'n') {
            cout << endl;
            cout << "No se encontro la categoria a la que quiere asignar un prestamo..." << endl;
            break;
        }
        cout << endl;
        cout << "Ingrese un codigo de prestatario: "; cin >> cod;
        for (i = 0; i < DLprestatarios; i++) {
            if (prestatarios[i].codigo_prestatario == cod) {
            	cod_prestatario=cod;
                e = 'g';
                break;
            }
        }
        if (e == 'n') {
            cout << endl;
            cout << "No se encontro el prestatario al que quiere asignarle un prestamo..." << endl;
            break;
        }
		estado=true;
        cout << endl;
        cout << "Ingrese descripcion: ";
        getline(cin >> ws, desc);
        cout << endl;
        Insertar_Lista(lista, cod_categoria, cod_prestatario, estado, desc);
        cout << "Desea ingresar un prestamo?(S/N): "; cin >> afir;
    }
	/*Se le solicita al usuario si desea ingresar un préstamo
	Mediante una estructura de control while se le pedirá al usuario que ingrese el codigo de categoria, codigo de prestatario y una descripción
	Automáticamente colocará el estado activo(true) para el prestamo*/
};

/*El usuario podrá seleccionar un préstamo para poder modificarlos.
Retorno: void. */
void Modificar_prestamo() {
	listar_categorias(categorias, DLcategorias);
	listar_prestatarios(prestatarios, DLprestatarios);
	Mostrar_Lista(lista);
	int e;
	char a;a='n';
	string leer;
	cout << "Ingrese el Prestamo a Modificar: ";
	cin >> e;
	NODO *actual = new NODO();
	actual = lista;
	while(actual != NULL){
		if(actual->codigo_prestamo==e){
			cout << "Ingrese la nueva Descripcion: ";  getline(cin >> ws, leer);
			actual->descripcion=leer;
			a='g';
			break;
		}
		actual = actual->siguiente;	
	}
	if(a=='n'){
		cout << "No se pudo modificar, el prestamos no existe.";
	}

	/*Solicita al usuario ingresar que préstamo quiere modificar
	Verifica su existencia mediante una estructura while, utilizando su codigo_prestamo
	Si se encuentra una coincidencia, se le solicita al usuario ingresar la nueva descripción.*/
};

/*El usuario podr� eliminar un pr�stamo anteriormente ingresado (se elimina el elemento seleccionado de la lista "prestamos").
Toma como par�metro al la lista de "prestamos".
Retorno: void*/

void eliminar_prestamo_de_la_lista(NODO*&inicio, int &contador_prestamos) {
	int cod;
	char a;a='n';
	Mostrar_Lista(inicio);
	cout<<endl;
	cout << "Ingrese el codigo de Prestamo a Eliminar: ";
	cin >> cod;
	
	NODO *actual = new NODO();
	actual = lista;
	while(actual != NULL){
		if(actual->codigo_prestamo==cod && actual->estado==false){
			a='g';
			break;
		}
		actual = actual->siguiente;	
	}
	if (inicio != NULL && a=='g') {
		NODO* aux = inicio;
		if (inicio->codigo_prestamo == cod) {
			inicio = inicio->siguiente;
			cout<<"Eliminado correctamente."<<endl;
			/*contador_prestamos--;*/
			delete aux;
		}
		else {
			while (aux->siguiente != NULL && aux->siguiente->codigo_prestamo != cod) {
			aux = aux->siguiente;
			}
			if (aux->siguiente->codigo_prestamo == cod) {
				NODO* aEliminar = aux->siguiente;
				aux->siguiente = aEliminar->siguiente;
				cout<<"Eliminado correctamente."<<endl;
				/*	contador_prestamos--;*/
				delete aEliminar;
			}
		}
	}
	if(a=='n'){
		cout<<"El prestamo No esta cargado o se encuentra pendiente."<<endl;
	}
	/* Se le solicita al usuario ingresar el código de prestamo a eliminar.
	Mediante la estructura while, localiza el elemento igual al que ingresó el usuario y se verifica que el prestamo no est� en estado pendiente, para poder posteriormente eliminarlo.
	y el valor de "a"(Para saber si se encuentra el préstamos)*/
}

/*La función permitirá al usuario cambiar el valor de estado del préstamo a “false”
Retorno: void */
void Devolver_prestamo() {
	Mostrar_Lista(lista);
    int e;
	char a;
	a='n';
    cout << "Devolver Prestamo" << endl;
    cout << "Ingrese un codigo de Prestamo: ";
    cin >> e;
	NODO *actual = new NODO();
	actual = lista;
	while(actual != NULL){
		if(actual->codigo_prestamo==e){
			actual->estado=false;
			a='g';
			break;
		}
		actual = actual->siguiente;	
	}

    cout << endl;
    if (a=='g'){
        cout << "Prestamo Devuelto Correctamente." << endl;
    }
    else{
        cout << "No se pudo devolver el prestamo" << endl;
    }
    /*El usuario podra ver la lista de prestamos, y con ello ver cuales se encuentran pendietes y cuales no,
	se le pedira el ingreso del deseado a devolver y posteriormente se busca para cambiar de estado ese parametro en el elemento.*/
};


/* El usuario podrá ver una lista de las categorías y la cantidad de objetos que se prestaron en cada una.
Toma como parámetro al arreglo "categorias", recorre la lista de prestamos, llevando una cuenta de el total pendiente.
Retorno: void */
void Cantidad_de_objetos_prestados_por_categoria(CATEGORIA categorias[], int dl3) {
	int contador;
	int contador_prestamosp;
	contador_prestamosp=0;
	for (int i = 0; i < DLcategorias; i++) {
		contador = 0;
		
		NODO *actual = new NODO();
		actual = lista;
		while(actual != NULL){
			if((categorias[i].categoria==actual->codigo_categoria)&&(actual->estado==true)){
				contador++;
				contador_prestamosp++;
			}
			if((categorias[i].categoria==actual->codigo_categoria)&&(actual->estado==false)){
				contador++;
			}
			actual = actual->siguiente;	
		}
	
		if (contador >= 0) {	
			cout << "Hay " << contador << " " << categorias[i].descripcion << " prestados." << endl;
		}
	}
	cout << "El total de Prestamos Pendiendes es: " << contador_prestamosp << endl;
};

/* Ordena el arreglo de categorias dejandolos ordenados alfabeticamente de manera ascendente.
No recibe parametros.
Retorna Void */
void Ordenar_categoria() {
	CATEGORIA aux;
    int ubicacion;
    
    for (int i = 0; i < DLcategorias; i++) {
        for (int j = i + 1; j < DLcategorias; j++)
        {
            if (categorias[i].descripcion > categorias[j].descripcion) {
                aux = categorias[i];
                categorias[i]  = categorias[j];
                categorias[j] = aux;
            }
        }

    }
};

/* Ordena el arreglo de categorias dejandolos ordenados de forma numerica de menor a mayor.
No recibe parametros.
Retorna Void */
void Ordenar_categoria_original() {
	CATEGORIA aux;
    int ubicacion;
    
    for (int i = 0; i < DLcategorias; i++) {
        for (int j = i + 1; j < DLcategorias; j++)
        {
            if (categorias[i].categoria > categorias[j].categoria) {
                aux = categorias[i];
                categorias[i]  = categorias[j];
                categorias[j] = aux;
            }
        }

    }
};


/* Imprime los prestamos Ordenados por categorias
No recibe parametros
Retorna void */
void ordenar_por_categoria() {
	Ordenar_categoria();
    char a;a='n';
	if(DLcategorias!=0){
		for (int i = 0; i < DLcategorias; i++) {
	        cout << "Categoria: " << categorias[i].descripcion; cout << " // "<<endl;
	        NODO *actual = new NODO();
			actual = lista;
			while(actual != NULL){
				if(actual->codigo_categoria==categorias[i].categoria){
					a='g';
					cout<<endl;
					cout << "             Prestatario: " << prestatarios[actual->codigo_prestatario].apellido; cout << " "; cout << prestatarios[actual->codigo_prestatario].nombre << " // ";
					cout << "  El objeto prestado es: " << actual->descripcion; cout << " // ";
					if (actual->estado == true) {
			        	cout << "Activo"; cout << endl;
			    	}
			     	else{
			      		cout << "Inactivo"; cout << endl;
			        }
			
				}
				actual = actual->siguiente;
			}
			
			if(a=='n'){
					cout<<"Esta categoria no fue utilizada."<<endl;
			}
	        	a='n';
	    }
		Ordenar_categoria_original();
	}
	else{
		cout<<"No hay categorias cargadas."<<endl;
	}
	/* Hace una llamada a la funcion "Ordenar_categoria()", una vez ordenada mediante el uso de estructuras de control imprime por pantalla los elementos de los prestamos 
 Luego de imprimir estos datos, reordena las categorias(Ordenar_categoria_original()) pero de manera que quden igual que al inicio de la funcion */   
};

/* Ordena el arreglo prestatarios dejandolos ordenados alfabeticamente de manera ascendente.
No recibe parametros.
Retorna Void */
void Ordenar_prestatario() {
	PRESTATARIO aux;
    int ubicacion;
    for (int i = 0; i < DLprestatarios; i++) {
        for (int j =i+1; j < DLprestatarios; j++)
        {
        if ((prestatarios[i].apellido > prestatarios[j].apellido) || (prestatarios[i].apellido == prestatarios[j].apellido && prestatarios[i].nombre > prestatarios[j].nombre)) {
                        aux = prestatarios[i];
                        prestatarios[i] = prestatarios[j];
                        prestatarios[j] = aux;
                }
        }
        
    }
	/* Con el uso de la estructura for e if se intercambian de lugar los elementos del arreglo prestatario utilizando un arreglo auxiliar.  */	
};

/* Ordena el arreglo de prestatarios dejandolos ordenados de forma numerica de menor a mayor.
No recibe parametros.
Retorna Void */
void Ordenar_prestatario_original(){
	PRESTATARIO aux;
    int ubicacion;
    for (int i = 0; i < DLprestatarios; i++) {
        for (int j =i+1; j < DLprestatarios; j++){
        	if (prestatarios[i].codigo_prestatario > prestatarios[j].codigo_prestatario) {
                    aux = prestatarios[i];
                    prestatarios[i] = prestatarios[j];
                 	prestatarios[j] = aux;
                }
        }
        
    }
	/* Con el uso de la estructura for e if se intercambian de lugar los elementos del arreglo prestatario utilizando un arreglo auxiliar.  */	
};	



/* Imprime los prestamos Ordenados por prestatarios
No recibe parametros
Retorna void */
void ordenar_por_prestatarios() {
	
	Ordenar_prestatario();
	char a;a='n';
	if(DLprestatarios!=0){
		for (int i = 0; i < DLprestatarios; i++) {
	        cout << "Prestatario: " << prestatarios[i].apellido<<" "<< prestatarios[i].nombre;cout << " // "<<endl;
	        NODO *actual = new NODO();
			actual = lista;
			while(actual != NULL){
				if(actual->codigo_prestatario==prestatarios[i].codigo_prestatario){
					a='g';
					cout<<endl;
					cout << "             Categoria: " << categorias[actual->codigo_categoria].descripcion; cout << " ";
					cout << "  El objeto prestado es: " << actual->descripcion; cout << " // ";
					if (actual->estado == true) {
			        	cout << "Activo"; cout << endl;
			    	}
			     	else{
			      		cout << "Inactivo"; cout << endl;
			        }
			
				}
				actual = actual->siguiente;
			}
			if(a=='n'){
					cout<<"Este prestatario no tiene prestamos asignados."<<endl;
			}
	        	a='n';
	    }
		 Ordenar_prestatario_original();
	}
	else{
			cout<<"No hay prestatarios cargados."<<endl;
	}
 /* Hace una llamada a la funcion "Ordenar_prestatario()", una vez ordenada mediante el uso de estructuras de control imprime por pantalla los elementos de los prestamos 
 Luego de imprimir estos datos, reordena los prestatarios (Ordenar_prestatario_original())pero de manera que quden igual que al inicio de la funcion */   
};
void Listado_de_prestamos_ordenados_por_categoria_o_prestatario(PRESTATARIO prestatarios[], int dlprestatarios, CATEGORIA categorias[], int dlcategorias) {
    cout << "========Consultar Prestamos========" << endl; 
    cout << "a. Listado de Prestamos por Categoria" << endl;
    cout << "b. Listado de Prestamos por Prestatario" << endl;
    cout << "c. Atras" << endl;
    cout << "===================================" << endl;
    cin >> opcion;
    switch (tolower(opcion)) {
    case 'a':
		ordenar_por_categoria();
        break;
    case 'b':
        ordenar_por_prestatarios();
        break;
    default:
        break;
    }
};

/* El usuario podrá ver una lista que mostrará los préstamos que se hayan hecho en cada categoría.
Toma como parámetro al arreglo "prestamos", al arreglo "categorías" y a la dimensión lógica.
Retorno: void */
void Listado_de_prestamos_por_categoria(CATEGORIA categorias[], int dl3) {
	int cat;
	char a,b; a='n';b='n';
	cout << endl << "Codigo de categoria Elegida: ";
	cin>>cat;
	cout<< endl;
	for (int i=0;i<DLcategorias;i++){
		if (categorias[i].categoria == cat){
			a='g';
			cout<<endl;
			cout << "Los prestamos pendientes de la categoria " << categorias[i].descripcion << " son: " << endl;
			cout<< endl;
			
			NODO *actual = new NODO();
			actual = lista;
			while(actual != NULL){
				if((cat==actual->codigo_categoria)&&(actual->estado==true)){
					b='g';
					cout << actual->descripcion<< ", prestado a " << prestatarios[actual->codigo_prestatario].nombre << " " << prestatarios[actual->codigo_prestatario].apellido << endl;
					cout<< endl;
				}
				actual = actual->siguiente;	
			}
			
			a='g';
			if(b=='n'){
				cout<< endl;
				cout << "La categoria elegida no tiene prestamos asignados.";
				cout<< endl;
			}
		}
	}
	if(a=='n'){
		cout<< endl;
		cout << "La categoria elegida no existe.";
		cout<< endl;
	}
};

/*El usuario podrá ver una lista de todos los prestatarios que hayan prestado al menos un objeto.
Toma como parámetro al arreglo "prestamos", al arreglo "prestatarios" y a la dimensión lógica.
Retorno: void */
void Listar_todos_los_prestatarios_que_tienen_al_menos_un_objeto_prestado(PRESTATARIO prestatarios[], int dl2) {
	int contador;
	if(DLprestatarios!=0){
			cout<<endl;
			cout<<"Listado de prestatarios con almenos un prestamo pendiente: "<<endl;
			cout<<endl;
		for (int i = 0; i < DLprestatarios; i++) {
			contador = 0;
			
			NODO *actual = new NODO();
			actual = lista;
			while(actual != NULL){
				if((prestatarios[i].codigo_prestatario==actual->codigo_prestatario)&&(actual->estado==true)){
					contador++;
				
				}
				actual = actual->siguiente;	
			}

			if (contador != 0) {
				cout << prestatarios[i].nombre << " ";
				cout << prestatarios[i].apellido << " // ";
				cout << "prestamos: ";
				cout << contador <<endl;
			}
		}
	}
	else{
		cout<<endl;
		cout << "No tiene prestatarios cargados." <<endl;
		cout<<endl;	
	}
};

/*Funciones de menu modularizado*/

void MenuAdministracionyconsulta() {
	do
	{
		cout << "\n =Administrar y consultar Categorias y Prestatarios=";
		cout <<endl;
		cout << "\n a. Agregar Categoria";
		cout << "\n b. Modificar Categoria";
		cout << "\n c. Eliminar Categoria";
		cout << "\n d. Agregar Prestatario";
		cout << "\n e. Modificar Prestatario";
		cout << "\n f. Eliminar Prestatario";
		cout << "\n g. Salir";
		cout <<endl;
		cout << "\n ===================================================";
		cout << "\n"; cin >> opcion;
		switch (tolower(opcion)) { /*Llamada de funciones de la seccion "Administrar y consultar categorias y prestatarios.
									Dimension logica=**, ya que el valor de la misma tiene que cambiar si agregamos o eliminamos elementos. */
		case 'a':
			DLcategorias = Agregar_categoria(categorias, DLcategorias);
			break;
		case 'b':
			Modificar_categoria(categorias, DLcategorias);
			break;
		case 'c':
			DLcategorias = Eliminar_categoria(categorias, DLcategorias);
			break;
		case 'd':
			DLprestatarios = Agregar_prestatario(prestatarios, DLprestatarios);
			break;
		case 'e':
			Modificar_prestatario(prestatarios, DLprestatarios);
			break;
		case 'f':
			DLprestatarios = Eliminar_prestatario(prestatarios, DLprestatarios);
			break;
		default:
			break;
		}
	} while (tolower(opcion) != 'g');

}

void AdministrarPrestamos() {
	do
	{
		cout << "\n =======Administrar Prestamos=======";
		cout <<endl;
		cout << "\n a. Agregar Prestamos";
		cout << "\n b. Modificar Prestamos";
		cout << "\n c. Eliminar Prestamos ";
		cout << "\n d. Devolver Prestamos ";
		cout << "\n e. Salir ";
		cout <<endl;
		cout << "\n ===================================";
		cout << "\n"; cin >> opcion;
		switch (tolower(opcion)) {/*LLamada de las funciones de "Administrar prestamos"*/
		case 'a':
			Agregar_prestamo();
			break;
		case 'b':
			Modificar_prestamo();
			break;
		case 'c':
			eliminar_prestamo_de_la_lista(lista,contador_prestamos);
			break;
		case 'd':
			Devolver_prestamo();
			break;
		default:
			break;
		}
	} while (tolower(opcion) != 'e');

}

void consultarprestamos() {
    do
    {
        cout << "\n ========Consultar Prestamos==============================================";
        cout << endl;
        cout << "\n a. Cantidad de objetos prestados por Categoria ";
        cout << "\n b. Listado de Prestamos por Categoria ";
        cout << "\n c. Listado de Prestamos ordenados por Categoria o Prestatario ";
        cout << "\n d. Listar todos los Prestatarios que tienen al menos un objeto Prestado";
        cout << "\n e. Salir ";
        cout << endl;
        cout << "\n =========================================================================";
        cout << "\n"; cin >> opcion;
        switch (tolower(opcion)) {/*Llamada de las funciones de "Consultar préstamos"*/
        case 'a':
            if(DLcategorias!=0){
                Cantidad_de_objetos_prestados_por_categoria(categorias, DLcategorias);
            }
            else{
                cout<<endl;
                cout<< "No tiene categorias cargadas"<<endl;
                cout<<endl;
            }
            break;
        case 'b':
            if(DLcategorias!=0){
                listar_categorias(categorias, DLcategorias);
                Listado_de_prestamos_por_categoria(categorias, DLcategorias);
            }
            else{
                cout<<endl;
                cout<< "No tiene categorias cargadas"<<endl;
                cout<<endl;
            }
            break;
        case 'c':
            Listado_de_prestamos_ordenados_por_categoria_o_prestatario(prestatarios, DLprestatarios, categorias, DLcategorias);
            break;
        case 'd':
            Listar_todos_los_prestatarios_que_tienen_al_menos_un_objeto_prestado(prestatarios, DLprestatarios);
            break;
        default:
            break;
        }
    } while (tolower(opcion) != 'e');

}

int main() {
	setlocale(LC_ALL, "");/*Nos permite utilizar tildes, "�", etc. por pantalla*/
	
	/*menú principal, el usuario deberá elegir entre sus opciones*/
	do {

		cout << "\n ==========Menu Principal===========";
		cout << "\n";
		cout << "\n 1. Administrar y consultar Categorias y Prestatarios ";
		cout << "\n 2. Administrar Prestamos ";
		cout << "\n 3. Consultar Prestamos ";
		cout << "\n 4. Salir ";
		cout << "\n";
		cout << "\n ===================================";
		cout << "\n"; cin >> opcion;

		switch (toupper(opcion)) /*Switch para iniciar los distintos menús secundarios*/
		{
		case '1':
			MenuAdministracionyconsulta();
			break;
		case '2':
			AdministrarPrestamos();
			break;
		case '3':
			consultarprestamos();
			break;
		}

	} while (toupper(opcion) != '4');
	cout<<endl;
	cout<<"==============================================="<<endl;
	cout<<"===PROGRAMA FINALIZADO========================="<<endl;
	cout<<"==========================QUE TENGA BUEN DIA==="<<endl;
	cout<<"==============================================="<<endl;
	cout<<"=====================:)========================"<<endl;
	cout<<"==============================================="<<endl;
	cout<<endl;
	return 0;
}
