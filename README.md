# Análisis del Mercado Inmobiliario mediante Regresión Lineal Simple
## Descripción del Proyecto:
Este proyecto desarrolla un modelo de regresión lineal simple en C++ para predecir el precio de propiedades en Argentina, utilizando el número de baños como variable independiente. El objetivo es analizar la relación entre el número de baños y el precio de la propiedad, entendiendo cómo esta característica influye en el valor del inmueble.
Estructura del Proyecto
-	data/: Contiene el conjunto de datos en formato CSV con la información de las propiedades.
o	DS_Proyecto_01_Datos_Properati.csv
-	src/: Incluye el código fuente en C++ del modelo de regresión lineal.
o	main.cpp
-	resultados/: Almacena el reporte generado automáticamente con los resultados del análisis.
o	reporte_analisis.txt
-	presentacion/: Contiene la presentación del proyecto en formato PDF.
o	presentacion_proyecto.pdf
## Instrucciones de Compilación y Ejecución
1.	Compilar el código:
g++ -o analisis_inmobiliario src/main.cpp -std=c++17
2.	Ejecutar el programa:
./analisis_inmobiliario
Al ejecutar el programa, se procesarán los datos y se generará un reporte con los resultados del análisis en el directorio resultados/.
# Resultados
El análisis proporcionará información sobre cómo el número de baños afecta el precio de las propiedades en Argentina. Esto puede ser útil para compradores, vendedores y profesionales del sector inmobiliario.
Resumen de Resultados
# Implementación del Modelo de Regresión Lineal
Pendiente (m): 201814
Intercepto (b): -61548.4
Desempeño del Modelo
# Conjunto de Entrenamiento:
Error Cuadrático Medio (MSE): 1.55835e+10
Coeficiente de Determinación (R²): 0.511228
Interpretación: El modelo captura aproximadamente el 51% de la variación en los precios de las propiedades basada en el número de baños.
# Conjunto de Prueba:
Error Cuadrático Medio (MSE): 1.11727e+10
Coeficiente de Determinación (R²): -0.311395
Interpretación: El rendimiento del modelo en el conjunto de prueba es menor, lo que indica que el modelo no se generaliza perfectamente a nuevos datos.
## Conclusiones
El modelo de regresión lineal simple muestra que el número de baños tiene un impacto positivo en el precio de la propiedad, pero no es la única variable que influye.
Para mejorar el modelo, se sugiere incluir más variables explicativas como la ubicación y el tamaño de la propiedad.
