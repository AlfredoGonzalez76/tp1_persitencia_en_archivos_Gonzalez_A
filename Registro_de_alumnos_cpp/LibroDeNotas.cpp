#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cmath>
using namespace std;

//--------------  Tipos de datos Introducidos  -----------------

const int Dimension = 50;

typedef struct {
   string nombres;
   string apellidos;
   int edad;
   int dni;
   int nota;
} tEstudiante;


typedef tEstudiante tArray[Dimension];

typedef struct {
   tArray elementos;
   int contador;
} tLista;


// En caso de utilizar archivos de texto la informacion se guarda y lee de la sig. manera:
// un campo por cada línea y cada registro de la lista debajo del anterior.

//------------------  Declaracion de Funciones Propias   ------------------------

int menu();

bool fileIsOk(string fileName);

tLista leerListaDeArchivo(string nombreArch);

void mostrarListado(tLista& listita);

void muestraRegistroCompleto(tLista& listita, int posicion);

void mostrarListadoConNotas(tLista& listita);

void ingresaRegistro(tLista& listaAlumnos);

void modificaRegistro(tLista& listita, int posicion);

void buscaRegistros(tLista& listita, string fragmento);

bool In(string fragmento, string palabra);

void eliminaRegistro(tLista& listaAlumnos, int posicion);

void ejecutar(int opcion, tLista& listita, string nombreArch);

void escribeListaEnArchivo(string nombreArch, tLista& listita);

string mayuscula(string cadena);


//----------------- Funciones Estadisticas -----------------------

void estadistica(tLista& listita);

double media(tLista& listita);

double varianza(tLista& listita);

double desvio(tLista& listita);

int maxima(tLista& listita);

int minima(tLista& listita);

int moda(tLista& listita);

double medianaPorBurbuja(tLista& listita);


//------------------------  Principal  ---------------------------

int main()
{
	string nombreArchivo = ".//AyEDI.txt";
	tLista lista;
	int opcion;

// Aquí va a tener que preguntar si el archivo nombreArchivo existe. Caso contrario lo creará y lo cerrará.

	if(fileIsOk(nombreArchivo))
	{
		lista = leerListaDeArchivo(nombreArchivo);  // Si no existía al comienzo, ahora estará vacío.

		do
		{
			opcion = menu();
			ejecutar(opcion, lista, nombreArchivo);
		}while(opcion != 8);	
	}
	else
	{
		cout << "Revise porque no se encuentra el archivo" << endl;
	}

	return 0;
}


//----------------- Definicion de Funciones Propias ----------------------

int menu()
{
	int op;
	cout << "-----------------------------------" << endl;
	cout << '|' << "          MENU PRINCIPAL         " << '|' << endl;
	cout << "-----------------------------------" << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 1. Mostrar Listado de Alumnos " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 2. Ingresar un Registro " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 3. Buscar un Registro " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 4. Modificar un Registro " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 5. Eliminar un Registro " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 6. Listado con todos los Datos " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 7. Ver Estadisticas " << '|' << endl;
	cout << '|' << setw(33) <<setiosflags(ios::left) << " 8. Grabar Datos y Salir " << '|' << endl;
	cout << "-----------------------------------" << endl;
	cout << endl;
	cout << "Elija una opcion: ";
	do
	{
		cin >> op;
		cin.ignore(); // Esto evita que quede el \n del Enter en el bufer y el programa se sale el getline del nombre
	}
	while ((op < 1) && (op > 8) );
	cout << endl;
	return op;
}


bool fileIsOk(string fileName)
{
	ifstream myFileIn(fileName.c_str()); // Esto es xq el metodo open() espera una cadena de C, no de C++
	ofstream myNewFile;
	bool rta;
	char op;

	if (myFileIn.good())
	{
		rta = true;
	}
	else
	{
		do
		{
			cout << "Archivo de datos no encontrado. Desea crearlo? (S/N)";
			cin >> op;
			cin.ignore();
		}
		while ((op != 's') && (op != 'S') && (op != 'n') && (op != 'N'));

		rta = ((op == 's')||(op == 'S'));
		if (rta)
		{
			myNewFile.open(fileName);   //
			myNewFile.close();
		}
	}
return rta;
}



