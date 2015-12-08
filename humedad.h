#ifndef HUMEDAD_H   
#define HUMEDAD_H

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

class Humedad: public Sensor{
	public:
		//constructor de la clase Humedad. Dicho constructor es utilizado para acceder el procedimiento adecuado en la clase padre Sensores
		Humedad(){prc = "add_Hum";
			  table = "s_Humedad";};
		//funcion CheckHumedad. Verifica la humedad en un intervalo de tiempo y dice que tan grave es el nivel de humedad, recomienda colocar una cierta cantidad de deshumidizadores.
		void CheckHumedad(string fecha1, string fecha2){
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT count(*) from "+table+" where Fecha>= "+fecha1+" and Fecha<= "+fecha2+""));

			
			double cant;
			int i=0;
			while(res->next()){
				cant = res->getDouble("count(*)");
			}
			int cantidad = (int)cant;
			double lista[cantidad];
			string listaF[cantidad];
			string listaH[cantidad];
			string listaL[cantidad];

			res.reset(stmt->executeQuery("SELECT valor, Fecha, Hora, Localizacion from "+table+" where Fecha>= "+fecha1+" and Fecha<= "+fecha2+""));

			while(res->next()){
				lista[i]=res->getDouble("Valor");
				listaF[i]=res->getString("Fecha");
				listaH[i]=res->getString("Hora");
				listaL[i]=res->getString("Localizacion");};	
			int c=0;

			for(int j = 0; j<=cantidad-1; j++){
				if(lista[j]>=35){
					cout<< "Se ha detectado humedad de nivel bajo en el " << listaL[j] << ", el dia " << listaF[j] << " a las " << listaH[j]<< ". Se recomienda colocar 1 deshumidizador lo antes posible en dicha piso."<<endl;
					cout<<endl;
					c = 1;	
				} else if(lista[j]>=40){
					cout<< "Se ha detectado humedad de nivel medio en el " << listaL[j] << ", el dia " << listaF[j] << " a las " << listaH[j]<< ". Se recomienda colocar 2 deshumidizadores lo antes posible en dicha piso, hongos se pueden empezar a generar si no se toman las medidas adecuadas."<<endl;
					cout<<endl;
					c = 1;	
				} else if(lista[j]>=45){
					cout<< "Se ha detectado humedad de nivel alto en el " << listaL[j] << ", el dia " << listaF[j] << " a las " << listaH[j]<< ". Se recomienda colocar al menos 3 deshumidizadores lo antes posible en dicha piso, con dicha humedad los hongos en las paredes son inevitables. Colocar los deshumidizadores indicados lo antes posible!"<<endl;
					cout<<endl;
					c=1;	
				};
			}
			if(c==0){cout<<"En el intervalo de tiempo seleccionado, no se han encontrado problemas de humedad, no es necesario colocar deshumidizador en ningun piso." <<endl; cout<<endl;};
		}
};

#endif
