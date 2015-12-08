#ifndef SENSOR_H   // if SENSOR_H no ha sido incluido
#define SENSOR_H

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

#define HOST "localhost"
#define USER "root"
#define PASS "RICart0928"
#define DB "sensores"

using namespace std;



class Sensor
{
	//clase padre.
	protected:
	string prc;
	string table;
	public:
		//Agrega informacion en la tabla determinada por el string table;
		void add_Data(string str1, string str2, string str3, string str4, string str5)
		{	
			//intanciamiento de las diferentes clases y funciones requeridas para realizar la conexion de codigo con la base de datos.
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			string temp = "CALL "+prc+"("+str1+", "+str2+", "+str3+", "+str4+", "+str5+")";
			stmt->execute(temp);
			cout << "Datos ingresados correctamente en la base de datos" << endl;
			cout << endl;
			
			
		};
		//obtener datos de una tabla en especifico en un piso particular
		void get_DataPiso(string Lugar)
		{	
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * from "+table+" where Localizacion = "+Lugar+" order by Fecha"));
			
			string palabra;
			if(table == "s_Temperatura"){palabra = "temperatura";}
			else if(table == "s_Presion"){palabra = "presion";}
			else if(table == "s_Humedad"){palabra = "humedad";}
			else if(table == "s_Luminosidad"){palabra = "luminosidad";}
			else if(table == "s_Viento"){palabra = "velocidad de viento";};
			
			cout << " Los valores de " << palabra << " obtenidos en el " << Lugar << " son los siguientes:" << endl;	
			while (res->next()){
  				cout << "El " << res->getString("Fecha") << " a las " << res->getString("Hora") << " con valor: " << res->getString("Valor") << " " << res->getString("Unidad") << endl;
				};
			cout << endl;
			
		};
		//Recuperar datos de una tabla de acuerdo a la fecha especifica;	
		void get_DataFecha(string Fecha)
		{	
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * from "+table+" where Fecha = "+Fecha+""));
			
			string palabra;
			if(table == "s_Temperatura"){palabra = "temperatura";}
			else if(table == "s_Presion"){palabra = "presion";}
			else if(table == "s_Humedad"){palabra = "humedad";}
			else if(table == "s_Luminosidad"){palabra = "luminosidad";}
			else if(table == "s_Viento"){palabra = "velocidad de viento";};
			
			cout << " El dia " << Fecha << " se obtuvieron los siguientes valores de " << palabra << endl;	
			while (res->next()){
  				cout << "En el  " << res->getString("Localizacion") << " a las " << res->getString("Hora") << " con valor: " << res->getString("Valor") << " " << res->getString("Unidad") << endl;
				};
			cout << endl;
			
		};
		
		//Recupera datos de una tabla en un intervalo de fechas dado.
		void get_DataIntervFecha(string inFecha1, string inFecha2 )
		{	
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * from "+table+" where Fecha >= "+inFecha1+" AND Fecha <= "+inFecha2+" order by Fecha"));
			
			string palabra;
			if(table == "s_Temperatura"){palabra = "temperatura";}
			else if(table == "s_Presion"){palabra = "presion";}
			else if(table == "s_Humedad"){palabra = "humedad";}
			else if(table == "s_Luminosidad"){palabra = "luminosidad";}
			else if(table == "s_Viento"){palabra = "velocidad de viento";};
			
			cout << "Se obtuvieron los siguientes valores de " << palabra << " en el intervalo de tiempo comprendido entre" << inFecha1<< "y" << inFecha2 << ":" << endl;	
			while (res->next()){
  				cout << "El " << res->getString("Fecha") <<" en el " << res->getString("Localizacion") << " a las " << res->getString("Hora") << " con valor: " << res->getString("Valor") << " " << res->getString("Unidad") << endl;
				};
			cout << endl;
			
		};

		//Recupera datos en un intervalo de valores dado;
		void get_DataIntervValor(string Valor1, string Valor2 )
		{	
			sql::Driver* driver = get_driver_instance();
  			std::auto_ptr<sql::Connection> con(driver->connect(HOST, USER, PASS));
  			con->setSchema(DB);
  			std::auto_ptr<sql::Statement> stmt(con->createStatement());
			std::auto_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * from "+table+" where Valor >= "+Valor1+" AND Valor <= "+Valor2+" order by Fecha"));
			
			string prueba;
			string palabra;
			if(table == "s_Temperatura"){palabra = "temperatura";}
			else if(table == "s_Presion"){palabra = "presion";}
			else if(table == "s_Humedad"){palabra = "humedad";}
			else if(table == "s_Luminosidad"){palabra = "luminosidad";}
			else if(table == "s_Viento"){palabra = "velocidad de viento";};
			
			cout << "Se obtuvieron los siguientes resultados de " << palabra << " en el intervalo de valores deseado, entre " << Valor1<< " y " << Valor2 << ":" << endl;	
			while (res->next()){
  				cout << "El " << res->getString("Fecha") <<" en el " << res->getString("Localizacion") << " a las " << res->getString("Hora") << " con valor: " << res->getString("Valor") << " " << res->getString("Unidad") << endl;
				};
			cout << endl;
			
		};
};

#endif

