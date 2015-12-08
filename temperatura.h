#ifndef TEMPERATURA_H   // if SENSOR_H no ha sido incluido
#define TEMPERATURA_H

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

class Temperatura: public Sensor{
	public:
		//constructor
		Temperatura(){prc = "add_Tempe";
			      table = "s_Temperatura";};

		//Verifica la temperatura en un intervalo de fechas y notifica si se encontraron mas de cierta cantidad x de mediciones sobre el maximo permitido. Alerta sobre esto.
		void CheckTemp(string fecha1, string fecha2){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Localizacion, count(*) from "+table+" where Valor >= 26 and Fecha> "+fecha1+" and Fecha< "+fecha2+" and Unidad = 'C' group by Localizacion"));

			double lista[5] = {0,0,0,0,0};
			string slista[5];
			int i = 0;
			int c = 0;
			
			while(res->next()){
				lista[i]=res->getDouble("count(*)");
				slista[i]=res->getString("Localizacion");
				i+=1;
			}

			for(int j = 0; j<=5; j++){
				if(lista[j]>=3){
					if(j==0){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] << ", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;} 
					else if(j==1){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] <<", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;}
					else if(j==2){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] <<", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;}
					else if(j==3){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] <<", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;}
					else if(j==4){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] <<", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;}
					else if(j==5){cout<<"En el intervalo de tiempo seleccionado, se han encontrado " << lista[j] << " mediciones de temperatura superior o igual al maximo de 26 C en el " << slista[j] <<", considere revisar el aire condicionado"<<endl; cout<< endl; c = 1;}
				}
			}
			if(c==0){cout<<"En el intervalo de tiempo seleccionado, no se han encontrado problemas graves de temperatura." <<endl; cout<<endl;};
			
		};

		//valor maximo de temperatura en una fecha dada
		void MaxTemp(string fecha1){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT count(*) from "+table+" where Fecha = "+fecha1+""));
			
			double can;
			while(res->next()){
				can = res->getDouble("count(*)");
			}
			int cantidad = (int)can;
			double lista[cantidad-1];
			int i = 0;

			
			res.reset(stmt->executeQuery("SELECT Valor from "+table+" where Fecha = "+fecha1+""));
			
			while(res->next()){
				lista[i]=res->getDouble("Valor");
				i+=1;
			}
			
			double max = lista[0];

			for(int j= 0; j<=cantidad-1; j++){
				
				if(lista[j]>max){
					max = lista[j];
				}
			};
			
			cout << "El valor maximo de temperatura medido el " << fecha1 << " es: " << max << " C" << endl;
			cout << endl;
		
		};
		//valor minimo de temperatura en un dia dado
		void MinTemp(string fecha1){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT count(*) from "+table+" where Fecha = "+fecha1+""));
			
			double can;
			while(res->next()){
				can = res->getDouble("count(*)");
			}
			int cantidad = (int)can;
			double lista[cantidad];
			int i = 0;

			
			res.reset(stmt->executeQuery("SELECT Valor from "+table+" where Fecha = "+fecha1+""));
			
			while(res->next()){
				lista[i]=res->getDouble("Valor");
				i+=1;
			}
			
			double min = lista[0];

			for(int j= 0; j<cantidad; j++){
				
				if(lista[j]<min){
					min = lista[j];
				}
			};
			
			cout << "El valor minimo de temperatura medido el " << fecha1 << " es: " << min << " C" << endl;
			cout << endl;
		
		};
		
};

#endif