tLista leerListaDeArchivo(string nombreArch)
{
	ifstream flujoIn;
	tLista listaAlumnos;

	flujoIn.open(nombreArch);

	if (flujoIn.fail()) // comprueba una conexión fallida
	{
		cout << "\n El archivo no se abrió con éxito"
			 << "\n Por favor compruebe que el archivo realmente exista."
		<< endl;
		exit(1);
	}
	else
	{
		if ( ! flujoIn.eof() )
		{
			listaAlumnos.contador = 0;
			string linea;
			int auxInt;
			while ( ! flujoIn.eof() )
			{		
				getline(flujoIn,linea);
				listaAlumnos.elementos[listaAlumnos.contador].nombres = linea ;

				getline(flujoIn,linea);
				listaAlumnos.elementos[listaAlumnos.contador].apellidos = linea ;
				
				getline(flujoIn,linea);
				auxInt = atoi(linea.c_str());
				listaAlumnos.elementos[listaAlumnos.contador].edad = auxInt ;

				getline(flujoIn,linea);
				auxInt = atoi(linea.c_str());
				listaAlumnos.elementos[listaAlumnos.contador].dni = auxInt ;

				getline(flujoIn,linea);
				auxInt = atoi(linea.c_str());
				listaAlumnos.elementos[listaAlumnos.contador].nota = auxInt ;

            if ((!listaAlumnos.elementos[listaAlumnos.contador].nombres.empty())&&(!listaAlumnos.elementos[listaAlumnos.contador].apellidos.empty()))
            {
               listaAlumnos.contador++;
            }
			}
		}
	}
	flujoIn.close();		

	return listaAlumnos;
}


void mostrarListado(tLista& listita)
{
	if (listita.contador > 0)
	{
		cout << "------------------------------------------------------" << endl ;
		cout << '|' << setw(40) << setiosflags(ios::left) << " Apellidos y Nombres  " << " |" << 
		setw(10) << setiosflags(ios::left) << " Registro" << '|' << endl;
		cout << "------------------------------------------------------" << endl ;

		for (int i = 0; i < listita.contador; ++i)
		{
			cout << "| " << setw(40) <<setiosflags(ios::left) << listita.elementos[i].apellidos + ", " + listita.elementos[i].nombres << "|     " <<
			setw(5) << setiosflags(ios::left) << i << '|' << endl;
		}

		cout << "------------------------------------------------------" << endl ;
		cout << endl;
	}
	else
	{
		cout << "No hay registros para mostrar" << endl;
	}
}

void muestraRegistroCompleto(tLista& listita, int posicion)
{
	cout << "Nombres: " << listita.elementos[posicion].nombres << endl ;
	cout << "Apellidos: " << listita.elementos[posicion].apellidos << endl ;
	cout << "Edad: " << listita.elementos[posicion].edad << endl ;
	cout << "DNI: " << listita.elementos[posicion].dni << endl ;
	cout << "Nota: " << listita.elementos[posicion].nota << endl ;
	cout << "Registro: " << posicion << endl;
	cout << "------------------------------" << endl ;
}

void mostrarListadoConNotas(tLista& listita)
{
	cout << "\n La lista acutal es:" << endl;
	cout << "------------------------------" << endl ;
	for (int i = 0; i < listita.contador; ++i)
	{
		muestraRegistroCompleto(listita,i);
	}
	cout << endl;
}


void ingresaRegistro(tLista& listaAlumnos)
{
	string auxString;

	cout << "Ingrese Nombres del alumno: ";
	getline(cin, listaAlumnos.elementos[listaAlumnos.contador].nombres);

	cout << "Ingrese Apellidos del alumno: ";
	getline(cin, listaAlumnos.elementos[listaAlumnos.contador].apellidos);

	cout << "Ingrese la Edad del alumno: ";
	cin >> auxString;
	cin.ignore();
	listaAlumnos.elementos[listaAlumnos.contador].edad = atoi(auxString.c_str());

	cout << "Ingrese DNI del alumno: ";
	cin >> auxString;
	cin.ignore();
	listaAlumnos.elementos[listaAlumnos.contador].dni = atoi(auxString.c_str());

	cout << "Ingrese la NOTA del alumno: ";
	cin >> auxString;
	cin.ignore();
	listaAlumnos.elementos[listaAlumnos.contador].nota = atoi(auxString.c_str());

	listaAlumnos.contador++;
}

