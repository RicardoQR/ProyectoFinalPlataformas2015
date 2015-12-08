#ifndef PRESION_H   // if SENSOR_H no ha sido incluido
#define PRESION_H

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

class Presion: public Sensor{
	
	double promedio;
	public:
		Presion(){prc = "add_Presion";
			  table = "s_Presion";};
		//calcula el valor promedio de la presion atmosferica en un piso dado
		void Promedio(string Piso){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT count(*) from "+table+" where Localizacion = "+Piso+""));
			
			double cant;
			while(res->next()){
				cant = res->getDouble("count(*)");
			}
			double temp;
			double total = 0;
			int i = 0;
			
			res.reset(stmt->executeQuery("SELECT Valor from "+table+" where Localizacion = "+Piso+""));
			
			while(res->next()){
				temp =res->getDouble("Valor");
				total = total + temp;
				i+=1;
			}
			
			promedio = total/cant;

			cout << "El valor promedio de presion en el " << Piso << ", es de: " << promedio << " kPa"<<endl;
			cout << endl;
			};
		//utilizando el promedio obtenido anteriormente, calcula la altura de la medicion respecto al nivel del mar.
		void NivelMar(){
			double nivel;
			nivel = (0.012)*(promedio)+1.2;
			cout << "La altura en metros es de " << nivel << " m respecto al nivel del mar aproximadamente." <<endl;
			cout << endl;
		};
	
			
};

#endif
