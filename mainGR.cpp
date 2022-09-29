#include <bits/stdc++.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

void fillMatrix(vector<vector<char>> &vec, fstream &file,int fila,int columna)
{
	vector<char> aux;
	int flag = 0;
	string trash;
	for (int i = 0; i < fila; ++i)
	{
		vec.push_back(aux);
		for (int j = 0; j < columna+2; ++j)
		{
			if (flag < columna)
			{
				vec.at(i).push_back(file.get());
				flag++;
			}
			else
			{
				trash = file.get();
				flag++;
				if (flag == columna+2)
					flag = 0;
			}
		}
	}
}
void printMatrix(vector<vector<char>> &vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec.at(i).size(); ++j)
		{
			cout << vec.at(i).at(j);
		}
		cout << endl;
		// cout<<vec.at(i).size();
	}
}

void record_pos_dif(vector<char>& inst, int pos, vector<char>& solucion, vector<int>& sol_posRecord)
{
	// cout<<" "<<inst.size()<<" "<< solucion.size()<<" ";
	for (int i = 0; i < inst.size(); i++){
		if (inst.at(i) != solucion.at(pos)) sol_posRecord.at(i) += 1;
	}
}

bool check_threshold(vector<int> &sol_posRecord, float threshold,int columnas, int filas){ // sol_posrecord size es 100
	float convert;// flotante para convertir el int de cada sol_porecord a un flotante
	int total = 0; //cuantas filas cumplen con el threshold
	int compareth = static_cast<int>(threshold * 100); //convierte el threshold a un nro entero
	// cout<< "compareth: "<<compareth<<endl;
	for (int i = 0; i < sol_posRecord.size(); i++)
	{
		convert = (float)sol_posRecord.at(i) / columnas;
		// cout<<"convert: "<< convert<<endl;
		if (convert > threshold || abs(threshold - convert) < 1e-9) total += 1;
		
	}
	cout<<total<<" de "<< filas <<"strings cumplen con el threshold"<<endl;
	return false;
}


void randomchoice(vector<int>& rep,vector<char>& sol,vector<int>& solRep){
	int save = 0; // posición elegida 
	vector<int> tie_vec;//vector con los empates guarda 0,1,2,3 siendo las letras empatadas
	for (int i = 0; i < rep.size()-1; i++){ //encuentro el suspuesto menor 
		if(rep.at(i) > rep.at(i+1)) save = i+1;
	}

	for (int i = 0; i < rep.size(); ++i){// busco si hay empates
		if (rep.at(save) == rep.at(i)){ 
			tie_vec.push_back(i);
		}
	}
	if (!tie_vec.empty()){ // si hay empates eligo una letra random entre ellas 
		int choice = rand()%tie_vec.size(); 
		save = tie_vec.at(choice);	
	}
	solRep.push_back(rep.at(save));
	switch (save){
	case 0:
		sol.push_back('A');
		break;
	case 1:
		sol.push_back('C');
		break;
	case 2:
		sol.push_back('G');
		break;
	case 3:
		sol.push_back('T');
		break;
	}
}

void exec (float threshold,vector<vector<char>>& mat, vector<char>& vj,vector<int>& reps_j,vector<char>& alf,vector<char>& sol,vector <int>& n_char_sol,int filas,int columnas){
    
    int alf1;
	int alf2;
	int alf3;
	int alf4; 
    sol.clear();
    n_char_sol.clear();
	vector<int> solRep(filas, 0);
    
    for (int j = 0; j < mat.at(0).size(); j++){
		alf1=0;
		alf2=0;
		alf3=0;
		alf4=0; 
		vj.clear();
		reps_j.clear();
		
		for (int i = 0; i < mat.size(); i++){//
			vj.push_back(mat.at(i).at(j)); //lleno la columna
		}
		for(int k = 0; k < vj.size();k++){
				if(vj.at(k) == alf.at(0)) alf1 ++;
				if(vj.at(k) == alf.at(1)) alf2 ++;
				if(vj.at(k) == alf.at(2)) alf3 ++;
				if(vj.at(k) == alf.at(3)) alf4 ++;
			}
		reps_j.push_back(alf1);
		reps_j.push_back(alf2);
		reps_j.push_back(alf3);
		reps_j.push_back(alf4);
		
		randomchoice(reps_j,sol,n_char_sol);	
		record_pos_dif(vj,j,sol,solRep);
	}
    
    check_threshold(solRep,threshold,columnas,filas);
}




