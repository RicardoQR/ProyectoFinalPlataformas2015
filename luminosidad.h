#ifndef LUMINOSIDAD_H   
#define LUMINOSIDAD_H

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
/* uncomment for applications that use vectors */
/*#include <vector>*/

#include "mysql_connection.h"

#include <string>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "sensor.h"

#define HOST "localhost"
#define USER "root"
#define PASS "RICart0928"
#define DB "sensores"

using namespace std;

class Luminosidad: public Sensor{
	public:
		Luminosidad(){prc = "add_Lumino";
			      table = "s_Luminosidad";}
		//Funcion que prende las luces del edificio de acuerdo a la cantidad de luminosidad medida.
		void CheckLuminosidad(string fecha1){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res;

			string pisos[6] = {"'Primer Piso'","'Segundo Piso'","'Tercer Piso'","'Cuarto Piso'","'Quinto Piso'","'Sexto Piso'"};
			for(int i=0; i<6; i++){
				res.reset(stmt->executeQuery("SELECT count(*) from "+table+" where Fecha= "+fecha1+" and Localizacion = "+pisos[i]+""));
				double cant;
				while(res->next()){
					cant = res->getDouble("count(*)");
				};
				int cantidad = (int)cant;
				
				if (cant != 0){
					double lista[cantidad];
					string listaH[cantidad];
					int n=0;
					res.reset(stmt->executeQuery("SELECT Valor, Hora from "+table+" where Fecha= "+fecha1+" and Localizacion = "+pisos[i]+" order by Valor"));
					while(res->next()){
						lista[n] = res->getDouble("Valor");
						listaH[n] = res->getString("Hora");
						n+=1;};

					for(int j= 0; j<cantidad; j++){
						if (lista[j] <= 600){
							cout<<"Encendiendo luces...."<<endl;
							cout<<"Luces del "<< pisos[i] << " encendidas a las " << listaH[j] <<endl;
							cout<<endl;
							break;
						};
					};
				}
				
				else{cout<<"No hay datos disponibles del " << pisos[i] <<endl; cout<<endl;};
					
					
					
			}
		}
		//Estima el consumo de electricidad en la noche de acuerdo a la intensidad luminosa dada en la noche.
		void Consumo(string Fecha){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT count(*) from "+table+" where Fecha= "+Fecha+" and Hora>= '19:00:00' and Hora<= '24:00:00' "));

			
			double cant;
			double valor;
			double total = 0;
			double costo;
			int i=0;
			while(res->next()){
				cant = res->getDouble("count(*)");
			}

			res.reset(stmt->executeQuery("SELECT Valor from "+table+" where Fecha= "+Fecha+" and Hora>= '19:00:00' and Hora<= '24:00:00' "));
			while(res->next()){
				valor = res->getDouble("Valor");
				total = total + valor;	
			}
			
			costo = total*10;
			cout<<"El dia " << Fecha << " se gastaron " <<costo << " colones en electricidad por iluminacion nocturna."<<endl;
			cout<<endl;
		}
};

#endif