void modificaRegistro(tLista& listita, int posicion)
{
	int opcion;
	string auxString;
	if (posicion < listita.contador)
	{
		do
		{
			muestraRegistroCompleto(listita,posicion);
			cout << " Presione: " << endl;
			cout << " 1) Para modificar Nombres " << endl;
			cout << " 2) Para modificar Apellidos" << endl;
			cout << " 3) Para modificar edad" << endl;
			cout << " 4) Para modificar DNI" << endl;
			cout << " 5) Para modificar nota" << endl;
			cout << " 6) Para terminar modificacion" << endl;
			cout << endl;
			cout << " Digite aqui su opcion: ";
			cin >> opcion;
			cin.ignore();
			cout << endl;

			switch(opcion)
			{
			  case 1:
			     cout << "Nombres: ";
			     getline(cin, listita.elementos[posicion].nombres);
			     cout << endl;
			    break;
			  case 2:
			     cout << "Apellidos: ";
			     getline(cin, listita.elementos[posicion].apellidos);
			     cout << endl;
			    break;
			  case 3:
			  	cout << "Edad: ";
				cin >> auxString;
				cin.ignore();
				listita.elementos[posicion].edad = atoi(auxString.c_str());
			    cout << endl;
			    break;
			  case 4:
			  	cout << "DNI: ";
				cin >> auxString;
				cin.ignore();
				listita.elementos[posicion].dni = atoi(auxString.c_str());
			    cout << endl;
			    break;
			  case 5:
			  	cout << "Nota: ";
				cin >> auxString;
				cin.ignore();
				listita.elementos[posicion].nota = atoi(auxString.c_str());
			    cout << endl;
			    break;
			  case 6:
			  	cout << "Ha terminado de modificar el Registro" << endl;;
			    break;
			  default:
			  	cout << "Opcion incorrecta" << endl;
			  	cout << endl;
			}
		}
		while(opcion != 6);
	}
	else
	{
		cout << "El Registro ingresado no existe." << endl;
	}
	cout << endl;
}


void eliminaRegistro(tLista& listita, int posicion)
{
	if (posicion < listita.contador)
	{
		for (int i = posicion; i < listita.contador; ++i)
		{
			listita.elementos[i] = listita.elementos[i+1];
		}
		listita.contador--;
	}
	else
	{
		cout << "El Registro ingresado no existe." << endl;
	}
}


string mayuscula(string cadena)
{
	for (int i = 0; i < cadena.length(); ++i)
	{
		cadena[i] = toupper(cadena[i]);
	}
	return cadena;
}


bool In(string fragmento, string palabra)
{
	bool esta = false;
	int i = 0, j = 0, aciertos = 0;

	while((i < fragmento.length()) && (j < palabra.length()) && (aciertos < fragmento.length()))
	{
		if(fragmento[i] == palabra[j])
		{
			i++;
			j++;
			aciertos++;
		}
		else
		{
			i = 0;
			aciertos = 0;
			j++;
		}
	}
	esta = (aciertos == fragmento.length());

	return esta;
}


void buscaRegistros(tLista& listita, string fragmento)
{

	for (int i = 0; i < listita.contador; ++i)
	{
		if(In(mayuscula(fragmento),mayuscula(listita.elementos[i].nombres)) || In(mayuscula(fragmento),mayuscula(listita.elementos[i].apellidos)))
		{
			muestraRegistroCompleto(listita, i);
		}

	}

}


//--------------------- ESTADISTICA -------------------

