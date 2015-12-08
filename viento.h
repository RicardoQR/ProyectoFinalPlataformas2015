#ifndef VIENTO_H   
#define VIENTO_H

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

class Viento: public Sensor{
	public:
		Viento(){prc = "add_Viento";
			table = "s_Viento";}
		
		//velocidad maxima en una fecha, recupera la hora y dice si es optima para colocar turbinas para generacion de energia eolica
		void MaxVel(string fecha1){
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
			string listaH[cantidad];
			int i = 0;

			
			res.reset(stmt->executeQuery("SELECT Valor, Hora from "+table+" where Fecha = "+fecha1+""));
			
			while(res->next()){
				lista[i]=res->getDouble("Valor");
				listaH[i]=res->getString("Hora");
				i+=1;
			}
			
			double max = lista[0];
			int s = 0;

			for(int j= 0; j<=cantidad-1; j++){
				
				if(lista[j]>max){
					max = lista[j];
					s = j;			
				}
			};
			
			cout << "El valor maximo de velocidad medido el " << fecha1 << " es: " << max << " m/s " << " a las " << listaH[s] << endl;
			cout << endl;
			
			if(max>=10){
				cout<<"Valor de velocidad de viento optimo para generacion de energia eolica!"<<endl;
				cout<<endl;
			}
		
		};
		
};

#endif
