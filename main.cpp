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
#include "temperatura.h"
#include "presion.h"
#include "humedad.h"
#include "luminosidad.h"
#include "viento.h"

#define HOST "localhost"
#define USER "root"
#define PASS "RICart0928"
#define DB "sensores"

using namespace std;




int main()
{

  cout << "Conectandose con el Connector/C++ a la base de datos.." << endl;
  cout << endl;
  
  //instancia de las clases
  Temperatura T1;
  Presion P1;
  Humedad H1;
  Luminosidad L1;
  Viento V1;

try {

  //PRUEBAS PARA LAS DIFERENTES CLASES, DESCOMENTAR LA PRUEBA DESEADA.
   /*T1.add_Data("'26'", "'C'", "'2015-06-19'", "'12:35:00'", "'Segundo Piso'");
   P1.add_Data("'120'", "'kPa'", "'2014-01-25'", "'18:20:53'", "'Tercer Piso'");
   H1.add_Data("'31.33'", "'gm3'", "'2008-10-15'", "'12:00:00'", "'Segundo Piso'");
   L1.add_Data("'1200'", "'L'", "'2011-12-07'", "'14:00:00'", "'Sexto Piso'");
   V1.add_Data("'1.2'", "'m/s'", "'2014-10-14'", "'21:09:44'", "'Segundo Piso'");*/
	

   
   //P1.get_DataPiso("'Cuarto Piso'");

   //T1.get_DataIntervFecha("'2013-01-01'","'2015-01-01'");
   //T1.get_DataIntervValor("'25'","'30'");

   /*T1.MaxTemp("'2002-02-22'");
  T1.MinTemp("'2002-02-22'");*/
   //T1.CheckTemp("'2002-01-01'", "'2002-01-02'");
   /*P1.Promedio("'Cuarto Piso'");
   P1.NivelMar();*/
   //H1.CheckHumedad("'2008-02-15'","'2008-02-22'");


   //T1.get_DataFecha("'2002-02-22'");

     //T1.CheckTemp("'2010-01-01'","'2015-12-31'");

    /*L1.CheckLuminosidad("'2011-12-07'");
    L1.Consumo("'2011-12-07'");*/
   
    V1.MaxVel("'2002-02-22'");




  } catch (sql::SQLException &e) {
  
    //manejo de errores
    cout << "# ERR: SQLException in " << __FILE__;
    cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
    cout << "# ERR: " << e.what();
    cout << " (MySQL error code: " << e.getErrorCode();
    cout << ", SQLState: " << e.getSQLState() << " )" << endl;

    return EXIT_FAILURE;
  }

  cout << "Listo." << endl;
  return EXIT_SUCCESS;
}
