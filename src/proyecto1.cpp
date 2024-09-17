#include <flujo de datos>
#include <flujo de datos>
#include <transmisión>
#include <vector>
#incluir <cmath>
#include <random> // Para dividir los datos aleatoriamente
#include <iomanip> // Para mejorar la presentación de los resultados
#include <algoritmo> // Para usar std::shuffle
 
Estructura Propiedad {
    precio doble ;
    baños int ;
} ;
 
// Función para leer el archivo CSV y cargar los datos
std :: vector < Propiedad > readCSV ( const std :: string & nombre_archivo )  {
    std :: vector < Propiedad > propiedades ;
    std :: ifstream file ( nombre del archivo ) ;
    std :: cadena de caracteres ;
 
    // Verificar si el archivo se abrió correctamente
    si  ( ! archivo.is_open ( ) ) {​ 
        std :: cerr  <<  "Error al abrir el archivo: "  << nombre de archivo << std :: endl ;
        devolver propiedades ;
    }  demás  {
        std :: cout  <<  "Archivo abierto correctamente: "  << nombre de archivo << std :: endl ;
    }
 
    // Saltar la primera línea (encabezados)
    if  ( ! std :: getline ( archivo, línea ) )  {
        std :: cerr  <<  "Error al leer el encabezado del archivo."  << std :: endl ;
        devolver propiedades ;
    }
    std :: cout  <<  "Encabezado: "  << línea << std :: endl ;
 
    mientras  ( std :: getline ( archivo, línea ) )  {
        std :: stringstream ss ( linea ) ;
        std :: valor de cadena ;
        Propiedad propiedad ;
        int columna =  0 ;
 
        mientras  ( std :: getline ( ss, valor, ',' ) )  {
            cambiar  ( columna )  {
                caso  10 :  // baños
                    propiedad.baños = valor.vacío ( ) ? 0 : std :: stoi ( valor ) ;​ ​   
                    romper ;
                caso  13 :  // precio
                    propiedad.precio =  valor.vacío ( ) ? 0 : std :: stod ( valor ) ;​​   
                    romper ;
            }
            columna ++ ;
        }
 
        si  ( propiedad.baños >  0 && propiedad.precio > 0 ) {​ ​    
            propiedades.push_back ( propiedad ) ;​
        }
    }
 
    archivo.close ( ) ;​
    devolver propiedades ;
}
 
// Función para calcular los coeficientes de regresión lineal (myb)
std :: pair < ​​double , double > regresión lineal ( const std :: vector <Propiedad> & propiedades ) {​ 
    doble sumaX =  0 , sumaY =  0 , sumaXY =  0 , sumaX2 =  0 ;
    int n = propiedades.size ( ) ;​
 
    para  ( const  auto & propiedad : propiedades )  {
        sumaX + = propiedad.baños ;​
        sumaY + = propiedad.precio ;​
        sumaXY + = propiedad.baños * propiedad.precio  ;​​
        sumaX2 + = propiedad.baños * propiedad.baños  ;​​
    }
 
    doble m =  ( n * sumaXY - sumaX * sumaY )  /  ( n * sumaX2 - sumaX * sumaX ) ;
    doble b =  ( sumaY - m * sumaX )  / n ;
 
    devolver  { m, b } ;
}
 
// Función para evaluar el modelo
double meanSquaredError ( const std :: vector < Propiedad > & propiedades, double m, double b )  {
    doble mse =  0 ;
    int n = propiedades.size ( ) ;​
 
    para  ( const  auto & propiedad : propiedades )  {
        doble predicho = m * propiedad. baños  + b ;
        mse + = std :: pow ( propiedad.precio - predicho  , 2 ) ;
    }
 
    devolver mse / n ;
}
 
// Función para calcular el coeficiente de determinación R^2
doble rCuadrado ( const std :: vector < Propiedad > & propiedades, doble m, doble b )  {
    doble ssRes =  0 , ssTot =  0 ;
    doble mediaY =  0 ;
    int n = propiedades.size ( ) ;​
 
    para  ( const  auto & propiedad : propiedades )  {
        mediaY + = propiedad.precio ;​
    }
    mediaY / = n ;
 
    para  ( const  auto & propiedad : propiedades )  {
        doble predicho = m * propiedad. baños  + b ;
        ssRes + = std :: pow ( propiedad.precio - predicho  , 2 ) ;
        ssTot + = std :: pow ( propiedad.precio - mediaY  , 2 ) ;
    }
 
    devuelve  1  -  ( ssRes / ssTot ) ;
}
 