void estadistica(tLista& listita)
{
	cout << "-----------------------------------" << endl;
	cout << '|' << "           ESTADISTICA           " << '|' << endl;
	cout << "-----------------------------------" << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Media:            " << '|' << setw(5) << fixed << setprecision(2) << media(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Varianza:         " << '|' << setw(5) << fixed << setprecision(2) << varianza(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Desvio Estandard: " << '|' << setw(5) << fixed << setprecision(2) << desvio(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Nota Maxima:      " << "| " << setw(4) << maxima(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Nota Minima:      " << "| " << setw(4) << minima(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Moda:             " << "| " << setw(4) << moda(listita) << '|' << endl;
	cout << '|' << setw(27) <<setiosflags(ios::left) << " Mediana:          " << "| " << setw(4) << medianaPorBurbuja(listita) << '|' << endl;
	cout << "-----------------------------------" << endl;
}


double media(tLista& listita)
{
	double acumula = 0;
	if(listita.contador > 0)
	{
		for (int i = 0; i < listita.contador; ++i)
		{
			acumula = acumula + listita.elementos[i].nota;
		}
	}
	else
	{
		cout << "No se han encontrado registros" << endl;
	}
	return (acumula/listita.contador);
}

double varianza(tLista& listita)
{
	double med = media(listita);
	double sigma2 = 0;

	for (int i = 0; i < listita.contador; ++i)
	{
		sigma2 = sigma2 + ((listita.elementos[i].nota - med)*(listita.elementos[i].nota - med));
	}
	return sigma2;
}

double desvio(tLista& listita)
{
	return sqrt(varianza(listita));
}

int maxima(tLista& listita)
{
	int max = 0;

	if(listita.contador > 0)
	{
		for (int i = 0; i < listita.contador; ++i)
		{
			if(listita.elementos[i].nota > max)
			{
				max = listita.elementos[i].nota;
			}
		}
	}
	else
	{
		cout << "No se han encontrado registros" << endl;
	}

	return max;
}


int minima(tLista& listita)
{
	int min = 10;

	if(listita.contador > 0)
	{
		for (int i = 0; i < listita.contador; ++i)
		{
			if(listita.elementos[i].nota < min)
			{
				min = listita.elementos[i].nota;
			}
		}
	}
	else
	{
		cout << "No se han encontrado registros" << endl;
	}

	return min;
}


int moda(tLista& listita)
{
	int notas[11] = {};
	int max = 0, cant = 0;
	for (int i = 0; i < listita.contador; ++i)
	{
		notas[listita.elementos[i].nota]++;
	}
	for (int j = 0; j < 11; ++j)
	{
		if(notas[j] > max)
		{
			cant = notas[j]; // Lo que encuentra es el maximo de las cantidades de cada nota
			max = j;
		}
	}
	return max;
}


void ejecutar(int opcion, tLista& listita, string nombreArch)
{
  	int pos;
  	string fragmento;
	switch(opcion) {
	  case 1:
	     mostrarListado(listita);
	    break;
	  case 2:
	    ingresaRegistro(listita);
	    break;
	  case 3:
	  	cout << "Ingrese al menos un fragmento del nombre o el apellido que busca: ";
	  	getline(cin, fragmento);
	  	cout << endl;
	  	buscaRegistros(listita, fragmento);
	    break;
	  case 4:
	    cout << "Ingrese el numero de Registro a Modificar: ";
	    cin >> pos;
	    cin.ignore();
	    cout << endl;
	    modificaRegistro(listita, pos);
	    break;
	  case 5:
	    cout << "Ingrese el numero de Registro a Eliminar: ";
	    cin >> pos;
	    cin.ignore();
	    cout << endl;
	    eliminaRegistro(listita, pos);
	    break;
	  case 6:
	  	cout << endl;
	  	mostrarListadoConNotas(listita);
	    break;
	  case 7:
	  	cout << endl;
	  	estadistica(listita);
	    break;
	  case 8:
	  	escribeListaEnArchivo(nombreArch, listita);
	    break;
	}	
	cout << endl;
}


void escribeListaEnArchivo(string nombreArch, tLista& listita)
{
	ofstream flujoOut;

	flujoOut.open(nombreArch);

	if (flujoOut.fail()) // comprueba una conexión fallida
	{
		cout << "\n El archivo no se abrió con éxito" << endl;
		exit(1);
	}
	else
	{
		for (int i = 0; i < listita.contador; ++i)
		{
			flujoOut << listita.elementos[i].nombres << endl;
			flujoOut << listita.elementos[i].apellidos << endl;
			flujoOut << listita.elementos[i].edad << endl;
			flujoOut << listita.elementos[i].dni << endl;
			if (i < (listita.contador - 1))  // Me veo obligado a hacer esto para que no deje un renglon en blanco al final del archivo
			{
				flujoOut << listita.elementos[i].nota << endl;
			}
			else
			{
				flujoOut << listita.elementos[i].nota;
			}
		}
	}
	flujoOut.close();
}


double medianaPorBurbuja(tLista& listita)
{
	int aux;
	double median;
	bool ordenado = false;

	int notas[Dimension] = {};
	for (int i = 0; i < listita.contador; ++i)
	{
		notas[i] = listita.elementos[i].nota;
	}
	for (int j = (listita.contador - 1); ((j > 0) && !ordenado); j--)
	{
		ordenado = true;
		for (int k = 0; k < j; ++k)
		{
			if(notas[k] > notas[k+1] )
			{
				aux = notas[k];
				notas[k] = notas[k+1];
				notas[k+1] = aux;
				ordenado = false;
			}
		}
	}
	if((listita.contador % 2) == 0 )
	{
		median = 0.5*(notas[listita.contador/2] + notas[(listita.contador/2)-1]);
	}
	else
	{
		median =notas[listita.contador/2];
	}

	return median;
}
