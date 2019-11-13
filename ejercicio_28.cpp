/* En este ejercicio deben solucionar la ecuacion de movimiento de un proyectil para el caso en
que hay una friccion proporcional a v2. Deben escribir un codigo en c++ llamado ODE cpp donde implementen el 
metodo de Leap-Frog o el metodo de Runge Kutta de 4to orden para
resolver la ecuacon de movimiento:*/

//////Importo lo necesario//////
#include<iostream>
#include <vector>
#include <math.h> 
#include<cmath>
#include <fstream>
#include <vector>

using namespace std;

///// Se declaran las constantes necesarias para desarrollar la ecuacion//////
float static PI = 3.14159265359; // el valor de pi como una constante global 
vector<float> g; // la ecelerecion gravitacional en metros sobre segundo cuadrado
float static c = 0.2; // el coeficiente de friccion 
float static m  = 0.2; // la masa del objeto en kilo gramos
float static ht = 0.001; // variacion del tiempo entre cada instante
///// Se declaras las variables de la ecuacion que varian segun los puntos /////
float static tmax = 3.0; //el tiempo maximo con el que se trabajara
int N = (int) tmax/ht; // el numero de iteraciones que se realizaran en el sisema
vector<float> fun[2];
vector<float> posx_0;
vector<float> vel_0;
vector<int> data_count;
/* Se define la funcion con la cual se construira la ecuacion a esta funcion 
le entran por parameto las 2 componentes de un vector v*/
void funcion_inc(vector<float> v0,vector<float> v1){
	float magv1 = sqrt(pow(v1.at(0),2)+pow(v1.at(1),2));
	vector<float> mov1;
	float mov1_x = -g.at(0)-(c/m)*(magv1)*v1.at(0);
	float mov1_y = -g.at(1)-(c/m)*(magv1)*v1.at(1);
	mov1.push_back(mov1_x);
	mov1.push_back(mov1_y);
	fun[0]=v1;
	fun[1]=mov1;
}
/*Se define la funcion con la cual se resolvera la ecuacion para encontrar el movimiento
del proyectil utilizando el metodo de  Runge Kutta 4*/
float  funcion_movimiento(float angulo,string file_exp){
	// asignando condiciones inicciales para la velocidad
	vel_0.clear();
	vel_0.push_back(300*cos(angulo*PI/180.0));
	vel_0.push_back(300*sin(angulo*PI/180.0));

	
	// Se define un vector para asignar un valor inicial del movimiento 
	vector<float> M[N][2];
	M[0][0]=posx_0;
	M[0][1]=vel_0;
/*Para que esta basura de lenguaje no bote error para crear los archivos de la parte 2 
tengo que declarar lo que sigue si no no sale bien en esta basura*/
	ofstream file;
	if(file_exp == "datos2_ODE.dat"){
		file.open(file_exp.c_str(), ios::out | ios::app);
	}
	else{
		file.open(file_exp.c_str());
	}
	file<<"Angulo:"<<angulo<<endl;
float x_total = 0;



/*Ahora se debe implementar el metodo de Runge Kutta para resulver la eqn*/
	for (int i = 1; i < N; ++i){
		// Inicialmente se debe calcular el valor de K1 para la solucion 
		vector<float> k1[2];
		funcion_inc(M[i-1][0],M[i-1][1]);
		k1[0] = fun[0];
		k1[1] = fun[1];

		// Calculado K1 se procede con el calculo de K2
		vector<float> k2[2];
		vector<float> valorM0_2;
		vector<float> valorM1_2;
		float valorM0_2_x = (M[i-1][0]).at(0)+(ht/2.0);
		float valorM0_2_y = (M[i-1][0]).at(1)+(ht/2.0);
		float valorM1_2_x = (M[i-1][1]).at(0)+((k1[1]).at(0))*(ht/2.0);
		float valorM1_2_y = (M[i-1][1]).at(1)+((k1[1]).at(1))*(ht/2.0);
		valorM0_2.push_back(valorM0_2_x);
		valorM0_2.push_back(valorM0_2_y);
		valorM1_2.push_back(valorM1_2_x);
		valorM1_2.push_back(valorM1_2_y);

		funcion_inc(valorM0_2,valorM1_2);
		k2[0] = fun[0];
		k2[1] = fun[1];
		//Se calcula el valor de k3
		vector<float> k3[2];
		vector<float> valorM0_3;
		vector<float> valorM1_3;
		float valorM0_3_x = (M[i-1][0]).at(0)+(ht/2.0);
		float valorM0_3_y = (M[i-1][0]).at(1)+(ht/2.0);
		float valorM1_3_x = (M[i-1][1]).at(0)+((k2[1]).at(0))*(ht/2.0);
		float valorM1_3_y = (M[i-1][1]).at(1)+((k2[1]).at(1))*(ht/2.0);
		valorM0_3.push_back(valorM0_3_x);
		valorM0_3.push_back(valorM0_3_x);
		valorM1_3.push_back(valorM1_3_x);
		valorM1_3.push_back(valorM1_3_y);

		funcion_inc(valorM0_2,valorM1_3);
		k3[0] = fun[0];
		k3[1] = fun[1];
		//Se calcula el valor de k4
		vector<float> k4[2];
		vector<float> valorM0_4;
		vector<float> valorM1_4;
		float valorM0_4_x = (M[i-1][0]).at(0)+(ht);
		float valorM0_4_y = (M[i-1][0]).at(1)+(ht);
		float valorM1_4_x = (M[i-1][1]).at(0)+((k3[1]).at(0))*(ht);
		float valorM1_4_y = (M[i-1][1]).at(1)+((k3[1]).at(1))*(ht);
		valorM0_4.push_back(valorM0_4_x);
		valorM0_4.push_back(valorM0_4_y);
		valorM1_4.push_back(valorM1_4_x);
		valorM1_4.push_back(valorM1_4_y);

		funcion_inc(valorM0_4,valorM1_4);
		k4[0] = fun[0];
		k4[1] = fun[1];
		/*Con lo vectores obtenidos en la solucion de la ecuacion con el metodo de RK de debe 
		generar la pendiente con la cual se generaran los valores de x que son soluciones 
		de la ecuacion diferencial*/
		float pendiente0_x = (1.0/6.0)*((k1[0]).at(0)+2.0*(k2[0]).at(0)+2.0*(k3[0]).at(0)+(k4[0]).at(0));
		float pendiente0_y = (1.0/6.0)*((k1[0]).at(1)+2.0*(k2[0]).at(1)+2.0*(k3[0]).at(1)+(k4[0]).at(1));
		float pendiente1_x = (1.0/6.0)*((k1[1]).at(0)+2.0*(k2[1]).at(0)+2.0*(k3[1]).at(0)+(k4[1]).at(0));
		float pendiente1_y = (1.0/6.0)*((k1[1]).at(1)+2.0*(k2[1]).at(1)+2.0*(k3[1]).at(1)+(k4[1]).at(1));
		// Se generan los vectores con los valores de las pendientes generadas por los vales de RK
		vector<float> pendiente_0;
		vector<float> pendiente_1;
		vector<float> M0;
		vector<float> M1;
	 	pendiente_0.push_back(pendiente0_x);
	 	pendiente_0.push_back(pendiente0_y);
	 	pendiente_1.push_back(pendiente1_x);
	 	pendiente_1.push_back(pendiente1_y);
	 	M0.push_back((M[i-1][0]).at(0)+ht*pendiente_0.at(0));
	 	M0.push_back((M[i-1][0]).at(1)+ht*pendiente_0.at(1));
	 	M1.push_back((M[i-1][1]).at(0)+ht* pendiente_1.at(0));
	 	M1.push_back((M[i-1][1]).at(1)+ht* pendiente_1.at(1));
	 	// Se generan los nuevos valores de movimiento en el vector M

	 	if ((M[i-1][0]).at(1) < 0)
	 	{
	 		data_count.push_back(i);
	 		break;
	 	}

	 	M[i][0]=M0;
		M[i][1]=M1;
		x_total += sqrt(pow(M[i][0].at(0)-M[i-1][0].at(0),2)+pow(M[i][0].at(1)-M[i-1][0].at(1),2));
		// Se dan los resultados de los valores de la posicion en la terminal 
		file<<"t="<<i*ht<<",posx="<<(M[i-1][0]).at(0)<<" , posy="<<(M[i-1][0]).at(1)<<" , velx="<<(M[i-1][1]).at(0)<<" , vely="<<(M[i-1][1]).at(1)<<"\n";


	}
	file.close();
	return x_total;
}
int main() {
	g.push_back(0.0);
	g.push_back(10.0);	
	posx_0.push_back(0.0);
	posx_0.push_back(0.0);
	//Para la primera parte
	float angulo = 45.0;
	float distancia_45_grados = funcion_movimiento(angulo, "datos1_ODE.dat");
	cout<<" La distancia que recorre el proyectil a 45 grados es "<<distancia_45_grados<<"m"<<endl;


	//Para la segunda parte
	float angulos_parte2[7];
	for (int i = 1; i <= 7; ++i)
	{	
		angulo=10*i;
		angulos_parte2[i-1]=funcion_movimiento(angulo,"datos2_ODE.dat");
	}

	ofstream file;
	file.open("datos2_ODE.dat", ios::out | ios::app);
	file<<data_count.at(1)<<","<<data_count.at(2)<<","<<data_count.at(3)<<","<<data_count.at(4)<<","<<data_count.at(5)<<","<<data_count.at(6)<<","<<data_count.at(7)<<endl;

	file.close();

	float movimiento__maximo = 0;
	int jamesito_el_numero = 10;
	for (int i = 0; i < 7; ++i)
	{
		if (angulos_parte2[i]>movimiento__maximo)
		{
			movimiento__maximo = angulos_parte2[i];
			jamesito_el_numero = (i+1)*10;
		}
	}
	cout<<" La distancia máxima que recorre el proyectil es cuando el angulo es 20  grados."<<endl;
	return 0;
}