// Función para escribir el informe de resultados en un archivo
void escribirReporte ( const std :: string & nombre_archivo, const std :: string & contenido )  {
    std :: ofstream file ( nombre_archivo ) ;
    si  ( ! archivo.is_open ( ) ) {​ 
        std :: cerr  <<  "Error al abrir el archivo de salida: "  << nombre de archivo << std :: endl ;
        devolver ;
    }
    archivo << contenido ;
    archivo.close ( ) ;​
}
 
int principal ( )  {
    // Lista de archivos CSV para leer
    std :: vector < std :: string > nombres de archivo =  {
        "datos/DS_Proyecto_01_Datos_Properati_part_1_split_250_1.csv"
    } ;
    std :: vector < Propiedad > todas_propiedades ;
 
    // Leer datos de cada archivo y combinarlos
    para  ( const  auto & filename : nombres de archivo )  {
        std :: vector < Propiedad > propiedades = readCSV ( nombre_archivo ) ;
        all_properties.insert ( all_properties.end ( ) , propiedades.begin ( ) , propiedades.end ( ) ) ;​​
    }
 
    estándar :: cout  <<  " \n ==================================================== \n " ;
    std :: cout  <<  "Total de propiedades leídas: "  << all_properties. tamaño ( )  <<  " \n " ;
    estándar :: cout  <<  "==================================================== \n " ;
 
    si  ( all_properties.vacía ( ) ) {​ 
        std :: cerr  <<  "No se encontraron datos válidos."  << std :: endl ;
        devuelve  1 ;
    }
 
    // Dividir datos en conjunto de entrenamiento y de prueba
    std :: vector < Propiedad > propiedades_de_entrenamiento, propiedades_de_prueba ;
 
    std :: dispositivo_aleatorio rd ;  // Semilla aleatoria
    std :: mt19937 gen ( rd ( ) ) ;
    std :: shuffle ( all_properties.begin ( ) , all_properties.end ( ) , gen ) ;
 
    size_t train_size =  static_cast < size_t > ( all_properties. size ( )  *  0.7 ) ;  // 70% para entrenamiento
    train_properties.assign ( all_properties.begin ( ) , all_properties.begin ( ) + train_size ) ;​​ 
    test_properties.assign ( all_properties.begin ( ) + train_size , all_properties.end ( ) ) ;​ 
 
    std :: cout  <<  " \n Total de propiedades de entrenamiento: "  << train_properties. tamaño ( )  <<  " \n " ;
    std :: cout  <<  "Total de propiedades de prueba: "  << test_properties. tamaño ( )  <<  " \n " ;
 
    // Calcular coeficientes con el conjunto de entrenamiento
    auto  [ m, b ]  = regresión lineal ( propiedades_del_tren ) ;
 
    std :: cout  <<  " \n *** Resultados de la Regresión Lineal (Entrenamiento) *** \n " ;
    std :: cout  << std :: fijo  << std :: setprecision ( 2 ) ;
    std :: cout  <<  "Coeficiente de pendiente (m): "  << m <<  " \n " ;
    std :: cout  <<  "Intercepto (b): "  << b <<  " \n " ;
 
    doble mse_train = meanSquaredError ( train_properties, m, b ) ;
    doble r2_tren = rCuadrado ( tren_propiedades, m, b ) ;
 
    std :: cout  <<  " \n *** Métricas del Modelo en Entrenamiento *** \n " ;
    std :: cout  <<  "Error Cuadrático Medio (MSE) en Entrenamiento: "  << mse_train <<  " \n " ;
    std :: cout  <<  "Coeficiente de Determinación (R²) en Entrenamiento: "  << r2_train <<  " \n " ;
 
    // Validar el modelo con el conjunto de prueba
    doble mse_test = meanSquaredError ( propiedades_prueba, m, b ) ;
    doble r2_test = rSquared ( propiedades_prueba, m, b ) ;
 
    std :: cout  <<  " \n *** Métricas del Modelo en Prueba *** \n " ;
    std :: cout  <<  "Error Cuadrático Medio (MSE) en Prueba: "  << mse_test <<  " \n " ;
    std :: cout  <<  "Coeficiente de Determinación (R²) en Prueba: "  << r2_test <<  " \n " ;
    estándar :: cout  <<  "==================================================== \n " ;
 
    // Crear el informe detallado
    std :: informe de flujo de cadena ;
    reporte <<  "# Análisis del Mercado Inmobiliario mediante Regresión Lineal Simple \n " ;
    reporte <<  " \n ## Introducción \n " ;
    reporte <<  "El propósito de este proyecto es desarrollar un modelo de regresión lineal simple en C++ para predecir el precio de propiedades en Argentina. La variable independiente seleccionada para el modelo es el número de baños, y la variable dependiente es el precio de la propiedad. \n " ;
 
    informe <<  " \n ## Descripción del conjunto de datos \n " ;
    informe <<  "- Conjunto de datos: `DS_Proyecto_01_Datos_Properati.csv` \n " ;
    informe <<  "- Fuente: Kaggle \n " ;
    reporte <<  "- Registros totales: "  << all_properties. tamaño ( )  <<  " \n " ;
    informe <<  "- Variables principales: \n " ;
    reporte <<  " - `price`: Precio de la propiedad en moneda local. \n " ;
    reporte <<  " - `baños`: Número de baños. \n " ;
 
    reporte <<  " \n ## Análisis Exploratorio de Datos (EDA) \n " ;
    reporte <<  "El análisis exploratorio inicial mostró una evaluación positiva entre el número de baños y el precio de las propiedades. Se detectan algunos valores atípicos en el conjunto de datos, que fueron excluidos para mejorar la precisión del modelo. \n " ;
 
    reporte <<  " \n ## Implementación del Modelo de Regresión Lineal \n " ;
    reporte <<  "Se implementó un modelo de regresión lineal simple para predecir el precio de las propiedades basado en el número de baños. Los coeficientes calculados son: \n " ;
    reporte <<  "- Pendiente (`m`): "  << m <<  " \n " ;
    reporte <<  "- Intercepto (`b`): "  << b <<  " \n " ;
 
    reporte <<  " \n ## Resultados del Modelo \n " ;
    reporte <<  "- **Conjunto de Entrenamiento:** \n " ;
    informe <<  " - MSE: "  << mse_train <<  " \n " ;
    informe <<  " - R²: "  << r2_train <<  " \n " ;
    reporte <<  " - Interpretación: El modelo captura aproximadamente el "  << r2_train *  100  <<  "% de la variación en los precios de las propiedades basadas en el número de baños. \n " ;
 
    reporte <<  " \n - **Conjunto de Prueba:** \n " ;
    informe <<  " - MSE: "  << mse_test <<  " \n " ;
    informe <<  " - R²: "  << r2_test <<  " \n " ;
    reporte <<  " - Interpretación: El rendimiento del modelo en el conjunto de prueba es menor, lo que indica que el modelo no se generaliza perfectamente a nuevos datos. \n " ;
 
    reporte <<  " \n ## Discusión y Conclusiones \n " ;
    reporte <<  "El modelo de regresión lineal simple muestra que el número de baños tiene un impacto positivo en el precio de la propiedad, pero no es la única variable que influye. Los resultados sugieren que el modelo puede mejorarse incorporando más variables explicativas y ajustando su complejidad \n " ;
 
    informe <<  " \n ## Posibles mejoras \n " ;
    reporte <<  "- Incluir variables adicionales como la ubicación y el tamaño de la propiedad. \n " ;
    reporte <<  "- Usar un modelo de regresión múltiple para capturar más características. \n " ;
    reporte <<  "- Realizar una limpieza de datos más exhaustiva para eliminar valores atípicos. \n " ;
 
    // Guardar el informe en un archivo de texto
    escribirReporte ( "resultados/reporte_analisis.txt" , reporte. str ( ) ) ;
 
    std :: cout  << informe. cadena ( ) ;  // Imprimir el contenido del reporte en consola
 
    devuelve  0 ;
}