int main(int argc, char *argv[]){
	srand(time(NULL));
	string s1=argv[1];
	string s2=argv[2];
	string s3=argv[3];
	string s4=argv[4];
	
	if(s1 != "-i") return 0;
	if(s2 !="100-300" && s2!="100-600"&&s2!="100-800"&&s2!="200-300"&&s2!="200-600"&&s2!="200-800") return 0;
	if(s3 != "-th") return 0;
	if(s4 !="0.75" && s4 != "0.80" && s4!="0.85") return 0;	


	string aux = s2.substr(0,3);
	int filas = stoi(aux);
	aux = s2.substr(4,3);
	int columnas = stoi(aux);
	float threshold = stof(s4);
	
	vector<string> texts;
	for (int i = 0; i < 10; i++){
		texts.push_back(s2);
	}
	texts.at(0) += "-001.txt";
	texts.at(1) += "-002.txt";
	texts.at(2) += "-003.txt";
	texts.at(3) += "-004.txt";
	texts.at(4) += "-005.txt";
	texts.at(5) += "-006.txt";
	texts.at(6) += "-007.txt";
	texts.at(7) += "-008.txt";
	texts.at(8) += "-009.txt";
	texts.at(9) += "-010.txt";

	vector<long double> promedios;
	vector<char> alfabeto{'A', 'C', 'G', 'T'};
	vector<vector<char>> vec1; // vector con las 10 instancias
	vector<vector<char>> vec2;
	vector<vector<char>> vec3;
	vector<vector<char>> vec4;
	vector<vector<char>> vec5;
	vector<vector<char>> vec6;
	vector<vector<char>> vec7;
	vector<vector<char>> vec8;
	vector<vector<char>> vec9;
	vector<vector<char>> vec10;
	fstream file1(texts.at(0), fstream::in | fstream::out);
	fstream file2(texts.at(1), fstream::in | fstream::out);
	fstream file3(texts.at(2), fstream::in | fstream::out);
	fstream file4(texts.at(3), fstream::in | fstream::out);
	fstream file5(texts.at(4), fstream::in | fstream::out);
	fstream file6(texts.at(5), fstream::in | fstream::out);
	fstream file7(texts.at(6), fstream::in | fstream::out);
	fstream file8(texts.at(7), fstream::in | fstream::out);
	fstream file9(texts.at(8), fstream::in | fstream::out);
	fstream file10(texts.at(9), fstream::in | fstream::out);
	
	fillMatrix(vec1, file1,filas,columnas);
	fillMatrix(vec2, file2,filas,columnas);
	fillMatrix(vec3, file3,filas,columnas);
	fillMatrix(vec4, file4,filas,columnas);
	fillMatrix(vec5, file5,filas,columnas);
	fillMatrix(vec6, file6,filas,columnas);
	fillMatrix(vec7, file7,filas,columnas);
	fillMatrix(vec8, file8,filas,columnas);
	fillMatrix(vec9, file9,filas,columnas);
	fillMatrix(vec10, file10,filas,columnas);



	vector<char> v_j;	  // vector columna en el que se esta trabajando
	vector<char> s_gr;	  // greedy
	vector<int> scount_gr; // cantidad de la letra elegida.
	 // vector de 100 pos cada una representa la fila i de cada instancia y muestra en
	// cuantas casillas difiere de la solucion
	int instancia = 1;

	vector<int> rep_j; // vector con repeticiones tamaño 4

	setprecision(9);
	//INSTANCIA 1
	auto start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec1,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	auto end1 = chrono::high_resolution_clock::now();
	chrono::duration<double> diff = end1 - start1;
	//cout<< "instancia 1 ->";
	
	printf( "%.10f\n", (diff.count()));
	//printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 2
	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec2,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	printf( "%.10f\n", (diff.count()));
	//cout<< "instancia 2 ->";
	//printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 3
	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec3,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 3 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 4
	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec4,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 4 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 5

	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec5,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 5 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 6

	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec6,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 6 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 7
	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec7,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 7 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 8
	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec8,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 8 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 9

	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec9,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;

	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 9 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	//INSTANCIA 10

	start1 = chrono::high_resolution_clock::now();

	exec(threshold,vec10,v_j,rep_j,alfabeto,s_gr,scount_gr,filas,columnas);

	end1 = chrono::high_resolution_clock::now();
	diff = end1 - start1;
	//printf( "%.10f\n", (diff.count()));
	cout<< "instancia 10 ->";
	printf("tiempo Greedy: %.10f seg\n", (diff.count()));
	promedios.push_back(diff.count());
	long double prom=0;
	cout.precision(9);
	for (int i = 0; i < promedios.size(); i++){
		prom=prom+promedios.at(i);
	}
	prom = prom/10;
	cout<<"promedio:  "<<prom<<endl;
	long double sumatoria=0;
	long double varianza=0;
	for (int i = 0; i < promedios.size(); i++){
		sumatoria=sumatoria + pow(promedios.at(i)+prom,2);
	}

	varianza = sumatoria/9;
	
	cout<<"varianza:  "<<varianza<<endl;
	long double desviacion=sqrt(varianza);

	cout<<"Desviacion "<<desviacion<<endl;
	return 0;
}
/*for (int i = 0; i < s_g.size(); ++i){
	cout<<s_g.at(i);
}
cout<<endl;
for (int i = 0; i < scount_g.size(); ++i){
	cout<<scount_g.at(i)<<" ";
}
cout<<endl;*/

/*for (int i = 0; i < s_gr.size(); ++i){
	cout<<s_gr.at(i);
}
cout<<endl;
for (int i = 0; i < scount_gr.size(); ++i){
	cout<<scount_gr.at(i)<<" ";
}
cout<<endl;
printMatrix(vec);






*/